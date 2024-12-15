#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "file_system.h"

#define MAX_CMD_LEN 128
#define MAX_CMD_NUM 14
#define MAX_HOSTNAME_LEN 128


char *builtin_str[] = {
        "format",
        "cd",
        "mkdir",
        "rmdir",
        "ls",
        "create",
        "rm",
        "open",
        "close",
        "write",
        "read",
        "showfat",
        "help",
        "exit"
};

int (*builtin_func[])(char **, int) = {
        &my_format,
        &my_cd,
        &my_mkdir,
        &my_rmdir,
        &my_ls,
        &my_create,
		&my_rm,
        &my_open,
        &my_close,
        &my_write,
        &my_read,
        &my_showfat,
        &my_help,
        &my_exitsys
};

char *args[MAX_CMD_NUM];
int argc;

char cmdStr[MAX_CMD_LEN];
char tmpStr[MAX_CMD_LEN];
char hostname[MAX_HOSTNAME_LEN];

void strip(char *in, char *out);
void get_cmd();
int parse_cmd();
void do_cmd();

int main() {
    int status;
    
    start_sys();
    
    gethostname(hostname, MAX_HOSTNAME_LEN);

    do {
        printf("\e[1m\e[032m%s:\e[1m\e[034m%s\e[0m$ ", hostname, current_dir);

        get_cmd();
        status = parse_cmd();
    } while (status);
    return 0;
}

void strip(char *in, char *out) {
	for (; *in == ' '; ++in);
	strncpy(out, in, MAX_CMD_LEN);
	char *p = out + strlen(out);
	if (*(p - 1) == '\n') *(--p) = '\0';
	for (; p > out && *(p - 1) == ' ';) *(--p) = '\0';
}

void get_cmd() {
    fgets(tmpStr, MAX_CMD_LEN, stdin);
    strip(tmpStr, cmdStr);
}

int parse_cmd() {
    if (strlen(cmdStr) == 0) return 1;
    argc = 1; 
    args[0] = strtok(cmdStr, " ");
    while (args[argc] = strtok(NULL, " "))
        ++argc;

    for (int i = 0; i < MAX_CMD_NUM; ++i) 
        if (!strcmp(args[0], builtin_str[i])) {
            return (*builtin_func[i])(args, argc);
        }

    fprintf(stderr, "no such command\n");
    
    return 1; 
}
