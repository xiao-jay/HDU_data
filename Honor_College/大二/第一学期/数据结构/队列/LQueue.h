#include "HeadFile.h"
typedef int QElemType;

typedef int Status;
typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue *Q)
{
	Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(OVERFLOW);
	Q->front->next=NULL;
	return OK;
}

Status DestroyQueue(LinkQueue *Q)
{
	while(Q->front)
	{
		Q->rear=Q->front->next;
		free(Q->front);
		Q->front=Q->rear;
	}
	return OK;
}

Status EnQueue(LinkQueue *Q,QElemType e)
{
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q->rear->next=p;
	Q->rear=p;
	return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e)
{
	if(Q->front==Q->rear) return ERROR;
	QueuePtr p=Q->front->next;
	*e=p->data;
	Q->front->next=p->next;
	if(Q->rear==p) Q->rear=Q->front;
	free(p);
	return OK;
}

void ShowQueue(LinkQueue *Q)
{
	QueuePtr temp = Q->front;
	while(temp != Q->rear)
	{
		temp = temp->next;
		printf("%d ",temp->data);
	}
	puts("");
}