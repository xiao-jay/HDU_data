#include "share.h"

int main() {
	init();
	int fd = open(fifofile, O_WRONLY);
	sem_wait(send_1);
	sem_wait(Mutex);
	printf("pid:%d 进程1写入数据：", getpid());
	readline(buf);
	write(fd, buf, strlen(buf));
	close(fd);
	sleep(1);
	sem_post(Mutex);
	sem_post(receive_1);
}
