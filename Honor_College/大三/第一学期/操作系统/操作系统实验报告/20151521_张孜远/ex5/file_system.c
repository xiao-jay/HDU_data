#include "file_system.h"

/**
 * 启动文件系统并执行初始化
 */
int start_sys(void)
{
    FILE *fp;
    int i;

    fs_head = (unsigned char *)malloc(DISK_SIZE);
    memset(fs_head, 0, DISK_SIZE);

    if ((fp = fopen(SYS_FILENAME, "r")) != NULL)
    {
        fread(fs_head, DISK_SIZE, 1, fp);
        fclose(fp);
    }
    else
    {
        printf("System initializing ...\n");
        do_format();
    }

    init_useropen();

    return 0;
}

/**
 * 执行 format 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_format(char **args, int argc)
{
    if (argc > 1)
    {
        fprintf(stderr, "format: to many arguments\n");
        return 1;
    }

    do_format();

    init_useropen();

    return 1;
}

/**
 * 对系统做默认初始化
 */
int do_format(void)
{
    block0 *init_block = (block0 *)(fs_head + BLOCK_SIZE * 0);
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    fat_bitmap *bitmap = (fat_bitmap *)(fs_head + BLOCK_SIZE * 5);
    fcb *root = (fcb *)(fs_head + BLOCK_SIZE * 6);
    FILE *fp;
    int i;

    memset(fs_head, 0, DISK_SIZE);

    /**< 初始化 block0 */
    strcpy(init_block -> information,
           "Disk Size = 1MB, Block Size = 1KB, Block0 in 0, FAT0/1 in 1/3, Bitmap in 5, Root Directory in 6");
    init_block -> root = 6;
    init_block -> start_block = 7;

    /**< 初始化 fat0/1 */
    (fat0 + 0) -> id = END; // block0
    (fat0 + 1) -> id = 2;   // fat0
    (fat0 + 2) -> id = END;
    (fat0 + 3) -> id = 4; // fat1
    (fat0 + 4) -> id = END;
    (fat0 + 5) -> id = END; // fat_bitmap
    (fat0 + 6) -> id = END;   // root
    memcpy(fat1, fat0, BLOCK_SIZE * 2);

    set_fcb(root, "/", "d", ATTR_DIR, init_block -> root, BLOCK_SIZE, 1);

    /**< 初始化 fat_bitmap */
    for (i = 0; i < 16; ++i)
        (bitmap + i) -> bits = 0xffffffffffffffff;
    for (i = 0; i < init_block -> start_block; ++i)
        bitmap -> bits ^= 1ull << (63 - i);

    return 0;
}

/**
 * 执行 cd命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_cd(char **args, int argc)
{
    fcb *dir;

    if (argc == 1)
    {
        fprintf(stderr, "cd: missing operand\n");
        return 1;
    }
    if (argc > 2)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }

    /**< 获取该路径对应文件的 fcb */
    dir = find_fcb(args[1]);

    /**< 如果该路径不存在或者该路径对应文件不是目录文件 */
    if (dir == NULL || dir->attribute == ATTR_FILE)
    {
        fprintf(stderr, "cd: no such folder\n");
        return 1;
    }

    do_cd(args[1]);

    return 1;
}

/**
 * 修改当前工作路径为 path
 * @param path 目标路径
 */
int do_cd(char *path) {
    int fd, i;
    char abspath[PATH_LENGTH];
    get_abspath(abspath, path);
    if (!strcmp(abspath, current_dir)) {
        printf("cd: current directory has not changed\n");
        return 0;
    }
    fcb *dir = find_fcb(abspath);
    
    /**< 检查该路径所对应目录是否被打开 */
    fd = -1;
    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        if (openfile_list[i].free == 0)
            continue;
        if (dir->first == openfile_list[i].open_fcb.first)
            fd = i;
    }
    if (fd == -1)
        fd = do_open(path);

    /**< 关闭当前目录 */
    if (curdir != 0) do_close(curdir);
    /**< 修改 curdir 和 current_dir */
    curdir = fd;
    strcpy(current_dir, openfile_list[curdir].dir);

    return 0;
}

/**
 * 执行 mkdir 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_mkdir(char **args, int argc)
{
    char abspath[PATH_LENGTH], path[PATH_LENGTH], *p;
    fcb *dir;
    int i, count = 1;
    if (argc == 1)
    {
        fprintf(stderr, "mkdir: missing operand\n");
        return 1;
    }
    if (argc > 3)
    {
        fprintf(stderr, "mkdir: too many arguments\n");
        return 1;
    }
    if (argc == 3)
    {
        count = 0;
        for (p = args[2]; *p != '\0'; p++)
            count = count * 10 + (*p) - '0';
    }

    /**< 将给定路径转换成绝对路径 */
    memset(abspath, 0, PATH_LENGTH);
    get_abspath(abspath, args[1]);
    dir = find_fcb(abspath);

    if (dir != NULL)
    {
        fprintf(stderr, "mkdir: folder already exists\n");
        return 1;
    }

    for (i = 1; i <= count; ++i)
    {
        if (i == 1)
            do_mkdir(abspath);
        else
        {
            snprintf(path, PATH_LENGTH, "%s(%d)", abspath, i);
            do_mkdir(path);
        }
    }

    return 1;
}

/**
 * 创建多个目录, 如所需创建的目录的父目录不存在则会优先创建父目录, 依次递归
 * @param abspath 需要创建的目录的绝对路径
 */
