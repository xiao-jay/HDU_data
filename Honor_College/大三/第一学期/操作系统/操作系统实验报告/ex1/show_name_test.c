#include <unistd.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	struct utsname name;
	struct utsname *p = NULL;
	p = &name;
	syscall(601, p);
	printf("user:\n");
	printf("sysname: %s\n", name.sysname);
	printf("release: %s\n", name.release);
	printf("version: %s\n", name.version);
	return 0;
}
