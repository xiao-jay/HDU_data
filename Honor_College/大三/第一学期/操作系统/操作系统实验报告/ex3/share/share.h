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

#define MEM_SIZE 1024
#define KEY 1111

sem_t *recv_1, *reply_1;
sem_t *recv_2, *reply_2;

int shmid;
void *shmp;
void init() {
	recv_1 = sem_open("recv_1", O_CREAT, 0666, 0);
	recv_2 = sem_open("recv_2", O_CREAT, 0666, 0);
	reply_1 = sem_open("reply_1", O_CREAT, 0666, 0);
	reply_2 = sem_open("reply_2", O_CREAT, 0666, 0);
	
	shmid = shmget(KEY, MEM_SIZE, 0666|IPC_CREAT);
	if (shmid < 0) {
		printf("创建共享内存出错！\n");
		exit(-1);
	}
	shmp = shmat(shmid, NULL, 0);
	if ((long long int)shmp == -1) {
		printf("映射内存出错！\n");
		exit(-1);
	}
}
