#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define BLOCK_SIZE      1024
#define DISK_SIZE       1048576
#define END             65535
#define FREE            0
#define ROOT_BLOCK_NUM  2
#define MAX_OPENFILE    10
#define ATTR_DIR        0
#define ATTR_FILE       1
#define SYS_FILENAME    "./file_system_data"
#define NAME_LENGTH     32
#define PATH_LENGTH     128
#define WRITE_SIZE      20 * BLOCK_SIZE

#define highbit(x) (63 - __builtin_clzll(x))

#define BLOCK_NUM       1024
#define SYS_PATH        "./fsfile"
#define ROOT            "/"     


#define DELIM           "/"
#define FOLDER_COLOR    "\e[1;34m"
#define DEFAULT_COLOR   "\e[0m"


typedef struct BLOCK0 {
    char information[200];
    unsigned short root;
    unsigned short start_block;
} block0;

typedef struct FCB {
    char filename[8];
    char exname[4];
    unsigned char attribute;    
    unsigned short time; 
    unsigned short date;
    unsigned short first;
    unsigned long length;
    char free;
} fcb;

typedef struct FAT {
    unsigned short id;
} fat;

typedef struct USEROPEN {
    fcb open_fcb;
    
    char dir[80];
    int count;
    char fcb_state;
    char free;
} useropen;

typedef struct FAT_BITMAP {
    unsigned long long bits;
} fat_bitmap;

unsigned char *fs_head;       
useropen openfile_list[MAX_OPENFILE];   
int curdir;
char current_dir[80];
unsigned char *start;

int start_sys(void);

int my_format(char **args, int argc);
int do_format(void);

int my_cd(char **args, int argc);
int do_cd(char *path);

int my_mkdir(char **args, int argc);
int do_mkdir(const char *abspath);

int my_rmdir(char **args, int argc);
int do_rmdir(fcb *dir);

int my_ls(char **args, int argc);
int do_ls(int first, int mode);

int my_create(char **args, int argc);
int do_create(const char *parpath, const char *filename);

int my_rm(char **args, int argc);
int do_rm(fcb *file);

int my_open(char **args, int argc);
int do_open(char *path);

int my_close(char **args, int argc);
int do_close(int fd);

int my_write(char **args, int argc);
int do_write(int fd, char *content, size_t len, int wstyle);

int my_read(char **args, int argc);
int do_read(int fd, int len, char *text);

int my_showfat(char **args, int argc);
int do_showfat(int mode);

int my_help(char **args, int argc);

int my_exitsys(char **args, int argc);

fcb *fcb_cpy(fcb *des, fcb *src);
fcb *find_fcb(const char *path);
fcb *find_fcb_r(char *token, int first);
fcb *get_fcb(fcb *cur);
int set_fcb(fcb *f, const char *filename, const char *exname, unsigned char attr, unsigned short first,
            unsigned long length, char ffree);

int get_bits(void);
int set_bits(int first);
    
int get_block(void);
int free_block(int first);
int set_block(int first);

char *get_abspath(char *abspath, const char *relpath);
char *get_fullname(char *fullname, fcb *f);
int get_useropen(void);

int init_folder(int first, int second);
int init_useropen(void);


unsigned short get_time(struct tm *timeinfo);
unsigned short get_date(struct tm *timeinfo);
char *trans_date(char *sdate, unsigned short date);
char *trans_time(char *stime, unsigned short time);

char *my_strtok(char *str, const char *ctr);

void *change_fullname(fcb *f, char *changename, char *mode);
int my_mv(char **args, int argc);
int do_mv(fcb *file, char *filename, char *mode);
//int do_mv(fcb *file, char *filename, char *mode, int dflag);


