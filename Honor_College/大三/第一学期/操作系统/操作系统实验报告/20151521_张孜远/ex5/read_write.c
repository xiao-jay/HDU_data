int do_read(int fd, int length, char *text)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    int i, location, len;
    int logic_block_num, physic_block_num, off, count;
    unsigned char *p;

    /**
     * count 表示文件的读写指针
     * location 表示已经读取的位置
     * logic_block_num 表示当前读取的物理块的逻辑块号
     * off 表示块内偏移
     * physic_block_num 表示当前读取的物理块的物理块号
     * length 表示未读取的长度
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
 * 将给定内容写入到给定文件
 * @param fd 要写入的文件的文件描述符
 * @param content 要写入的字符串
 * @param length 要写入的长度
 * @param 写模式
 */
int do_write(int fd, char *content, size_t length, int wstyle)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    fat *curfat, *ifat;
    char text[WRITE_SIZE], input[WRITE_SIZE];
    int count, block_num, location, id;

    /**< text 表示最终要写入文件的字符串 */
    memset(text, 0, WRITE_SIZE);

    /**< 在写入之前, 首先将文件内的内容都读取到 text 内, 方便后面对于不同写模式进行操作 */
    count = openfile_list[fd].count;
    openfile_list[fd].count = 0;
    do_read(fd, openfile_list[fd].open_fcb.length, text);
    openfile_list[fd].count = count;
    /**< input 表示要写入的内容 */
    memset(input, 0, WRITE_SIZE);
    memcpy(input, content, length);

    if (wstyle == 'c')
    {
        /**< 截断写则直接将 text 清空, 然后将 input 写入 text */
        memset(text, 0, WRITE_SIZE);
        strcpy(text, input);
    }
    else if (wstyle == 'w')
    {
        /**< 覆盖写则从当前读写指针开始写入 */
        memcpy(text + openfile_list[fd].count, input, length);
    }
    else if (wstyle == 'a')
    {
        /**< 追加写则从文件末尾开始写入 */
        strcat(text, input);
    }

    /**
     * location text 表示已经写入的位置
     * block_num 表示当前物理块的块号
     * length 表示未写入的总长度
     * curfat 表示当前物理块的 fat
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
            /**< 如果还需要写入超过一整块, 则需要再申请一个空的物理块 */
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

    /**< 如果文件写完还有剩余的空磁盘块, 则需要将其释放 */
    ifat = curfat;
    while (ifat->id != END)
    {
        id = ifat->id;
        ifat->id = FREE;
        ifat = fat0 + id;
    }
    curfat->id = END;

    /**< 备份 fat0 到 fat1, 修改当前文件的文件描述符 */
    memcpy(fat1, fat0, BLOCK_SIZE * 2);
    openfile_list[fd].open_fcb.length = strlen(text);
    openfile_list[fd].fcb_state = 1;

    return strlen(input);
}



