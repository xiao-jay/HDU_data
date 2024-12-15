//�������ļ�ʾ������ȡһ�������������ļ�������󱣴浽�������ļ� 
#include<stdio.h>
#include<stdlib.h>
#define N 30
#define M 5
struct Singers
{
	int id;
	char name[10];         
   	float score[M];        //ÿλѧ��ѡ�ֵ�M������
	float finalscore;      //ÿλѧ��ѡ�ֵ����յ÷�
};


int Read_Binaryinfo(struct Singers *sin,char *filename)
{
	int n=0;
	int i;
	FILE *fp;
	fp=fopen(filename,"rb");
	if(fp==NULL)
	{
		printf("Open file error\n");
		exit(0);
	}		
	//����Ķ��ļ����� 
//	while(!feof(fp))
//	{
//		fread(&sin[0],sizeof(struct Singers),1,fp);
//		n++;
//	
//	}

	while(fread(&sin[n],sizeof(struct Singers),1,fp)==1)
		n++;
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

void WriteToBinaryFile(struct Singers *sin,char *filename, int num)
{
	FILE *fp;	
	int i,j;
	
	if((fp=fopen(filename,"wb"))==NULL)
	{
		printf("Create file failed!\n");
		exit(0);
	}	
	fwrite(sin,sizeof(struct Singers),num,fp);	//�����ṹ������һ��д���ļ� 
	//Ҳ��������ṹ������Ԫ��д���ļ� 
//	for(i=0;i<num;i++)
//		fwrite(&sin[i],sizeof(struct Singers),1,fp);
	fclose(fp);
}

int main()
{
    struct Singers sin[N];
	int count=0;     
	
	count = Read_Binaryinfo(sin,"d:\\score_file.dat");	//�������ļ������Ƕ������ļ� 
	calc(sin, count);
	sort(sin, count);
    WriteToBinaryFile(sin,"d:\\result.data", count);
    return 0;
 }
