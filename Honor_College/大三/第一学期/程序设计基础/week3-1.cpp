#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,n1,n2;
	int i;
	
	for(n=4;;n=n+2)	//对所有的偶数进行验证 
	{
		for(n1=2;n1<=n/2;n1++)	//对一个偶数分解成两个数 
		{
			for(i=2;i<n1;i++)	//判断第一个数是否素数 
				if(n1%i==0)
					break;
			if(i==n1)			//第一个数是素数	
			{
				n2=n-n1;		
				for(i=2;i<n2;i++)	//判断第二个数是否素数 
					if(n2%i==0)
						break;
				if(n2==i)			//第二个数是素数 
				{
					printf("%d=%d+%d\n",n,n1,n2);	//输出分解式子 
					break;			//只需找到一个分解的方法 
				}
			}
		}
						
		if(n1>n/2)		//一个偶数没有找到分解的式子 
		{			
			printf("Goldbach is wrong!!!\n");
			printf("The even number=%d\n",n);
			break;		//跳出第一重循环，无需再验证其它偶数 
		}		
	}
				
	return 0;
}
