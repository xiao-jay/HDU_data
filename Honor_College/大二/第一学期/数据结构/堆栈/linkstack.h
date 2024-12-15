typedef int Status;
typedef char ElemType;
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define OK 1

typedef struct Stack_Node
{
    ElemType data;
    struct Stack_Node *next;
} NODE, *PNODE;

typedef struct stack
{
    PNODE front;
    PNODE rear;
} STACK, *PSTACK;

PNODE initstack(void)
{
    PNODE s = (PNODE)malloc(sizeof(NODE));
    s->next = NULL;
    return s;
}

void push(PNODE s, ElemType x)
{
    PNODE p = (PNODE)malloc(sizeof(NODE));
    p->data = x;
    p->next = s->next;
    s->next = p;
}

ElemType pop(PNODE s, ElemType *x)
{
    PNODE p = s->next;
    *x = p->data;
    s->next = p->next;
    free(p);
    return (*x);
}

//队列的初始化
/*
void initque(STACK pS)
{
pS.front = pS.rear =(NODE*)malloc(sizeof(NODE));
pS.front = NULL;
}
*/

PSTACK initque(void)
{
    PSTACK pS = (PSTACK)malloc(sizeof(STACK));
    pS->rear = (PNODE)malloc(sizeof(NODE));
    pS->front = pS->rear;
    pS->rear->next = NULL;
    return pS;
}

Status isEmpty(PSTACK Q)
{
    if (Q->front == Q->rear)
        return TRUE;
    else
        return FALSE;
}

void Insert_Stack(PSTACK Q, ElemType e)
{
    PNODE p = (PNODE)malloc(sizeof(NODE));
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

void Delete_LinkStack(PSTACK Q, int *x)
{
    PNODE p;
    while (Q->front)
    {
        p = Q->front;
        Q->front = Q->front->next;
        free(p);
    }
    return;
}