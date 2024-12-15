#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char sysname[100],release[100],version[100];
	syscall(336,sysname,release,version);
	printf("Original Sysname: Linux\n");
	printf("Original Version: 5.4.0-131-generic\n");
	printf("Original Release: #147~18.04.1-Ubuntu SMP Sat Oct 15 13:10:18 UTC 2022\n");
	printf("New Sysname:%s\nNew Release:%s\nNew Version:%s\n",sysname,release,version);
}

