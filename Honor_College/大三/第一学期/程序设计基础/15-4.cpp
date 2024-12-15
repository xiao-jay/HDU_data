//新建链表节点插到链表尾 
#include<stdio.h>
#include<stdlib.h>

struct node 
{
	int number;
	struct node *next;
};

struct node *create()
{
	int x;
	struct node *head,*p;
	head=NULL;
	while(scanf("%d",&x) && x!=-1)
	{
		p = (struct node *)malloc(sizeof(struct node));
		if(p==NULL)
		{
			printf("memory allocation failed\n!!!");
			exit(-1);
		}
		p->number=x;
		if(head==NULL) //empty link
		{
			head = p;
			p->next=NULL;
		}
		else
		{
			p->next=head;
			head = p;
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
		printf("%d\n",p->number);
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

struct node *insert(struct node *head,int x)
{
	struct node *p1,*p2,*p;
	p=(struct node *)malloc(sizeof(struct node));
	p->number=x;	
	p1=head;
	p2=NULL;
	while(p1!=NULL && p1->number>x)
	{
		p2=p1;
		p1=p1->next;
	}

	if(p1==head)		//insert before head
	{
		p->next=head;
		head=p;
	}
	else if(p1==NULL)	//insert after tail
	{
		p2->next=p;
		p->next=NULL;
	}
	else				//insert in middle
	{	
		p->next=p1;
		p2->next=p;
	}

	return head;
}

int main()
{
	struct node *head;
	int x;
	
	head=create();
	show(head);	
	printf("enter inserted x:");
	scanf("%d",&x);
	head=insert(head,x);
	show(head);	
	freelink(head);		
	return 0;
}
