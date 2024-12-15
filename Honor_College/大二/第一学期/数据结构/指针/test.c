#include <stdio.h>
#include <stdlib.h>
void test(int *a)
{
	(*a)--;
}
int main()        
{
	int a;
	a=5;
	test(&a);
	printf("%d",a);
	return 0;
}