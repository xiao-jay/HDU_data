int do_read(int fd, int length, char *text)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    int i, location, len;
    int logic_block_num, physic_block_num, off, count;
    unsigned char *p;

    /**
     * count ��ʾ�ļ��Ķ�дָ��
     * location ��ʾ�Ѿ���ȡ��λ��
     * logic_block_num ��ʾ��ǰ��ȡ���������߼����
     * off ��ʾ����ƫ��
     * physic_block_num ��ʾ��ǰ��ȡ��������������
     * length ��ʾδ��ȡ�ĳ���
     */
    count = openfile_list[fd].count;
    if (length > openfile_list[fd].open_fcb.length - count)
        length = openfile_list[fd].open_fcb.length - count;
    location = 0;

    logic_block_num = count / BLOCK_SIZE;
    off = count % BLOCK_SIZE;
    physic_block_num = openfile_list[fd].open_fcb.first;
    for (i = 0; i < logic_block_num; ++i)
        physic_block_num = (fat0 + physic_block_num)->id;

    while (length)
    {
        p = fs_head + BLOCK_SIZE * physic_block_num;
        if (off + length <= BLOCK_SIZE)
        {
            len = length;
        }
        else
        {
            len = BLOCK_SIZE - off;
        }

        strncpy(text + location, p + off, len);
        count += len;
        location += len;
        length -= len;
        
        physic_block_num = (fat0 + physic_block_num)->id;
    }

    return location;
}



/**
 * ����������д�뵽�����ļ�
 * @param fd Ҫд����ļ����ļ�������
 * @param content Ҫд����ַ���
 * @param length Ҫд��ĳ���
 * @param дģʽ
 */
int do_write(int fd, char *content, size_t length, int wstyle)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    fat *curfat, *ifat;
    char text[WRITE_SIZE], input[WRITE_SIZE];
    int count, block_num, location, id;

    /**< text ��ʾ����Ҫд���ļ����ַ��� */
    memset(text, 0, WRITE_SIZE);

    /**< ��д��֮ǰ, ���Ƚ��ļ��ڵ����ݶ���ȡ�� text ��, ���������ڲ�ͬдģʽ���в��� */
    count = openfile_list[fd].count;
    openfile_list[fd].count = 0;
    do_read(fd, openfile_list[fd].open_fcb.length, text);
    openfile_list[fd].count = count;
    /**< input ��ʾҪд������� */
    memset(input, 0, WRITE_SIZE);
    memcpy(input, content, length);

    if (wstyle == 'c')
    {
        /**< �ض�д��ֱ�ӽ� text ���, Ȼ�� input д�� text */
        memset(text, 0, WRITE_SIZE);
        strcpy(text, input);
    }
    else if (wstyle == 'w')
    {
        /**< ����д��ӵ�ǰ��дָ�뿪ʼд�� */
        memcpy(text + openfile_list[fd].count, input, length);
    }
    else if (wstyle == 'a')
    {
        /**< ׷��д����ļ�ĩβ��ʼд�� */
        strcat(text, input);
    }

    /**
     * location text ��ʾ�Ѿ�д���λ��
     * block_num ��ʾ��ǰ�����Ŀ��
     * length ��ʾδд����ܳ���
     * curfat ��ʾ��ǰ������ fat
     */
    location = 0;
    block_num = openfile_list[fd].open_fcb.first;
    length = strlen(text);
    curfat = fat0 + block_num;

    while (length)
    {
        strncpy((char *)fs_head + BLOCK_SIZE * block_num, text + location, BLOCK_SIZE);
        location += BLOCK_SIZE;

        if (length > BLOCK_SIZE)
        {
            /**< �������Ҫд�볬��һ����, ����Ҫ������һ���յ������ */
            if (curfat->id == END)
            {
                block_num = get_block();
                set_block(block_num);
                curfat->id = block_num;
                curfat = fat0 + block_num;
                curfat->id = END;
            }
            else
            {
                block_num = curfat->id;
                curfat = fat0 + block_num;
            }
            length -= BLOCK_SIZE;
        }
        else
        {
            length = 0;
        }
    }

    /**< ����ļ�д�껹��ʣ��Ŀմ��̿�, ����Ҫ�����ͷ� */
    ifat = curfat;
    while (ifat->id != END)
    {
        id = ifat->id;
        ifat->id = FREE;
        ifat = fat0 + id;
    }
    curfat->id = END;

    /**< ���� fat0 �� fat1, �޸ĵ�ǰ�ļ����ļ������� */
    memcpy(fat1, fat0, BLOCK_SIZE * 2);
    openfile_list[fd].open_fcb.length = strlen(text);
    openfile_list[fd].fcb_state = 1;

    return strlen(input);
}



