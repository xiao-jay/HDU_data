//用命令行实现：将一个文件内容追加到另一个文件末尾 
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc,char *argv[])
{
	FILE *fp1,*fp2;
	char ch;
	
	if(argc!=3)
	{
		printf("erroe argument count!\n");
		exit(0);
	}
	fp1=fopen(argv[2],"r");
	fp2=fopen(argv[1],"a");		//appended file 
	if(fp1==NULL || fp2==NULL)
	{
		printf("open file failed!\n");
		exit(0);
	}
	
	while((ch=fgetc(fp1))!=EOF)	
		fputc(ch,fp2);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
