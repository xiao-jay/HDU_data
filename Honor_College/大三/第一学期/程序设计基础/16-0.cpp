//����һ���ļ�����ͳ�Ƹ��ļ��ﵥ�ʵĸ��� 
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main()
{
	FILE *fp;
	char ch;
	int count=0;
	int bAlpha=0;	//��־λ��ǰһ���ַ��Ƿ���Ӣ����ĸ 
	char filename[20];
	
	printf("enter a file name:");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}
	while((ch=fgetc(fp))!=EOF)
	{	
		if(isalpha(ch))
		{
			if(bAlpha==0)
				count++;
			bAlpha=1;
		}
		else
			bAlpha=0;
	}	
	
	//����ȷ���ļ������жϷ��������жϣ����ȡ 
//	while(!feof(fp)) 
//	{	
//		ch=fgetc(fp);
//		if(isalpha(ch))
//		{
//			if(bAlpha==0)
//				count++;
//			bAlpha=1;
//		}
//		else
//			bAlpha=0;
//	}
	
	printf("\nword count=%d\n",count);
	fclose(fp);
	return 0;
}
