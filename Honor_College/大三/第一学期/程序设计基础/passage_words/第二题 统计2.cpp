#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{
	char word[20];
	//�˴�20ֻ��һ�����ʵ��ձ�����
	struct Node *next;
	int count;
}node;

node *newnode();	
int isnew(node *head,char ch[20]);
void split(node *head,char *filename);
void sortbycount(node *head);
void stopword(node *head);
void print(node *head,char *filename);
void destory(node *p); 

int main(int argc, char * argv[])
{
	node *head;
	char w[20];
	head=newnode();
	//������ͷ 
	split(head,argv[1]);
	//ɸѡ���ַ��� 
	sortbycount(head);
	//ð������ 
	stopword(head);
	//ͣ�ô� 
	print(head,argv[2]);
	destory(head);
	
	return 0;
}

node *newnode()
{
	node *p;
	p=(node *)malloc(sizeof(node));
	if(p==NULL)
	{
		printf("Error:out of memory!\n");
		exit(-1);
	}//����ѯ��ָ��p�ǲ��ǿյģ����ָ��p�ǿգ���ô���� -1 
	p->next=NULL;
	// �´�����ָ��p�ĵ�ַ����������ģ����������һ������ɷǷ������ڴ������� 
	p->count=0;
	//����µ�ַ��Ҫ���������ʱ�ļ���Ϊ0 
	return p;
}

int isnew(node *head,char w[20])
{
	node *p=head->next;
	int flag=1;
	while(p!=NULL)
	{
		if(strcmp(p->word,w)==0)
		//strucp�����Ľ��0 ��˼�ǣ������ַ�����һ���� 
		{
			p->count++;
			return 0;
		}
		else
			p=p->next;
	}
	return 1;
	//ԭ��flag=1 
}

void split(node *head,char *filename)
//��ѡ��һ�����ַ���ֱ��������һ�������ţ��ٰ�֮ǰ���е��ַ�����ַ������ 
{
	node *p=head;
	//head=NULL; *p=head
	char ch;
	//����һ���ַ� 
	char w[20];
	//����һ���ַ��� 
	int i=0,flag=0;
	//flag��һ����־������Ϊ����ж�if������ 
	FILE *fp;
	//��file�ļ�.txt 
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("Error:open file1 failed!\n");
		exit(-1);
	}
	while(~(ch=fgetc(fp)))
	//fgetc=file+getchar 
	{
		ch=tolower(ch);
		//tolower����λ��ctypeͷ�ļ���; �����ǣ��Ѵ�д��ĸ���Сд��������д���ֲ��� 
		if(isalpha(ch))
		//isalpha����λ��ctypeͷ�ļ��У������ǣ��ж��ǲ����ַ� 
		{
			w[i]=ch;
			//�ñ���i������ַ�����λ�� 
			i++;
			flag=1;
		}
		else if(flag==1)
		//else��ʾ��ɨ�赽�Ĳ����ַ������Ǳ����߿ո� 
		{
			w[i]='\0';
			//ֻ�����������ֹͣ��
			//��'\0'��ʾ�ַ���������� ��ֹ�� 
			if(isnew(head,w))
			//���ɨ����������ַ�����һ���µĵ��� 
			{
				p->next=newnode();
				p=p->next;
				strcpy(p->word,w);
				//strucp����λ��ctypeͷ�ļ���  �����ǣ������ַ����Ŀ�������
				//�����ַ����飨�ַ������Ŀ������Ʋ���ֱ���õȺ����� 
				p->count++; 
			}
			i=0;
			//��i����ָ�ص�һ��ָ���λ�ã����¶������ָ��������� 
			strcpy(w,"\0");
			flag=0;
		}  //flag ֻ�е���һ������ĸ��ʱ�����else�����򲻻����else if���ж� 
	}      //eg�� do. I can fly.  ��仰�п���������Ϊ����Iǰ����һ���ո� �����Ļ����������������ַ�����ɨ�� 
	fclose(fp);
}

void sortbycount(node *head)
//bubblesort ð������ ������count�ɴ�С�����Ӧ���ַ��������ʣ�
{
	node *tail=NULL;
	node *nextp,*p=head->next;
	node *prep=head;

	while(head->next != tail)
	{
		prep=head;
		p=head->next;
		while(p->next!=tail)
		{
			if(p->count < p->next->count)
			{
				nextp=p->next;
				prep->next = p->next;
				p->next = p->next->next;
				prep->next->next=p;
				p=nextp;
			}
			p=p->next;
			prep=prep->next;
		}
		tail=p;
	}
}

void stopword(node *head)
//ɸѡ��ͣ�ô� ����Ҫ����������ͳ�Ƶķ�Χ֮�� 
{
	char word[27][20]={"a","an","the","and","am","is","of","for","very","through","because","on","should","between","any","that","from","although","below","while","only","into","onto","until","some","before","each"};
	//����һ����ά���� 
	int i=0;
	node *p,*q;
	for(i=0;i<7;i++)
	{
		p=head;
		while(p->next)
		{
			if(strcmp(p->next->word,word[i])==0)
			{
				q=p->next->next; 
			    free(p->next);	
				p->next=q;
			}
			p=p->next;
		}   //pָ���һ�� �жϵڶ����ǲ���ͣ�ô� ����ǵĻ���p->nextɾ��������ָ��qָ��ָ��p�����¸�λ��
	}    
}           

void print(node *head,char *filename)
{
	FILE *fp;
	int total=0,i=1;
	node *p=head->next;
	//total ָ��ƪ���¹��ж��ٸ�����
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("Error:open file2 failed!\n");
		exit(-1);
	}
	while(p)
	//�ȼ���while(p!=NULL) 
	{
		total+=p->count;
		//��һ�������ʵĸ����ӵ�total�� 
		p=p->next;
		//������������ 
	}
	p=head->next;
	printf("%d",total); 
	while(p)
	{
		fprintf(fp,"%-3d %-20s%3d %.2f%%\n",i,p->word,p->count,(float)p->count/(float)total*100.0);
		//%nd��ʾ���n���ַ���ʮ����������%ns��ʾ���n����λ���ȵ��ַ��������š�-����������� 
		//%%����ʵ����%�����ֻдһ��%������̵��� 
		p=p->next;
		i++;//i������ ������ÿ�������������е�λ�� 
	}
	fprintf(fp,"total word count = %d",total);
}

void destory(node *p)
{
	while(p)
	{
		node *q=p->next;
		free(p);
		p=q;
	}//1����ָ��qָ���¸�p  2���ͷ�ָ��p  3����p��qָ��ָ����һ��ͬһ��λ�� : �������� 
}