int do_mkdir(const char *abspath)
{
    char *token, curpath[PATH_LENGTH], str[PATH_LENGTH], *curstr;
    fcb *dir, *f, *cur;
    int first, second;
    block0 *init_block = (block0 *)fs_head;
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    /**< str 为 abspath 后再加入一个 "/", 方便后续判断 */
    memset(str, 0, PATH_LENGTH);
    strcpy(str, abspath);
    strcat(str, "/");
    token = my_strtok(str, "/");

    /* dir 初始为 root */
    memset(curpath, 0, PATH_LENGTH);
    dir = (fcb *)(fs_head + BLOCK_SIZE * init_block->root);

    /**
     * 循环建立目录
     * 如果给定路径中有多个目录未被创建, 则会依次创建
     * curpath 表示当前已经完成创建的目录路径
     * dir 表示当前要创建目录的父目录的 fcb
     */
    do
    {
        /* 更新 curpath */
        strcat(curpath, "/");
        strcat(curpath, token);

        /**
         * first 表示当前要创建的目录的父目录的起始盘块号
         * second 表示当前要创建的目录起始盘块号
         * f 用于查找空的 fcb 以分配给要创建的目录
         * cur 表示当前的目录
         * dir 表示下一级目录
         */
        first = dir->first;
        cur = dir;

        /**< 当前要创建的目录已被创建, 则不执行下面的语句 */
        if ((dir = find_fcb(curpath)) != NULL)
        {
            continue;
        }

        f = get_fcb(cur);
        if (f == NULL)
        {
            fprintf(stderr, "mkdir: no more space\n");
            return -1;
        }

        /**< 找空的盘块 */
        second = get_block();
        if (second == -1)
        {
            fprintf(stderr, "mkdir: no more space\n");
            return -1;
        }

        set_block(second);

        /**< 创建新的目录, 并初始化 */
        set_fcb(f, token, "d", ATTR_DIR, second, BLOCK_SIZE, 1);

        /**< 初始化新目录 */
        init_folder(first, second);

        /**< 更新 dir 的值 */
        dir = f;
    } while ((token = my_strtok(NULL, "/")) != NULL);

    memcpy(fat1, fat0, BLOCK_SIZE * 2);
    return 0;
}

/**
 * 执行 rmdir 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_rmdir(char **args, int argc)
{
    fcb *dir;
    int i;

    if (argc == 1)
    {
        fprintf(stderr, "rmdir: missing operand\n");
        return 1;
    }
    if (argc > 2)
    {
        fprintf(stderr, "rmdir: too many arguments\n");
        return 1;
    }

    if (!strcmp(args[1], ".") || !strcmp(args[1], ".."))
    {
        fprintf(stderr, "rmdir: cannot remove %s: '.' or '..' is read only\n", args[i]);
        return 1;
    }

    if (!strcmp(args[1], "/"))
    {
        fprintf(stderr, "rmdir: cannot remove root directory\n");
        return 1;
    }

    dir = find_fcb(args[1]);

    if (dir == NULL)
    {
        fprintf(stderr, "rmdir: no such folder\n");
        return 1;
    }

    if (dir->attribute == ATTR_FILE)
    {
        fprintf(stderr, "rmdir: cannot remove %s: is a file\n", args[1]);
        return 1;
    }

    /**< 遍历 openfile_list 表查看该目录是否被打开 */
    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        if (openfile_list[i].free == 0)
        {
            continue;
        }

        if (dir->first == openfile_list[i].open_fcb.first)
        {
            fprintf(stderr, "rmdir: cannot remove %s: directory is open\n", args[1]);
            return 1;
        }
    }

    do_rmdir(dir);

    return 1;
}

/**
 * 删除给定目录
 * @param dir 要删除的目录的 fcb
 */
int do_rmdir(fcb *dir) {
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    /**< 将要删除的目录的 fcb 置为空, 注意这个 fcb 是存储在父目录的盘块里的 */
    dir -> free = 0;
    int id, lastid;
    /**< 回收盘块并修改 fat 表 */
    /**< 依次回收并清空该文件的所有盘块 */
    for (id = dir -> first; id != END; ) {
        lastid = id;
        id = (fat0 + id) -> id;
        // printf("%d\n", lastid);
        free_block(lastid);
    }
    memcpy(fat1, fat0, BLOCK_SIZE * 2);
    return 0;
}

/**
 * 执行 ls 命令
 * -n 表示常规显示, -l 表示长格式显示，-o 表示列出所有已打开文件
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_ls(char **args, int argc)
{
    int mode;

    if (argc > 2) {
        fprintf(stderr, "ls: too many arguments\n");
        return 1;
    }

    /**< 判断显示模式, 默认为 -n */
    mode = 'n';
    if (argc == 2) {
        if (!strcmp(args[1], "-l")) {
            mode = 'l';
        } else if (!strcmp(args[1], "-n")) {
            mode = 'n';
        } else if (!strcmp(args[1], "-o")) {
            mode = 'o';
        } else {
            fprintf(stderr, "ls: wrong arguments\n");
            return 1;
        }
    }

    do_ls(openfile_list[curdir].open_fcb.first, mode);

    return 1;
}

/**
 * 执行 ls 命令
 * @param first 要显示的目录所分配到的盘块号, 该目录的所有子目录和子文件的 fcb 都存储在这里
 * @param mode ls 命令的显示模式
 */
int do_ls(int first, int mode) {
    int i, count, length, id;
    char fullname[NAME_LENGTH], date[16], time[16];
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fcb *dir;
    block0 *init_block = (block0 *)fs_head;

    length = BLOCK_SIZE;

    if (mode == 'o') {
        for (i = 0; i < MAX_OPENFILE; ++i) {
            if (openfile_list[i].free == 0) continue;
            if (openfile_list[i].open_fcb.attribute == ATTR_DIR) {
                printf("%d\t", i);
                printf("%s", FOLDER_COLOR);
                printf("%s", openfile_list[i].dir);
                printf("%s\n", DEFAULT_COLOR);
            } else {
                printf("%d\t%s\n", i, openfile_list[i].dir);
            }
        }
        return 0;
    }

    /**< 遍历该目录所存储的所有 fcb */
    for (id = first; id != END; id = (fat0 + id) -> id) {
        dir = (fcb *)(fs_head + BLOCK_SIZE * id);
        for (i = 0, count = 1; i < length / sizeof(fcb); ++i, ++dir) {
            /**< 为空则跳过 */
            if (dir -> free == 0)
                continue;

            /**< 判断显示模式并输出 */
            if (mode == 'n') {
                if (dir -> attribute == 0) {
                    printf("%s", FOLDER_COLOR);
                    printf("%s\t", dir->filename);
                    printf("%s", DEFAULT_COLOR);
                } else {
                    get_fullname(fullname, dir);
                    printf("%s\t", fullname);
                }
                if (count % 5 == 0) printf("\n");
                count++;
            }
            else {
                trans_date(date, dir->date);
                trans_time(time, dir->time);
                get_fullname(fullname, dir);
                printf("%d\t%6d\t%6ld\t%s\t%s\t", dir->attribute, dir->first, dir->length, date, time);
                if (dir->attribute == 0) {
                    printf("%s", FOLDER_COLOR);
                    printf("%s\n", fullname);
                    printf("%s", DEFAULT_COLOR);
                }
                else printf("%s\n", fullname);
                count++;
            }
        }
    }
    if (mode == 'n') printf("\n");
    return 0;
}

