#ifndef _SqStack_
#define _SqStack_
 
//˳��ջ�ṹ
struct SqStack {	           	
    SElemType *base;     //����ַָ��
    int top;            //ջ��ָ��
    int size;           //�����ռ��С
};

//ջ�ĳ�ʼ��������m������˳��ռ䣬����һ���յ�˳��ջ
void InitSqStack( SqStack &s, int m )
{
    s.top = 0;
    s.base = new SElemType[ m ];
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

//ȡջ��Ԫ�ص�ֵ���Ⱦ�������ջ���ա�
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

//��ջ����ջ����������չ�ռ䡣����e��ջ��
void PushSqStack( SqStack &s, SElemType e )
{
    if ( s.top >= s.size )
    {	 //��ջ��������չ�ռ䡣 
	    SElemType *newbase;
        newbase = new SElemType[ s.size + 10 ];
        for ( int j = 0; j < s.top; j++ ) 
            newbase[ j ] = s.base[ j ];   
        delete[] s.base;
        s.base = newbase;
	    s.size += 10;
    }
    s.base[ s.top++ ] = e;
}

//��ջ,�Ⱦ�������ջ�ǿա�
bool PopSqStack( SqStack &s, SElemType &e )
{
    if ( SqStackEmpty( s ) )
        return false;
    e = s.base[ --s.top ];
    return true;
}

#endif
