#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
int main() 
{
	pid_t pid;
	char strin[100];
	int nicevalue = 3100;
	int flag = 2;
	int p = 0;
	int n = 0;
	int *prio = &p;
	int *nice = &n;
	while(1) {
		printf("输入0查看nice和prio，输入1修改nice和prio，输入其他值退出。\n");
		scanf("%d", &flag);
		if(flag != 0 && flag != 1) return 0;
        	printf("请输入pid：\n");
        	scanf("%d",&pid);
		if(flag == 1) {
			printf("请输入nice：\n");
                	scanf("%d", &nicevalue);
			if(nicevalue < -20 || nicevalue > 19){
				printf("nice值非法n");
				continue;
			}
		}
        	syscall(602, pid, flag, nicevalue, prio, nice);
        	printf("现在的nice为%d\n", n);
		printf("现在的prio为%d\n", p);

	}
}