/**
 * 执行 create 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_create(char **args, int argc)
{
    char abspath[PATH_LENGTH], parpath[PATH_LENGTH];
    char filename[NAME_LENGTH];
    char *end;

    if (argc == 1)
    {
        fprintf(stderr, "create: missing operand\n");
        return 1;
    }

    memset(abspath, 0, PATH_LENGTH);
    memset(parpath, 0, PATH_LENGTH);
    memset(filename, 0, NAME_LENGTH);

    /**< end 为 '/' 加上要创建的文件名 */
    get_abspath(abspath, args[1]);
    end = strrchr(abspath, '/');

    /**< 获取文件名 filename 和父目录的绝对路径 parpath, 其中 end == abspath 表示父目录为根目录 */
    if (end == abspath)
    {
        strcpy(parpath, "/");
        strcpy(filename, abspath + 1);
    }
    else
    {
        strncpy(parpath, abspath, end - abspath);
        strcpy(filename, end + 1);
    }

    if (find_fcb(parpath) == NULL)
    {
        fprintf(stderr, "create: cannot create \'%s\': farent folder not exists\n", parpath);
        return 1;
    }

    if (find_fcb(abspath) != NULL)
    {
        fprintf(stderr, "create: cannot create \'%s\': folder or file exists\n", args[1]);
        return 1;
    }

    do_create(parpath, filename);

    return 1;
}

/**
 * 创建文件
 * 如果文件名没有给定后缀名, 则后缀名默认为 .f
 * @param parpath 父目录所对应的绝对路径
 * @param filename 文件名
 */
int do_create(const char *parpath, const char *filename)
{
    char fullname[NAME_LENGTH], fname[16], exname[8];
    char *token;
    int first;
    fcb *dir = find_fcb(parpath);
    first = dir->first;
    fcb *f;

    f = get_fcb(dir);
    if (f == NULL)
    {
        fprintf(stderr, "create: no more space\n");
        return -1;
    }

    /**< 分配一个盘块 */
    first = get_block();
    if (first == -1)
    {
        fprintf(stderr, "create: no more space\n");
        return -1;
    }
    set_block(first);

    /**< 获取文件的详细信息, 并设置文件的 fcb */
    memset(fullname, 0, NAME_LENGTH);
    memset(fname, 0, sizeof(fname));
    memset(exname, 0, sizeof(exname));
    strcpy(fullname, filename);
    token = strtok(fullname, ".");
    strncpy(fname, token, 8);
    token = strtok(NULL, ".");
    if (token != NULL)
    {
        strncpy(exname, token, 4);
    }
    else
    {
        strncpy(exname, "f", 2);
    }

    set_fcb(f, fname, exname, ATTR_FILE, first, 0, 1);

    return 0;
}

/**
 * 执行 rm 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_rm(char **args, int argc)
{
    int i;
    fcb *file;

    if (argc == 1)
    {
        fprintf(stderr, "rm: missing operand\n");
        return 1;
    }

    file = find_fcb(args[1]);

    if (file == NULL)
    {
        fprintf(stderr, "rm: cannot remove %s: no such file\n", args[1]);
        return 1;
    }

    if (file->attribute == ATTR_DIR)
    {
        fprintf(stderr, "rm: cannot remove %s: is a directory\n", args[1]);
        return 1;
    }

    /**< 遍历 openfile_list 判断该文件是否被打开 */
    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        if (openfile_list[i].free == 0)
            continue;

        if (file->first == openfile_list[i].open_fcb.first)
        {
            fprintf(stderr, "rm: cannot remove %s: file is open\n", args[1]);
            return 1;
        }
    }

    do_rm(file);

    return 1;
}

/**
 * 删除文件
 * @param file 表示要删除的文件的 fcb
 */
int do_rm(fcb *file)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    int id, lastid;

    /**< 将要删除的目录的 fcb 置为空, 注意这个 fcb 是存储在父目录的盘块里的 */
    file -> free = 0;

    /**< 依次回收并清空该文件的所有盘块 */
    for (id = file -> first; id != END; ) {
        lastid = id;
        id = (fat0 + id) -> id;
        // printf("%d\n", lastid);
        free_block(lastid);
    }
    memcpy(fat1, fat0, BLOCK_SIZE * 2);
    return 0;
}

/**
 * 执行 open 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_open(char **args, int argc)
{
    int i;
    fcb *file;

    if (argc == 1)
    {
        fprintf(stderr, "open: missing operand\n");
        return 1;
    }

    if (argc > 2)
    {
        fprintf(stderr, "close: too many arguments\n");
        return 1;
    }

    file = find_fcb(args[1]);

    if (file == NULL)
    {
        fprintf(stderr, "open: cannot open %s: no such file or folder\n", args[1]);
        return 1;
    }

    /**< 遍历 openfile_list 查看文件是否已被打开 */
    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        if (openfile_list[i].free == 0)
            continue;

        if (file->first == openfile_list[i].open_fcb.first)
        {
            fprintf(stderr, "open: cannot open %s: file or folder is open\n", args[1]);
            return 1;
        }
    }

    do_open(args[1]);

    return 1;
}

