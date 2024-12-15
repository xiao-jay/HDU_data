//期末编程题：读取文本数据文件，计算并排序后，再保存 
#include<stdio.h>
#include<stdlib.h>
#define N 30
#define M 5
struct Singers
{
	int id;
	char name[10];         
   	float score[M];        //每位学生选手的M个评分
	float finalscore;      //每位学生选手的最终得分
};


int Read_info(struct Singers *sin,char *filename)
{
	int n=0;
	int i;
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("Open file error\n");
		exit(0);
	}
	while(fscanf(fp,"%d%s",&sin[n].id,sin[n].name)!=EOF)
	{
		for(i=0;i<M;i++)
			fscanf(fp,"%f",&sin[n].score[i]);
		n++;
	}
	fclose(fp);
	return n;
}

void calc(struct Singers *sin, int num)
{
	int i,j;
	int maxj,minj;
	
	for(i=0;i<num;i++)
	{
		maxj=minj=0;
		for(j=1;j<M;j++)
			if(sin[i].score[j]>sin[i].score[maxj])
				maxj=j;
			else if(sin[i].score[j]<sin[i].score[minj])
				minj=j;
		sin[i].finalscore=0.0;
		for(j=0;j<M;j++)
			if(j!=maxj && j!=minj)
				sin[i].finalscore += sin[i].score[j];
		sin[i].finalscore /= (M-2);
	}
}

void sort(struct Singers *sin, int num)
{
	int i,j;
	struct Singers temp;
	for(i=0;i<num-1;i++)
		for(j=0;j<num-1-i;j++)
			if(sin[j].finalscore>sin[j+1].finalscore)
			{
				temp=sin[j];
				sin[j]=sin[j+1];
				sin[j+1]=temp;
			}
}

void WriteToFile(struct Singers *sin,char *filename, int num)
{
	FILE *fp;	
	int i,j;
	
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("Create file failed!\n");
		exit(0);
	}
	for(i=0;i<num;i++)
	{
		fprintf(fp,"%10d%10s",sin[i].id,sin[i].name);
		for(j=0;j<M;j++)
			fprintf(fp,"%7.2f",sin[i].score[j]);
		fprintf(fp,"%7.2f\n",sin[i].finalscore);
	}
	fclose(fp);
}

int main()
{
    struct Singers sin[N];
	int count=0;     
	
	count = Read_info(sin,"d:\\score_file.txt");
	calc(sin, count);
	sort(sin, count);
    WriteToFile(sin,"d:\\score_file1.txt", count);
    return 0;
 }
