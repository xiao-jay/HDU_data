#ifndef _Hchess_
#define _Hchess_

//棋盘的位置坐标 
struct PosType {
    int x;     //行坐标
    int y;	//列坐标
};

//栈中数据元素类型 
struct SElemType {
    PosType seat;	//马在棋盘中的坐标位置
    int di;                   //从此点走到下一点的方向（0~7表示1~8个方向）
};

#include "SqStack.h"

//棋盘结构 
struct Hchess {
    int **chess;
    int row;       //行数
    int col;        //列数
};

//棋盘初始化 
void Initchess( Hchess &ch, int m, int n )
{
    int i, j;
    ch.row = m;
    ch.col = n;
    ch.chess = new int *[ ch.row ];
    for ( i = 0; i < ch.row; i++ )
	    ch.chess[ i ] = new int[ ch.col ];
    //用二维数组记录棋盘中的每一个点的坐标：先开一个数组，再对数组中的每个元素开一个数组
    //这就代表了棋盘中每个位置的坐标
    for ( i = 0; i < ch.row; i++ )
	    for ( j = 0; j < ch.col; j++ )
		    ch.chess[ i ][ j ] = 0;
     //将每个位置的坐标初始化为0	
}

//棋盘销毁
void Destroychess( Hchess &ch )
{
    //先销毁小数组，再销毁大数组
    for ( int i = 0; i < ch.row; i++ )
	    if ( ch.chess[ i ] != NULL )
		    delete [] ch.chess[ i ];
    if ( ch.chess != NULL )
	    delete [] ch.chess;
}

//按顺时针可选择的8个跳步方向 
PosType NextPos( PosType c, int d )
{
    //记录下一步可能到达的坐标位置相对于之前位置的坐标变化
    PosType direct[ 8 ] = { { 1, 2 }, { 2, 1 }, { 2, - 1 }, { 1, - 2 }, { - 1, - 2 }, { - 2, - 1 }, { - 2, 1 }, { - 1, 2 } };
    c.x += direct[ d ].x;
    c.y += direct[ d ].y;
    return c;
}

//未优化马踏棋盘过程 
bool ChessPath( Hchess &ch, PosType start, int m, int n, int &backnum, int &compare )
{
    SqStack path;
    InitSqStack( path, m * n );
    PosType curpos;
    SElemType e;
    curpos = start;
    //current_position
    int curstep = 1;
    //current_step
    do
    {   
        //判断该位置是否可行
        if ( ( curpos.x >= 0 && curpos.x < ch.row && curpos.y >= 0 && curpos.y < ch.col) && ( ch.chess[ curpos.x ][ curpos.y ] == 0 ) )
        //条件是：不超过棋盘的边界且这个点还没有被访问过
        {                                     
            compare++;  
            //统计探测次数 
            ch.chess[ curpos.x ][ curpos.y ] = curstep;
            e.seat.x = curpos.x;
            e.seat.y = curpos.y;
            e.di = 0;
            PushSqStack( path, e );                   //当前位置及方向入栈
            curstep++;	                                   //步数加1				
            curpos = NextPos( curpos,e.di );      
        }
        //取下一可行的位置	
        else if( ! SqStackEmpty( path ) )
        {								
        	compare++;                           //统计探测次数 
                PopSqStack( path, e );            //退栈到前一位置
	curstep--;
	while ( e.di == 7 && ! SqStackEmpty( path ) )      //到最后一个方向
                {
                ch.chess[ e.seat.x ][ e.seat.y ] = 0 ;                    				
                PopSqStack( path, e );    //退栈到前一位置
	curstep--;
	backnum++;                  //统计回溯次数
                }

	if ( e.di < 7 )
	{
		e.di++;
	                PushSqStack( path, e );
	                curstep++;
	                curpos = NextPos( e.seat, e.di );				
	 }
        }
        //无路可行 
       else return false; 	
    }while( curstep < ch.row * ch.col + 1 ); 
    //马踏棋盘游戏的运行条件是马没有走够64步
    return true;	    
}

#endif
