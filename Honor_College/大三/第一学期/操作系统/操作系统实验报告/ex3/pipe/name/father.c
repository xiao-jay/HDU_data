#include "share.h"

int main() {
	clean();
	init();
	mkfifo(fifofile, 0666);
	sem_post(send_1);
	sem_post(send_2);
	sem_post(send_3);
	int fd = open(fifofile, O_RDONLY);
	sem_wait(receive_1);
	sem_wait(receive_2);
	sem_wait(receive_3);
	sem_wait(Mutex);
	read(fd, buf, 150);
	printf("pid:%d 父进程接收数据: \n%s", getpid(), buf);
	close(fd);
	unlink(fifofile);
	sleep(1);
	sem_post(Mutex);
	sem_post(send_1);
	sem_post(send_2);
	sem_post(send_3);
}
