#include "share.h"
#define N (MEM_SIZE >> 1)
pthread_t S, R;

char buf[N], tmp[N], tmp2[N], tmp3[N];
void strip(char *in, char *out) {
	for (; *in == ' '; ++in);
	strncpy(out, in, N);
	// printf("%d\n", strlen(out));
	char *p = out + strlen(out);
	if (*(p - 1) == '\n') *(--p) = '\0';
	for (; p > out && *(p - 1) == ' ';) *(--p) = '\0';
}

void *send(void *arg) {
	while (1) {
		printf("发送：");
		fflush(stdout);
		fgets(buf, N, stdin);
		memcpy(shmp + N, buf, sizeof(buf));
		sem_post(recv_1);
		strip(buf, tmp);
		if (!strcmp(tmp, "exit")) {
			pthread_cancel(R);
			break;
		}
		sem_wait(reply_1);
		printf("发送成功！\n");
	}
}
void *recv(void *arg) {
	while (1) {
		sem_wait(recv_2);
		memcpy(tmp2, shmp, N * sizeof(char));
		printf("\r\t\t\t\t\t\t\t");
		strip(tmp2, tmp3);
		if(!strcmp(tmp3, "exit")){
			printf("\r对方终止会话\n");
			pthread_cancel(S);
			shmdt(shmp);
			shmctl(shmid, IPC_RMID, NULL);
			sem_unlink("reply_1");
			sem_unlink("reply_2");
			sem_unlink("recv_1");
			sem_unlink("recv_2");
			break;
		}
		printf("\r收到消息：%s", tmp2);
		memset(shmp, 0, N * sizeof(char));
		sem_post(reply_2);
		printf("发送消息：");
		fflush(stdout);
	}
}
int main() {
	pid_t pid = getpid();
	init();
	int res1 = 0, res2 = 0;
	res1 = pthread_create(&S, NULL, send, &pid);
    res2 = pthread_create(&R, NULL, recv, &pid);
    if (res1 || res2) {
    	printf("create pthread failed\n");
        return 1;
    }
    pthread_join(S, NULL);
    pthread_join(R, NULL);
    return 0;
}

