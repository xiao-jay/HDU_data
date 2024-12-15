#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node
{
	char word[20];
	//此处20只是一个单词的普遍上限
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
	//创建新头 
	split(head,argv[1]);
	//筛选出字符串 
	sortbycount(head);
	//冒泡排序 
	stopword(head);
	//停用词 
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
	}//首先询问指针p是不是空的，如果指针p非空，那么返回 -1 
	p->next=NULL;
	// 新创建的指针p的地址数据是随机的（如果不做这一步会造成非法访问内存的情况） 
	p->count=0;
	//这个新地址将要存放数，此时的计数为0 
	return p;
}

int isnew(node *head,char w[20])
{
	node *p=head->next;
	int flag=1;
	while(p!=NULL)
	{
		if(strcmp(p->word,w)==0)
		//strucp函数的结果0 意思是：两个字符串是一样的 
		{
			p->count++;
			return 0;
		}
		else
			p=p->next;
	}
	return 1;
	//原因：flag=1 
}

void split(node *head,char *filename)
//挑选出一个个字符，直到读到第一个标点符号，再把之前所有的字符组成字符串输出 
{
	node *p=head;
	//head=NULL; *p=head
	char ch;
	//读入一个字符 
	char w[20];
	//读入一个字符串 
	int i=0,flag=0;
	//flag是一个标志符，作为简便判断if的条件 
	FILE *fp;
	//打开file文件.txt 
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("Error:open file1 failed!\n");
		exit(-1);
	}
	while(~(ch=fgetc(fp)))
	//fgetc=file+getchar 
	{
		ch=tolower(ch);
		//tolower函数位于ctype头文件中; 作用是：把大写字母变成小写，其他书写保持不变 
		if(isalpha(ch))
		//isalpha函数位于ctype头文件中；作用是：判断是不是字符 
		{
			w[i]=ch;
			//用变量i来标记字符串的位置 
			i++;
			flag=1;
		}
		else if(flag==1)
		//else表示：扫描到的不是字符，而是标点或者空格 
		{
			w[i]='\0';
			//只会输出到这里停止了
			//（'\0'表示字符串不输出了 终止） 
			if(isnew(head,w))
			//如果扫描出来的新字符串是一个新的单词 
			{
				p->next=newnode();
				p=p->next;
				strcpy(p->word,w);
				//strucp函数位于ctype头文件中  作用是：进行字符串的拷贝复制
				//两个字符数组（字符串）的拷贝复制不能直接用等号连接 
				p->count++; 
			}
			i=0;
			//让i重新指回第一个指针的位置（重新读）；恢复出厂设置 
			strcpy(w,"\0");
			flag=0;
		}  //flag 只有当上一个是字母的时候才走else；否则不会进行else if的判断 
	}      //eg： do. I can fly.  这句话中可能由于人为因素I前多了一个空格 这样的话会有连续两个非字符串的扫描 
	fclose(fp);
}

void sortbycount(node *head)
//bubblesort 冒泡排序 ；按照count由大到小输出对应的字符串（单词）
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
//筛选出停用词 不需要把它们列入统计的范围之中 
{
	char word[27][20]={"a","an","the","and","am","is","of","for","very","through","because","on","should","between","any","that","from","although","below","while","only","into","onto","until","some","before","each"};
	//创造一个二维数组 
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
		}   //p指向第一个 判断第二个是不是停用词 如果是的话把p->next删除，再用指针q指向指针p的下下个位置
	}    
}           

void print(node *head,char *filename)
{
	FILE *fp;
	int total=0,i=1;
	node *p=head->next;
	//total 指这篇文章共有多少个单词
	if((fp=fopen(filename,"w"))==NULL)
	{
		printf("Error:open file2 failed!\n");
		exit(-1);
	}
	while(p)
	//等价于while(p!=NULL) 
	{
		total+=p->count;
		//把一个个单词的个数加到total中 
		p=p->next;
		//遍历整个链表 
	}
	p=head->next;
	printf("%d",total); 
	while(p)
	{
		fprintf(fp,"%-3d %-20s%3d %.2f%%\n",i,p->word,p->count,(float)p->count/(float)total*100.0);
		//%nd表示输出n个字符的十进制整数；%ns表示输出n个单位长度的字符串；负号“-”代表左对齐 
		//%%在现实等于%，如果只写一个%程序会吞掉的 
		p=p->next;
		i++;//i是序数 代表了每个单词在链表中的位置 
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
	}//1、让指针q指向下个p  2、释放指针p  3、让p、q指针指向下一个同一个位置 : 遍历链表 
}
