#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

//链队列结点结构
struct LinkNode {
    QElemType data;
    LinkNode *next;
};

//带头结点的链队列结构 
struct LinkQueue {
    LinkNode  *front;         //队头指针
    LinkNode  *rear;          //队尾指针
};

//构造一个空的链队列。
void InitQueue( LinkQueue &Q )
{
    Q.front = Q.rear = new LinkNode ;
    Q.front->next = NULL;
}//LinkQueue

//将链队列清空。
void ClearQueue( LinkQueue &Q )
{
    LinkNode *p;
    while ( Q.front->next != NULL ) 
    {
        p = Q.front->next;
        Q.front->next = p->next;
        delete p;
    }
    Q.rear = Q.front;
}

//链队列结构销毁。
void DestroyQueue( LinkQueue &Q )
{
    ClearQueue( Q );  //成员函数Clear()的功能是释放链表中的所有元素结点
    delete Q.front;
    Q.front = Q.rear = NULL;
}

//判链队列是否为空，若为空，则返回true，否则返回false。
bool QueueEmpty( LinkQueue Q ) 
{
    return Q.front == Q.rear;
}

//返回链队列中元素个数。
int QueueLength( LinkQueue Q )
{
    int i = 0;
    LinkNode *p = Q.front->next;
    while ( p != NULL ) 
    {
        i++;
        p = p->next;
    }
    return i;
}

//取链队列队头元素的值。先决条件是队列不空。
QElemType GetHead( LinkQueue &Q )
{
    return Q.front->next->data;
}

//取链队列队尾元素的值。先决条件是队列不空。
QElemType GetLast( LinkQueue &Q ) 
{
    return Q.rear->data;
}

//链队列入队，插入e到队尾。
void EnQueue( LinkQueue &Q, QElemType e )
{
    LinkNode *p;
    p = new LinkNode ;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

//链队列出队。先决条件是队列不空。
bool DeQueue( LinkQueue &Q,QElemType &e )
{   
    if ( QueueEmpty( Q ) ) 
        return false;
    LinkNode *p = Q.front->next;
    Q.front->next = p->next;
    e = p->data;
    if ( p == Q.rear )
	    Q.rear = Q.front;  //若出队后队列为空，需修改Q.rear。
    delete p;
    return true;
}

#endif
