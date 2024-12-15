#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#include <pthread.h>
#include <semaphore.h>
#include <glob.h>

pthread_t a, b;

char s[100];
void *A() {
	while (1) {
		printf("输入：");
		fflush(stdout);
		scanf("%s", s);
		if(!strcmp(s, "exit")) {
			pthread_cancel(b);
			break;
		}
	}
}
void *b() {
	while (1) {
		Sleep(1);
		printf("\r收到消息\n输入：");
		
	}
}

int main() {
	
}
