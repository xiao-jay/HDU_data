#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	printf("请输入修改的主机名称：");
	char name[100];
	fgets(name, 100, stdin);
	syscall(603, name, strlen(name));
}
