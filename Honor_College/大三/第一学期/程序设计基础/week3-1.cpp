#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,n1,n2;
	int i;
	
	for(n=4;;n=n+2)	//�����е�ż��������֤ 
	{
		for(n1=2;n1<=n/2;n1++)	//��һ��ż���ֽ�������� 
		{
			for(i=2;i<n1;i++)	//�жϵ�һ�����Ƿ����� 
				if(n1%i==0)
					break;
			if(i==n1)			//��һ����������	
			{
				n2=n-n1;		
				for(i=2;i<n2;i++)	//�жϵڶ������Ƿ����� 
					if(n2%i==0)
						break;
				if(n2==i)			//�ڶ����������� 
				{
					printf("%d=%d+%d\n",n,n1,n2);	//����ֽ�ʽ�� 
					break;			//ֻ���ҵ�һ���ֽ�ķ��� 
				}
			}
		}
						
		if(n1>n/2)		//һ��ż��û���ҵ��ֽ��ʽ�� 
		{			
			printf("Goldbach is wrong!!!\n");
			printf("The even number=%d\n",n);
			break;		//������һ��ѭ������������֤����ż�� 
		}		
	}
				
	return 0;
}
