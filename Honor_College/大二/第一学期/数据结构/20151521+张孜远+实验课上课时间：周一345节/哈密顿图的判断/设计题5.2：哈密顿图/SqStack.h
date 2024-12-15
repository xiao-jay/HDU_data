#ifndef _SqStack_
#define _SqStack_
 
//顺序栈结构
struct SqStack {	           	
    SElemType *base;     //基地址指针
    int top;            //栈顶指针
    int size;           //向量空间大小
};

//栈的初始化，分配m个结点的顺序空间，构造一个空的顺序栈
void InitSqStack( SqStack &s, int m )
{
    s.top = 0;
    s.base = new SElemType[ m ];
    s.size = m;
}

//栈销毁
void DestroySqStack( SqStack &s )
{
    delete[] s.base;
    s.top = 0;
    s.size = 0;	 
}

//置空栈
void ClearSqStack( SqStack &s )
{
    s.top = 0;
}

//判别栈是否为空 
bool SqStackEmpty( SqStack s ) 
{
    return s.top == 0;
}

//求栈中元素个数
int SqStackLength( SqStack s ) 
{
    return s.top;
}

//取栈顶元素的值。先决条件是栈不空。
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

//入栈，若栈满，则先扩展空间。插入e到栈顶
void PushSqStack( SqStack &s, SElemType e )
{
    if ( s.top >= s.size )
    {	 //若栈满，则扩展空间。 
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

//出栈,先决条件是栈非空。
bool PopSqStack( SqStack &s, SElemType &e )
{
    if ( SqStackEmpty( s ) )
        return false;
    e = s.base[ --s.top ];
    return true;
}

#endif
