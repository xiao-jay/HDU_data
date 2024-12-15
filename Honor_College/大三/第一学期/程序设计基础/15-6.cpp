//创建链表：新节点插入链表尾 
#include<stdio.h>
#include<stdlib.h>
struct node
{
	int num;
	struct node *next;
};


struct node *create()
{
	int x;
	struct node *head,*tail,*p;
	
	head=NULL;tail=NULL;
	while(scanf("%d",&x) && x!=-1)
	{
		p=(struct node *)malloc(sizeof(struct node));
		p->num = x;
		if(head==NULL)
		{
			p->next=NULL;
			head=p;
			tail=p;
		}
		else
		{
			tail->next=p;
			p->next=NULL;
			tail = p;
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
		printf("%d ",p->num);
		p = p->next;	
	}	
	printf("\n");
}

void freelink(struct node *head)
{
	struct node *p;
	p=head;
	while(p!=NULL)
	{
		head = p->next;
		free(p);
		p=head;
	}
}

struct node *deletenode(struct node *head,int x)
{
	struct node *p1,*p2;
	
	p1=head;p2=NULL;
	while(p1!=NULL && p1->num!=x)
	{		
		p2=p1;	
		p1=p1->next;
	}

	if(p1==NULL)
			return head;	
	if(p1==head)		//delete head node
	{
		head=head->next;
		free(p1);
		return head;
	}
	else	
	{
		p2->next=p1->next;
		free(p1);
		return head;
	}	
}

int main()
{
	struct node *head;
	int x;
	head = create();
	show(head);
	freelink(head);
	return 0;
}
