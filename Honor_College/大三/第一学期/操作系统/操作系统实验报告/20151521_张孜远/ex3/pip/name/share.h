#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#define N 1010
#define fifofile "./fifomy"

sem_t *Mutex;
sem_t *send_1, *send_2, *send_3;
sem_t *receive_1, *receive_2, *receive_3;
char raw[N], buf[N];
void readline(char *str) {
	fgets(raw, N, stdin);
	strncpy(str, raw, N);
}

void clean() {
	sem_unlink("Mutex");

	sem_unlink("send_1");
	sem_unlink("send_2");
	sem_unlink("send_3");

	sem_unlink("receive_1");
	sem_unlink("receive_2");
	sem_unlink("receive_3");
}

void init() {
	Mutex = sem_open("Mutex", O_CREAT, 0666, 1);

	send_1 = sem_open("send_1", O_CREAT, 0666, 0);
	send_2 = sem_open("send_2", O_CREAT, 0666, 0);
	send_3 = sem_open("send_3", O_CREAT, 0666, 0);

	receive_1 = sem_open("receive_1", O_CREAT, 0666, 0);
	receive_2 = sem_open("receive_2", O_CREAT, 0666, 0);
	receive_3 = sem_open("receive_3", O_CREAT, 0666, 0);
}