/**
 * 打开文件或目录
 * @param path 需要打开的文件或目录的相对路径
 */
int do_open(char *path)
{
    char abspath[PATH_LENGTH];
    int fd;
    fcb *file;

    /**< 获取 openfile_list 的空位 */
    fd = get_useropen();
    if (fd == -1)
    {
        fprintf(stderr, "open: cannot open file, no more useropen entry\n");
        return -1;
    }

    memset(abspath, 0, PATH_LENGTH);
    get_abspath(abspath, path);

    file = find_fcb(abspath);

    /**< 将该文件加入到 openfile_list 中, 表示已打开该文件 */
    fcb_cpy(&openfile_list[fd].open_fcb, file);
    openfile_list[fd].free = 1;
    openfile_list[fd].count = 0;
    openfile_list[fd].fcb_state = 0;
    memset(openfile_list[fd].dir, 0, 80);
    strcpy(openfile_list[fd].dir, abspath);

    return fd;
}

/**
 * 执行 close 命令
 * close -a 表示关闭所有已打开的文件
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_close(char **args, int argc)
{
    int i;
    fcb *file;
    char fullname[NAME_LENGTH];
    if (argc == 1) {
        fprintf(stderr, "close: missing operand\n");
        return 1;
    }

    if (argc > 2) {
        fprintf(stderr, "close: too many arguments\n");
        return 1;
    }

    if (!strcmp(args[1], "-a")) {
        for (i = 1; i < MAX_OPENFILE; ++i) {
            if (openfile_list[i].free == 0)
                continue;
            do_close(i);
        }
    } else {
        file = find_fcb(args[1]);
        if (file == NULL) {
            fprintf(stderr, "close: cannot close %s: no such file or folder\n", args[1]);
            return 1;
        }
        get_fullname(fullname, file);
        if (!strcmp(fullname, "/")) {
            fprintf(stderr, "close: cannot close %s: root must be open\n", args[1]);
            return 1;
        }
        /**< 遍历 openfile_list 查看文件是否已被打开 */
        int flag = 0;
        for (i = 0; i < MAX_OPENFILE; ++i) {
            if (openfile_list[i].free == 0)
                continue;

            if (file -> first == openfile_list[i].open_fcb.first) {
                do_close(i);
                flag = 1;
                break;
            }
        }

        if (!flag) fprintf(stderr, "close: file is not open\n");
    }
    /**< 当前所在的目录被关闭 */
    if (openfile_list[curdir].free == 0) {
        curdir = 0;
        strcpy(current_dir, openfile_list[curdir].dir);
    }
    return 1;
}

/**
 * 关闭文件
 * @param fd 需要关闭的文件的文件描述符
 */
int do_close(int fd)
{
    /**< 如果该文件 fcb 被修改过, 则写入 */
    if (openfile_list[fd].open_fcb.attribute == ATTR_FILE 
        && openfile_list[fd].fcb_state == 1) {
        fcb_cpy(find_fcb(openfile_list[fd].dir), &openfile_list[fd].open_fcb);
    }

    openfile_list[fd].free = 0;
}

/**
 * 执行 write 命令
 * -c 截断写：放弃文件原有内容, 重新写文件
 * -w 覆盖写：修改文件从当前读写指针所指的位置开始的部分
 * -a 追加写：在原文件的最后添加新的内容
 * 默认模式为截断写
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_write(char **args, int argc)
{
    int mode, i, j;
    fcb *file;
    char str[WRITE_SIZE], line[WRITE_SIZE], *end;

    if (argc == 1)
    {
        fprintf(stderr, "write: missing operand\n");
        return 1;
    }

    if (argc > 3)
    {
        fprintf(stderr, "write: too many arguments\n");
        return 1;
    }

    if (argc == 3)
    {
        if (!strcmp(args[2], "-c"))
        {
            mode = 'c';
        }
        else if (!strcmp(args[2], "-w"))
        {
            mode = 'w';
        }
        else if (!strcmp(args[2], "-a"))
        {
            mode = 'a';
        }
        else
        {
            fprintf(stderr, "write: wrong arguments\n");
            return 1;
        }
    }
    else
    {
        mode = 'c';
    }

    file = find_fcb(args[1]);

    if (file == NULL)
    {
        fprintf(stderr, "write: file not exists\n");
        return 1;
    }

    if (file->attribute == ATTR_DIR)
    {
        fprintf(stderr, "write: must be file\n");
        return 1;
    }


    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        if (openfile_list[i].free == 0)
            continue;

        if (file->first != openfile_list[i].open_fcb.first)
            continue;

        /**< 根据写模式修改文件的读写指针 */
        if (mode == 'c')
        {
            openfile_list[i].count = 0;
        }
        else if (mode == 'a')
        {
            openfile_list[i].count = openfile_list[i].open_fcb.length;
        }
        else
        {
            printf("please input location: ");
            scanf("%d", &openfile_list[i].count);
            getchar();
        }

        memset(line, 0, WRITE_SIZE);
        memset(str, 0, WRITE_SIZE);
        /**< 每次读取一行内容, 直至在末尾读取到 !q */
        printf("please enter the file content, use \"!q\" in the end of the line to quit\n");
        fflush(stdin);
        while (fgets(line, WRITE_SIZE, stdin))
        {
            /**< 判断末尾是否为 !q */
            end = strchr(line, '!');
            // printf("%s", end);
            if (end != NULL && !strcmp(end, "!q\n"))
            {
                *end = '\0';
                strcat(str, line);
                break;
            }
            else
            {
                strcat(str, line);
            }
        }
        do_write(i, str, strlen(str), mode);

        return 1;
    }

    fprintf(stderr, "write: file is not open\n");
    return 1;
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

    /**< 备份 fa0 到 fat1, 修改当前文件的文件描述符 */
    memcpy(fat1, fat0, BLOCK_SIZE * 2);
    openfile_list[fd].open_fcb.length = strlen(text);
    openfile_list[fd].fcb_state = 1;

    return strlen(input);
}

