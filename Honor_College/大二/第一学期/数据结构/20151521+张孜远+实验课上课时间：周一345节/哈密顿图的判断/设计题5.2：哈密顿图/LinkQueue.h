#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

//�����н��ṹ
struct LinkNode {
    QElemType data;
    LinkNode *next;
};

//��ͷ���������нṹ 
struct LinkQueue {
    LinkNode  *front;         //��ͷָ��
    LinkNode  *rear;          //��βָ��
};

//����һ���յ������С�
void InitQueue( LinkQueue &Q )
{
    Q.front = Q.rear = new LinkNode ;
    Q.front->next = NULL;
}//LinkQueue

//����������ա�
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

//�����нṹ���١�
void DestroyQueue( LinkQueue &Q )
{
    ClearQueue( Q );  //��Ա����Clear()�Ĺ������ͷ������е�����Ԫ�ؽ��
    delete Q.front;
    Q.front = Q.rear = NULL;
}

//���������Ƿ�Ϊ�գ���Ϊ�գ��򷵻�true�����򷵻�false��
bool QueueEmpty( LinkQueue Q ) 
{
    return Q.front == Q.rear;
}

//������������Ԫ�ظ�����
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

//ȡ�����ж�ͷԪ�ص�ֵ���Ⱦ������Ƕ��в��ա�
QElemType GetHead( LinkQueue &Q )
{
    return Q.front->next->data;
}

//ȡ�����ж�βԪ�ص�ֵ���Ⱦ������Ƕ��в��ա�
QElemType GetLast( LinkQueue &Q ) 
{
    return Q.rear->data;
}

//��������ӣ�����e����β��
void EnQueue( LinkQueue &Q, QElemType e )
{
    LinkNode *p;
    p = new LinkNode ;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
}

//�����г��ӡ��Ⱦ������Ƕ��в��ա�
bool DeQueue( LinkQueue &Q,QElemType &e )
{   
    if ( QueueEmpty( Q ) ) 
        return false;
    LinkNode *p = Q.front->next;
    Q.front->next = p->next;
    e = p->data;
    if ( p == Q.rear )
	    Q.rear = Q.front;  //�����Ӻ����Ϊ�գ����޸�Q.rear��
    delete p;
    return true;
}

#endif
