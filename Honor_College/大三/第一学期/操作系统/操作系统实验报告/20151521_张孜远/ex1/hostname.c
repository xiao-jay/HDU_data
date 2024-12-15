#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	long flag = 0;
	printf("请输入修改的hostname：");
	char nodename[100];
	fgets(nodename,100,stdin);
	flag = syscall(337,nodename,strlen(nodename));
	//printf("Original hostname: Linux\n");
	printf("New hostname:%s\n",nodename);
}