/**
 * 执行 read 命令
 * -n 表示默认读, 即从文件的开头开始读取
 * -s 表示选择读, 需要给定读取的起始位置和长度
 * 默认是 -n
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_read(char **args, int argc)
{
    int mode, length, i;
    fcb *file;
    char str[WRITE_SIZE];

    if (argc > 3)
    {
        fprintf(stderr, "write: too many arguments\n");
        return 1;
    }

    if (argc == 3)
    {
        if (!strcmp(args[2], "-a"))
        {
            mode = 'a';
        }
        else if (!strcmp(args[2], "-s"))
        {
            mode = 's';
        }
        else
        {
            fprintf(stderr, "read: wrong arguments\n");
            return 1;
        }
    }
    else
    {
        mode = 'a';
    }

    file = find_fcb(args[1]);

    if (file == NULL)
    {
        fprintf(stderr, "read: file not exists\n");
        return 1;
    }

    if (file->attribute == ATTR_DIR)
    {
        fprintf(stderr, "read: must be file\n");
        return 1;
    }

    memset(str, 0, WRITE_SIZE);

    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        if (openfile_list[i].free == 0)
            continue;

        if (file->first != openfile_list[i].open_fcb.first)
            continue;

        /**< 根据读模式修改读写指针 */
        if (mode == 'a')
        {
            openfile_list[i].count = 0;
            length = 65535;
        }
        else
        {
            printf("please input location: ");
            scanf("%d", &openfile_list[i].count);
            printf("please input length: ");
            scanf("%d", &length);
            getchar();
        }

        do_read(i, length, str);
        fputs(str, stdout);

        return 1;
    }

    fprintf(stderr, "read: file is not open\n");
    return 1;
}

/**
 * 读取给定文件的内容
 * @param fd 待读取的文件的文件描述符
 * @param length 读取最大长度
 * @param text 读取到的字符串
 */
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
 * 执行 showfat 命令
 * -l 以链接方式显示 FAT ,只会显示已占用的物理块编号
 * -a 显示 FAT 完整的 FAT
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_showfat(char **args, int argc)
{
    if (argc > 2)
    {
        fprintf(stderr, "showfat: too many arguments\n");
        return 1;
    }
    int mode;
    if (argc == 1)
        mode = 'l';
    else
    {
        if (!strcmp(args[1], "-l"))
            mode = 'l';
        else if (!strcmp(args[1], "-a"))
            mode = 'a';
        else
        {
            fprintf(stderr, "showfat: wrong arguments\n");
            return 1;
        }
    }
    do_showfat(mode);
    return 1;
}

/**
 * 显示 FAT
 * @param mode 显示模式
 */
int do_showfat(int mode)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    int i, id;
    if (mode == 'l')
    {
        int vis[BLOCK_NUM] = {0};
        for (i = 0; i < BLOCK_NUM; ++i)
            if (!vis[i])
            {
                vis[i] = 1;
                id = i;
                if ((fat0 + id)->id == FREE)
                    continue;
                printf(" %04x ", id);
                while ((fat0 + id)->id != END)
                {
                    id = (fat0 + id)->id;
                    vis[id] = 1;
                    printf("-> %04x ", id);
                }
                printf("\n");
            }
    }
    else
    {
        for (i = 0; i < BLOCK_NUM; ++i)
        {
            printf("%04x(%04x) ", i, (fat0 + i)->id);
            if (i % 6 == 5 || i == BLOCK_NUM - 1)
                printf("\n");
        }
    }
}

/**
 * 执行 help 命令
 * @param args 命令及参数
 * @param argc 参数个数
*/
int my_help(char **args, int argc) {
    printf("format              \t格式化文件系统\n");
    printf("cd [dir]            \t进入目录\n");
    printf("mkdir [dir] [num]   \t创建目录\n");
    printf("rmdir [dir]         \t删除一个空目录\n");
    printf("ls [-n|-l|-o]       \t列出文件\n");
    printf("create [file]       \t创建文件\n");
    printf("rm [file]           \t删除文件\n");
    printf("open [dir|file]     \t打开目录或文件\n");
    printf("close [dir|file|-a] \t关闭目录或文件\n");
    printf("write [-c|-w|-a]    \t写入文件\n");
    printf("read [-n|-s]        \t读取文件\n");
    printf("showfat [-l|-a]     \t显示 FAT 表\n");
    printf("help                \t显示命令提示\n");
    printf("exit                \t退出文件系统\n");
    return 1;
}

/**
 * 执行 exit 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_exitsys(char **args, int argc)
{
    int i;
    FILE *fp;

    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        do_close(i);
    }

    /**< 保存文件系统 */
    fp = fopen(SYS_FILENAME, "w");
    fwrite(fs_head, DISK_SIZE, 1, fp);
    free(fs_head);
    fclose(fp);

    return 0;
}

/**
 * 拷贝一个 src fcb 到 des fcb
 * @param des 目标 fcb
 * @param src 源 fcb
 */
fcb *fcb_cpy(fcb *des, fcb *src)
{
    memset(des->filename, 0, 8);
    memset(des->exname, 0, 4);

    strncpy(des->filename, src->filename, 8);
    strncpy(des->exname, src->exname, 4);
    des->attribute = src->attribute;
    des->time = src->time;
    des->date = src->date;
    des->first = src->first;
    des->length = src->length;
    des->free = src->free;

    return des;
}

/**
 * 根据给定路径得到对应文件或目录的 fcb
 * @param path 相对或绝对路径
 */
fcb *find_fcb(const char *path)
{
    char abspath[PATH_LENGTH];
    char *token;
    block0 *init_block = (block0 *)fs_head;

    get_abspath(abspath, path);
    token = strtok(abspath, "/");

    /**< token == NULL 表示 path 为 root */
    if (token == NULL)
    {
        return (fcb *)(fs_head + BLOCK_SIZE * init_block->root);
    }

    /**< 递归求 fcb */
    return find_fcb_r(token, init_block->root);
}

