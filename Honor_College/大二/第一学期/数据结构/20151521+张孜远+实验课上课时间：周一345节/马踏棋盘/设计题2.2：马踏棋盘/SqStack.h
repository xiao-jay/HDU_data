#ifndef _SqStack_
#define _SqStack_
 
//˳��ջ�洢�ṹ
struct SqStack {	           	
    SElemType *base;     //����ַָ��
    int top;                      //ջ��ָ��
    int size;                     //�����ռ��С
};

//ջ�ĳ�ʼ��
void InitSqStack( SqStack &s, int m )
{
    s.top = 0;
    s.base = new SElemType[ m ];
    //����m������˳��ռ䣬����һ���յ�˳��ջ
    s.size = m;
}

//ջ����
void DestroySqStack( SqStack &s )
{
    delete[] s.base;
    s.top = 0;
    s.size = 0;	 
}

//�ÿ�ջ
void ClearSqStack( SqStack &s )
{
    s.top = 0;
}

//�б�ջ�Ƿ�Ϊ�� 
bool SqStackEmpty( SqStack s ) 
{
    return s.top == 0;
}

//��ջ��Ԫ�ظ���
int SqStackLength( SqStack s ) 
{
    return s.top;
}

//��ջ����ʱ��ȡջ��Ԫ�ص�ֵ
bool GetTop( SqStack s, SElemType &e ) 
{	
    if ( ! SqStackEmpty( s ) )
    {                        
        e = s.base[ s.top - 1 ];
        return true;
    }
    else 
        return false;
}

//��ջ������Ԫ��e��ջ��
void PushSqStack( SqStack &s, SElemType e )
{
    if ( s.top >= s.size )
    {	 //��ջ��������չ�ռ䡣
        SElemType *newbase;
        newbase = new SElemType[ s.size + 10 ];
        for ( int j = 0; j < s.top; j++ )  newbase[ j ] = s.base[ j ];   
        delete[] s.base;
        s.base = newbase;
        s.size += 10;
    }
    s.base[ s.top++ ] = e;
}

//��ջ�ǿ�ʱ����ջ
bool PopSqStack( SqStack &s, SElemType &e )
{
    if ( SqStackEmpty( s ) )
        return false;
    e = s.base[ --s.top ];
    return true;
}

#endif
