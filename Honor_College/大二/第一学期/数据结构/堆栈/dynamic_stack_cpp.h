#include<stdio.h>
#include<stdlib.h>
typedef int Status;
typedef int SElemType;
#define stack_init_size 200
#define stack_increment 10
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define OK 1
typedef struct PosType
{
	int x;
	int y;
}PosType;
typedef struct SqStack
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;
Status GetTop(SqStack s,SElemType &e)
{
	if(s.top==s.base) return ERROR;
	e=*(s.top-1);
	return OK;
}
Status InitStack(SqStack &s)//构造一个空栈
{
	s.base=(SElemType *)malloc(stack_init_size * sizeof(SElemType));
	if(!s.base) return OVERFLOW;
	s.top=s.base;
	s.stacksize=stack_init_size;
	return OK;
}
Status Pop(SqStack &s,SElemType &e)//出栈
{
	if(s.top==s.base)
		return ERROR;
	e=*--s.top;
	return OK;
}
Status Push(SqStack &s,SElemType e)//入栈
{
	if(s.top-s.base>=s.stacksize){
		s.base=(SElemType *)realloc(s.base,(s.stacksize+stack_increment) *sizeof(SElemType));
	if(!s.base) exit(OVERFLOW);
	s.top=s.base+s.stacksize;
	s.stacksize+=stack_increment;
	}
	*s.top++=e;
	return OK;
}
Status StackEmpty(SqStack s)//是否空栈
{
	if(s.top==s.base) return OK;
	return OVERFLOW;
}
void StackClear(SqStack &s)
{
	SElemType temp;
	while(!StackEmpty(s)) Pop(s,temp);
}