/**
 * 递归求 fcb
 * @param token 绝对路径
 * @param first 当前目录的起始物理块
 */
fcb *find_fcb_r(char *token, int first)
{
    int i, length, id;
    char fullname[NAME_LENGTH] = "\0";
    fcb *dir;
    block0 *init_block = (block0 *)fs_head;
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);

    length = BLOCK_SIZE;

    /**
     * length 表示当前目录的单个物理块大小
     * dir 当前目录的 fcb
     * fullname 表示当前目录或文件的全名, 文件需加上扩展名, 目录不需要, fullname 的作用之一就是区别文件和目录
     */
    for (id = first; id != END; id = (fat0 + id) -> id) {
        dir = (fcb *)(fs_head + BLOCK_SIZE * id);
        for (i = 0; i < length / sizeof(fcb); ++i, dir++)
        {
            if (dir->free == 0) {
                continue;
            }

            get_fullname(fullname, dir);
            if (!strcmp(token, fullname))
            {
                token = strtok(NULL, "/");
                if (token == NULL)
                {
                    return dir;
                }

                /**< 没有找到底则继续递归找 */
                return find_fcb_r(token, dir->first);
            }
        }
    }

    return NULL;
}

/**
 * 给定一个目录的 fcb ，在其物理块中寻找一个空的 fcb ，若没有则会创建新的盘块
 * @param dir 目录的fcb
 */
fcb *get_fcb(fcb *dir)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);
    int flag = 0, i;
    int id, tmp, first = dir->first;
    /**< 找空的 fcb */
    fcb *f;
    for (id = first;; id = (fat0 + id)->id)
    {
        f = (fcb *)(fs_head + BLOCK_SIZE * id);
        for (i = 0; i < BLOCK_SIZE / sizeof(fcb); ++i, ++f)
        {
            /**< 在当前目录的某个盘块下找到空的 fcb */
            if (f->free == 0)
            {
                flag = 1;
                break;
            }
        }
        if ((fat0 + id)->id == END)
            break;
    }

    /**< 没有空的 fcb ，需要给当前目录分配新的盘块 */
    if (!flag)
    {
        tmp = get_block();
        if (tmp == -1)
            return NULL;
        set_block(tmp);
        dir->length += BLOCK_SIZE;
        (fat0 + id)->id = tmp;
        f = (fcb *)(fs_head + BLOCK_SIZE * tmp);
        memcpy(fat1, fat0, BLOCK_SIZE * 2);
    }
    return f;
}

/**
 * 根据给定属性设置给定 fcb
 */
int set_fcb(fcb *f, const char *filename, const char *exname, unsigned char attr, unsigned short first,
            unsigned long length, char ffree)
{
    time_t *now = (time_t *)malloc(sizeof(time_t));
    struct tm *timeinfo;
    time(now);
    timeinfo = localtime(now);

    memset(f->filename, 0, 8);
    memset(f->exname, 0, 4);
    strncpy(f->filename, filename, 8);
    strncpy(f->exname, exname, 8);
    f->attribute = attr;
    f->time = get_time(timeinfo);
    f->date = get_date(timeinfo);
    f->first = first;
    f->length = length;
    f->free = ffree;

    free(now);

    return 0;
}

/**
 * 通过 bitmap 找空的物理块
 */
int get_bits(void)
{
    fat_bitmap *bitmap = (fat_bitmap *)(fs_head + BLOCK_SIZE * 5);
    int i;

    /**
     * 物理块一共有 1K, 即 1024, 一个 bitmap 可以将 64 个 0/1 压成一个 unsigned long long
     * 我们查找的时候只要找第一个 1 就行, hightbit 为给定二进制数的最高位的 1
     */
    for (i = 0; i < 16; ++i, ++bitmap)
        if (bitmap->bits != 0)
            return i * 64 + 63 - highbit(bitmap->bits);

    return -1;
}

/**
 * 物理块被分配后设置 bitmap
 * @param first 表示被分配的物理块的块号
 */
int set_bits(int first)
{
    fat_bitmap *bitmap = (fat_bitmap *)(fs_head + BLOCK_SIZE * 5);
    int num, offset;

    /**< num 表示 first 应该对应第几个 bitmap, offset 表示对应 bitmap 的第几位 */
    num = first / 64;
    offset = first % 64;

    (bitmap + num)->bits ^= 1ull << (63 - offset);

    return 0;
}

/**
 * 找没有被分配的物理块
 */
int get_block()
{
    return get_bits();
}

/**
 * 释放给定物理块的空间, 并修改 fat
 * @param first 表示物理块的块号
 */
int free_block(int first)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);

    (fat0 + first)->id = FREE;
    (fat1 + first)->id = FREE;

    memset((void *)(fs_head + BLOCK_SIZE * first), 0, BLOCK_SIZE);

    set_bits(first);

    return 0;
}

/**
 * 分配给定物理块
 * @param first 物理块的块号
 */
int set_block(int first)
{
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fat *fat1 = (fat *)(fs_head + BLOCK_SIZE * 3);

    (fat0 + first)->id = END;
    (fat1 + first)->id = END;

    set_bits(first);

    return 0;
}

/**
 * 求给定相对路径的绝对路径
 * @param abspath 绝对路径
 * @param relpath 相对路径
 */
