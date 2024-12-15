#include "errno.h"
#include "fcntl.h"
#include "semaphore.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/ipc.h"
#include "sys/sem.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "unistd.h"

#define BUF_MAX_SIZE 1024

char buf[BUF_MAX_SIZE];

int main() {
	int fd[2];
	int pipe_num = pipe(fd);
	int count = 0;
	int flags = fcntl(fd[1], F_GETFL);
	memset(buf, 1, sizeof(buf));
	int flag = 0;
	fcntl(fd[1], F_SETFL, flags | O_NONBLOCK);
	while (!flag) {
		int n = write(fd[1], buf, BUF_MAX_SIZE);
		if (n == -1) flag = 1;
		else ++count;
	}
	printf("%dKB\n", (count * BUF_MAX_SIZE) / 1024);
}
