//用void *实现函数接口参数的统一 
#include<stdio.h>
enum Type{INT,DOUBLE};

void swap(void *p1,void *p2,enum Type type)
{
	if(type==INT)
	{	
		int temp;
		int *x,*y;
		x=(int *) p1;
		y=(int *) p2;
		temp=*x;
		*x=*y;
		*y=temp;
	}
	else if(type==DOUBLE)
	{	
		double temp;
		double *x,*y;
		x=(double *) p1;
		y=(double *) p2;
		temp=*x;
		*x=*y;
		*y=temp;
	}
}

int main()
{
	int a=3,b=4;
	double x=1.4,y=3.5;
	
	swap(&a,&b,INT);
	swap(&x,&y,DOUBLE);
	printf("a=%d,b=%d\n",a,b);
	printf("x=%f,y=%f\n",x,y);
	return 0;
}
