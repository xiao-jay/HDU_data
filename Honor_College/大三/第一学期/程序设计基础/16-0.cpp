//输入一个文件名，统计该文件里单词的个数 
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main()
{
	FILE *fp;
	char ch;
	int count=0;
	int bAlpha=0;	//标志位：前一个字符是否是英文字母 
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
	
	//不正确的文件结束判断方法：先判断，后读取 
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