char *get_abspath(char *abspath, const char *relpath)
{
    /**< 如果 relpath 为 root 或以 / 开头 */
    if (!strcmp(relpath, "/") || relpath[0] == '/')
    {
        strcpy(abspath, relpath);
        return 0;
    }

    char str[PATH_LENGTH];
    char *token, *end;

    memset(abspath, 0, PATH_LENGTH);
    abspath[0] = '/';
    strcpy(abspath, current_dir);

    strcpy(str, relpath);
    token = strtok(str, "/");

    do
    {
        /**< 如果是 . 则表示当前目录, 不需要做任何操作 */
        if (!strcmp(token, "."))
        {
            continue;
        }
        /**< 如果 .. 则表示需要回退一个目录 */
        if (!strcmp(token, ".."))
        {
            /**< 如果当前在 root ，回退后仍为 root 目录 */
            if (!strcmp(abspath, "/"))
            {
                continue;
            }
            else
            {
                /**< 如果当前在 root 的一级子目录, 直接回退为 "/" */
                end = strrchr(abspath, '/');
                if (end == abspath)
                {
                    strcpy(abspath, "/");
                    continue;
                }
                /**< 将 end 的首位置成 0, 相当于将 abspath 的最后一个 "/" 置为 0, 即完成了回退 */
                memset(end, 0, 1); // *end = ‘\0'
                continue;
            }
        }
        /**< 规范一下目录格式："/xx/yy" -> "/xx/yy/" */
        if (strcmp(abspath, "/"))
        {
            strcat(abspath, "/");
        }
        strcat(abspath, token);
    } while ((token = strtok(NULL, "/")) != NULL);

    return abspath;
}

/**
 * 得到给定文件的全名, 目录文件不带后缀, 普通文件带后缀
 * @param fullname 全名
 * @param f 给定文件的 fcb
 */
char *get_fullname(char *fullname, fcb *f)
{
    memset(fullname, 0, NAME_LENGTH);

    strcat(fullname, f->filename);
    if (f->attribute == ATTR_FILE)
    {
        strncat(fullname, ".", 2);
        strncat(fullname, f->exname, 4);
    }

    return fullname;
}

/**
 * 找空的 openfile_list 的下标
 */
int get_useropen(void)
{
    int i;

    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        if (openfile_list[i].free == 0)
            return i;
    }

    return -1;
}

/**
 * 初始化目录
 */
int init_folder(int first, int second)
{
    int i;
    fcb *par = (fcb *)(fs_head + BLOCK_SIZE * first);
    fcb *cur = (fcb *)(fs_head + BLOCK_SIZE * second);

    for (i = 0; i < BLOCK_SIZE / sizeof(fcb); ++i, cur++) {
        cur->free = 0;
    }

    return 0;
}

/**
 * 初始化用户打开目录
*/
int init_useropen() {
    int i;
    /**< 初始化所有 openfile_list */
    fcb *empty = (fcb *)malloc(sizeof(fcb));
    set_fcb(empty, "\0", "\0", 0, 0, 0, 0);
    for (i = 0; i < MAX_OPENFILE; ++i)
    {
        fcb_cpy(&openfile_list[i].open_fcb, empty);
        strcpy(openfile_list[i].dir, "\0");
        openfile_list[i].free = 0;
        openfile_list[i].count = 0;
        openfile_list[i].fcb_state = 0;
    }

    /**< 将根目录加载到 openfile_list 中 */
    fcb_cpy(&openfile_list[0].open_fcb, ((fcb *)(fs_head + 6 * BLOCK_SIZE)));
    strcpy(openfile_list[0].dir, "/");
    openfile_list[0].count = 0;
    openfile_list[0].fcb_state = 0;
    openfile_list[0].free = 1;
    curdir = 0;

    /**< 初始化其它全局变量 */
    strcpy(current_dir, ROOT);

    free(empty);

    return 0;
}

unsigned short get_time(struct tm *timeinfo)
{
    int hour, min, sec;
    unsigned short result;

    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    result = (hour << 11) + (min << 5) + (sec >> 1);

    return result;
}

unsigned short get_date(struct tm *timeinfo)
{
    int year, mon, day;
    unsigned short result;

    year = timeinfo->tm_year;
    mon = timeinfo->tm_mon;
    day = timeinfo->tm_mday;
    result = (year << 9) + (mon << 5) + day;

    return result;
}

char *trans_date(char *sdate, unsigned short date)
{
    int year, month, day;
    memset(sdate, '\0', 16);

    year = date & 0xfe00;
    month = date & 0x01e0;
    day = date & 0x001f;
    sprintf(sdate, "%04d-%02d-%02d", (year >> 9) + 1900, (month >> 5) + 1, day);
    return sdate;
}

char *trans_time(char *stime, unsigned short time)
{
    int hour, min, sec;
    memset(stime, '\0', 16);

    hour = time & 0xfc1f;
    min = time & 0x03e0;
    sec = time & 0x001f;
    sprintf(stime, "%02d:%02d:%02d", hour >> 11, min >> 5, sec << 1);
    return stime;
}

/**
 * 和 strtok 一样
 */
char *my_strtok(char *str, const char *ctr)
{
    static char *myStrtok = NULL;
    char *sbegin, *send;
    sbegin = str ? str : myStrtok;
    if (!sbegin)
    {
        return NULL;
    }
    sbegin += strspn(sbegin, ctr);
    if (*sbegin == '\0')
    {
        myStrtok = NULL;
        return NULL;
    }
    send = strpbrk(sbegin, ctr);
    if (send && *send != '\0')
        *send++ = '\0';
    myStrtok = send;
    return sbegin;
}

