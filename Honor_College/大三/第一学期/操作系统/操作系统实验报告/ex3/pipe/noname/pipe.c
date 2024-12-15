#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <fcntl.h>
#define N 1010

char raw[N], buf[N];
void clean() {
	sem_unlink("Mutex");

	sem_unlink("send_1");
	sem_unlink("send_2");
	sem_unlink("send_3");

	sem_unlink("receive_1");
	sem_unlink("receive_2");
	sem_unlink("receive_3");
}

void strip(char *in, char *out) {
	for (; *in == ' '; ++in);
	strncpy(out, in, N);
	// printf("%d\n", strlen(out));
	char *p = out + strlen(out);
	if (*(p - 1) == '\n') *(--p) = '\0';
	for (; p > out && *(p - 1) == ' ';) *(--p) = '\0';
}

void readline(char *str) {
	fgets(raw, N, stdin);
	// strip(raw, str);
	strncpy(str, raw, N);
}

int main()
{
	int fd[2], pipe_num;
	
	sem_t *Mutex;
	sem_t *send_1, *send_2, *send_3;
	sem_t *receive_1, *receive_2, *receive_3;
	pid_t pid_1, pid_2, pid_3;
	
	clean();

	Mutex = sem_open("Mutex", O_CREAT, 0666, 1);

	send_1 = sem_open("send_1", O_CREAT, 0666, 1);
	send_2 = sem_open("send_2", O_CREAT, 0666, 1);
	send_3 = sem_open("send_3", O_CREAT, 0666, 1);

	receive_1 = sem_open("receive_1", O_CREAT, 0666, 0);
	receive_2 = sem_open("receive_2", O_CREAT, 0666, 0);
	receive_3 = sem_open("receive_3", O_CREAT, 0666, 0);

	pipe_num = pipe(fd);
    if(pipe_num == -1){
		printf("pipe create error\n");
		return 1;
    }
	pid_1 = fork();
	if(pid_1 > 0) {
		pid_2 = fork();
		if(pid_2 > 0) pid_3 = fork();
	}
	if(pid_1 < 0 || pid_2 < 0 || pid_3 <0) {
		clean();
		printf("fork error\n");
		return 2;
	}

	if(pid_1 == 0) {
		sem_wait(send_1);
		sem_wait(Mutex);
		printf("pid:%d 进程1写入数据：", getpid());
		readline(buf);
		write(fd[1], buf, strlen(buf));
		close(fd[1]);
		sleep(1);
		sem_post(Mutex);
		sem_post(receive_1);
	}
	else if(pid_2 == 0) {
		sem_wait(send_2);
		sem_wait(Mutex);
		printf("pid:%d 进程2写入数据：", getpid());
		readline(buf);
		write(fd[1], buf, strlen(buf));
		close(fd[1]);
		sleep(1);
		sem_post(Mutex);
		sem_post(receive_2);
	}
	else if(pid_3 == 0) {
		sem_wait(send_3);
		sem_wait(Mutex);
		printf("pid:%d 进程3写入数据：", getpid());
		readline(buf);
		write(fd[1], buf, strlen(buf));
		close(fd[1]);
		sleep(1);
		sem_post(Mutex);
		sem_post(receive_3);
	}
	else {
		sem_wait(receive_1);
		sem_wait(receive_2);
		sem_wait(receive_3);
		sem_wait(Mutex);
		read(fd[0], buf, 150);
		printf("pid:%d 父进程接收数据: \n%s", getpid(), buf);
		close(fd[0]);
		sleep(1);
		sem_post(Mutex);
		sem_post(send_1);
		sem_post(send_2);
		sem_post(send_3);
	}
}
