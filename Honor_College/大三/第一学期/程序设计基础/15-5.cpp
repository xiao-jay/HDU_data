//用链表统计输入整数及其出现的次数 
#include<stdio.h>
#include<stdlib.h>

struct node 
{
	int number;
	int count;
	struct node *next;
};

struct node *find(struct node *head,int x)
{
	struct node *p;
	
	p=head;
	while(p!=NULL && p->number!=x)
		p=p->next;
	return p;
}

struct node *create()
{
	int x;
	struct node *head,*tail,*p,*fp;
	head=NULL;
	tail=NULL;
	while(scanf("%d",&x) && x!=-1)
	{
		fp=find(head,x);
		if(fp!=NULL)	
		{
			fp->count++;
		}
		else
		{
			p = (struct node *)malloc(sizeof(struct node));
			if(p==NULL)
			{
				printf("memory allocation failed\n!!!");
				exit(-1);
			}
			p->number=x;
			p->count=1;
			if(head==NULL) //第一个节点 
			{
				head = p;
				tail=p;
				p->next=NULL;
			}
			else			//插在链表尾 
			{
				tail->next=p;
				p->next=NULL;
				tail = p;
			}
		}				
	}		
	return head;
}

void show(struct node *head)
{
	struct node *p;
	p=head;
	while(p!=NULL)
	{
		printf("%d %d\n",p->number,p->count);
		p=p->next;
	}
}

void freelink(struct node *head)
{
	struct node *p;
	p=head;
	while(p!=NULL)
	{
		head=p->next;
		free(p);
		p=head;
	}
}

int main()
{
	struct node *head;
	head=create();
	show(head);
	freelink(head);
	
	return 0;
}