void *change_fullname(fcb *f, char *changename, char *mode){
    //printf("***%u***\n", openfile_list[curdir].open_fcb.first);
    int flag = 1;
    int i, count, length;
    unsigned short id;
    char fullname[NAME_LENGTH], the_same_file[NAME_LENGTH], date[16], time[16];
    char *token;
    fat *fat0 = (fat *)(fs_head + BLOCK_SIZE * 1);
    fcb *dir, *file;
    block0 *init_block = (block0 *)fs_head;
    length = BLOCK_SIZE;
    for (id = openfile_list[curdir].open_fcb.first; id != END; id = (fat0 + id) -> id) {
        dir = (fcb *)(fs_head + BLOCK_SIZE * id);
        //printf("yes!\n");
        for (i = 0, count = 1; i < length / sizeof(fcb); ++i, ++dir) {
            if (dir -> free == 0) continue;
            if (dir -> attribute == 0) continue;
  	    else {
                //printf("yes!!\n");
                get_fullname(fullname, dir);
                //printf("%s %s\n", fullname, changename);
                //printf("yes!!!\n");
		if (strcmp(fullname, changename) == 0){
                    //printf("The same!\n");
                    //printf("%s %s", fullname, f->exname);
                    flag = 0;
		    strcpy(the_same_file, changename);
		}
            }
        }
    }
   
    memset(fullname, 0, NAME_LENGTH);
    strcpy(fullname, changename);
    token = strtok(fullname, ".");
    token = strtok(NULL, ".");
    //printf("flag is %d\n", flag);
    char ans;
    if (!flag){
        printf("There already exists a file named %s\n", the_same_file);
        file = find_fcb(the_same_file); 
	if (strcmp(mode, "-b") == 0){
	    //overwrite after backup, backup = rename + new file 
 
	    memset(fullname, 0, NAME_LENGTH);
	    strcpy(fullname, changename);
	    token = strtok(fullname, ".");
	    strncpy(f->filename, token, 8);
	    token = strtok(NULL, ".");
	    //strcpy(f->exname, token);

	    //rename 
            char ori_file[NAME_LENGTH];
            const char* backup = "~";
            //printf("***%s***%s***%s", f->filename, backup, token);
            strcpy(ori_file, strcat(f->filename, backup));
            strcpy(file->filename, ori_file);

            //new file
	    memset(fullname, 0, NAME_LENGTH);
	    strcpy(fullname, changename);
	    token = strtok(fullname, ".");
	    strncpy(f->filename, token, 8);
	    token = strtok(NULL, ".");
	    strcpy(f->exname, token);
        }else if (strcmp(mode, "-f") == 0) {
		//delete the_same_file
		fat *fat_rb0 = (fat *)(fs_head + BLOCK_SIZE * 1);
		fat *fat_rb1 = (fat *)(fs_head + BLOCK_SIZE * 3);
		int id, lastid;
		file -> free = 0;
		/**< 依次回收并清空该文件的所有盘块 */
		for (id = file -> first; id != END; ) {
	            lastid = id;
		    id = (fat0 + id) -> id;
	            free_block(lastid);
		}
		memcpy(fat_rb1, fat_rb0, BLOCK_SIZE * 2);

		//change the file name
                char *token;
		memset(fullname, 0, NAME_LENGTH);
		strcpy(fullname, changename);
		token = strtok(fullname, ".");
		strncpy(f->filename, token, 8);
		token = strtok(NULL, ".");
		strcpy(f->exname, token);
	}else if (strcmp(mode, "-i") == 0){
            printf("mv: overwrite '%s'?\n", the_same_file);
            printf("please print 'y == yes, n == no' to continue\n");
            scanf("%c", &ans);
            if (ans == 'y') {
            //overwrite, overwrite = delete ori_file + change the file name

            //delete the_same_file
            fat *fat_rb0 = (fat *)(fs_head + BLOCK_SIZE * 1);
	    fat *fat_rb1 = (fat *)(fs_head + BLOCK_SIZE * 3);
	    int id, lastid;
	    file -> free = 0;
	    /**< 依次回收并清空该文件的所有盘块 */
	    for (id = file -> first; id != END; ) {
	        lastid = id;
                id = (fat0 + id) -> id;
	        free_block(lastid);
            }
	    memcpy(fat_rb1, fat_rb0, BLOCK_SIZE * 2);

	    //change the file name
            char *token;
	    memset(fullname, 0, NAME_LENGTH);
	    strcpy(fullname, changename);
	    token = strtok(fullname, ".");
	    strncpy(f->filename, token, 8);
	    token = strtok(NULL, ".");
	    strcpy(f->exname, token);
	    }else printf("please enter the instrument again.");
        }else printf("please use 'mv XXX XXX -i' for more information.");
    }else{
        //printf("normal condition\n");
        memset(fullname, 0, NAME_LENGTH);
	strcpy(fullname, changename);
	token = strtok(fullname, ".");
	strncpy(f->filename, token, 8);
	token = strtok(NULL, ".");
	strcpy(f->exname, token);
    }
}

/*void *change_file_direction(fcb *f, char *changename, int mode){
    // create new_file
    my_create();
    // read ori_file and write new_file
    read(ori_file);
    write(new_file);
    // delete ori_file
    delete(ori_file);
}
*/

/**
 * 执行 mv 命令
 * @param args 命令及参数
 * @param argc 参数个数
 */
int my_mv(char **args, int argc){
    int i;
    fcb *file;
    if (argc < 3)
    {
        fprintf(stderr, "mv: missing arguments.\n");
        return 1;
    }

    file = find_fcb(args[1]);

    if (file == NULL)
    {
        fprintf(stderr, "mv: The file does not exist.\n", args[1]);
        return 1;
    }

    if (file->attribute == ATTR_DIR)
    {
        fprintf(stderr, "mv: It is not a file, it is a catalogue.\n", args[1]);
        return 1;
    }

    /**< 遍历 openfile_list 判断该文件是否被打开 */
    for (i = 0; i < MAX_OPENFILE; ++i){
        if (openfile_list[i].free == 0) continue;
        if (file->first == openfile_list[i].open_fcb.first){
            fprintf(stderr, "mv: cannot rename %s: file is open\n", args[1]);
            return 1;
        }
    }
    
    char mode[3];
    char flag_ch;
    int dflag = 0;
    if (argc == 3){
    	strcpy(mode, "-wa");
	//printf("please print file&file operation or dic&file operation, namely using f and d in place of them.");
        //scanf("%c", &flag_ch);
	//if (strcmp(flag_ch, "f")) dflag = 0;
        //else dflag = 1;
    }else strcpy(mode, args[3]);
    //printf("***%s***\n", mode);
    do_mv(file, args[2], mode);
    //do_mv(file, args[2], mode, dflag);
    return 1;
}

int do_mv(fcb *file, char *filename, char *mode){
    if (strcmp(mode, "-b") == 0 || strcmp(mode, "-f") == 0 || strcmp(mode, "-i") == 0 || strcmp(mode, "-wa") == 0) change_fullname(file, filename, mode);
    //else if (dflag) change_file_direction(file, filename, mode);
    return 0;
}

