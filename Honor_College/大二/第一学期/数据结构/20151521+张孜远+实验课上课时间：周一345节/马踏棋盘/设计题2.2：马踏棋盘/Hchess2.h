#ifndef _Hchess_
#define _Hchess_

//棋盘坐标 
struct PosType {
    int x;      //行坐标
    int y;      //列坐标
};

//优化版：栈中存放的数据元素类型  
struct SElemType {
    PosType seat;	//马在棋盘中的坐标位置
    int di;                   //从此点走到下一点的方向（0~7表示1~8个方向）
    PosType A[8];      //按可跳位置的出口数排序的数组 
};

#include "SqStack.h"

//马行棋的顺时针八个方向 
PosType direct[ 8 ] = { { 1, 2 }, { 2, 1 }, { 2, - 1 }, { 1, - 2 }, { - 1, - 2 }, { - 2, - 1 }, { - 2, 1 }, { - 1, 2 } };

//二维数组表示的棋盘 
struct Hchess {
    int **chess;
    int row;
    int col;
};

//棋盘初始化 
void Initchess( Hchess &ch,int m, int n )
{   
    int i, j;
    ch.row = m;
    ch.col = n;
    ch.chess = new int *[ ch.row ];
    for ( i = 0; i < ch.row; i++ )
	    ch.chess[ i ] = new int[ ch.col ];	
    for ( i = 0; i < ch.row; i++ )	 
	    for ( j = 0; j < ch.col; j++ )
		    ch.chess[ i ][ j ] = 0;	
}

//销毁二维数组表示的棋盘 
void Destroychess( Hchess &ch )
{
    for ( int i = 0; i < ch.row; i++ )
	    if ( ch.chess[ i ] != NULL )
		    delete [] ch.chess[ i ];
    if ( ch.chess != NULL )	
	    delete [] ch.chess;	
}

//马行走的下一位置 
PosType NextPos( PosType &c, SElemType &e )
{
    c.x += e.A[ e.di ].x;
    c.y += e.A[ e.di ].y;
    return c;
}

//行棋方向的优化：当前位置的下一行棋方向，按可跳位置中下一可跳位置的多少从小到大的筛选（相当于剪枝） 
void Resort( Hchess ch, SElemType &c )
{
    int i,  j, k, min, m, b[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    PosType e, r, q;
    for ( i = 0; i < 8; i++ ) 
    {
        //统计每一可跳位置的出口数
        e.x = c.seat.x + direct[ i ].x;
        e.y = c.seat.y + direct[ i ].y;
        if ( ( e.x >= 0 && e.x < ch.row && e.y >= 0 && e.y < ch.col) && (ch.chess[ e.x ][ e.y ] == 0 ) )
        //下一步跳马符合规则
            for ( j = 0; j < 8; j++ ) 
            {
                r.x = e.x + direct[ j ].x;
                r.y = e.y + direct[ j ].y;
                if ( ( r.x >= 0 && r.x < ch.row &&r.y >= 0 && r.y < ch.col) && (ch.chess[ r.x ][ r.y ] == 0 ) ) 
                    b[ i ]++;    
	    //统计一共有几种走法  
            }            
    }  
    for ( i = 0; i < 7; i++ )  
    {	
        //对每一可跳位置的出口数进行从小到大的排序
        //默认拥有的八条路（最多）是最小值 并随时更新
        min = 8 ; 
        k = i;            
        for ( j = i; j < 8; j++ ) 
        	if ( b[ j ] > 0 && b[ j ] < min ) 
           	{
                	min = b[ j ]; 
                	k = j;
           	}    
        //用min记录拥有最少路径的马跳步
        m = b[ i ] ; 
        b[ i ] = b[ k ]; 
        b[ k ] = m; 
        q = c.A[ i ] ;
        c.A[ i ] = c.A[ k ];
        c.A[ k ] = q;
    }   
}

//按优化后的策略马踏棋盘  
bool ChessPath( Hchess &ch, PosType start, int m, int n, int &backnum, int &compare)
{
    SqStack path;
    PosType curpos, curp;
    SElemType e;
    InitSqStack( path, m * n );
    curpos = start;
    int curstep = 1;
    do
    {  
        //判断当前位置是否可行
        if ( ( curpos.x >= 0 && curpos.x < ch.row && curpos.y >= 0 && curpos.y < ch.col) && ( ch.chess[ curpos.x ][ curpos.y ] == 0 ) )
        {                                        
            compare++;                                             //统计探测次数 
            ch.chess[ curpos.x ][ curpos.y ] = curstep;
            e.seat.x = curpos.x;
            e.seat.y = curpos.y;
            e.di = 0;
            for ( int i = 0; i < 8; i++ ) 
                e.A[ i ] = direct[ i ];
            Resort( ch, e );
            PushSqStack( path, e );                             //当前位置及方向入栈			
            curstep++;	                                             //足迹加1		
            curpos = NextPos( curpos, e);                  //更新下一个当前位置          
        }
        //取可行的下一位置	
        else if ( ! SqStackEmpty( path ) )
        {		
            compare++;                                             //统计探测次数 		
            PopSqStack( path, e );	                             //退栈到前一位置	    
            curstep--;
            while ( e.di == 7 && ! SqStackEmpty( path ) )   //到最后一个方向
            { 
                ch.chess[ e.seat.x ][ e.seat.y ] = 0 ;                  
	PopSqStack( path, e );                                    //退回一步
	curstep--;
	backnum++;                                                  //统计回溯次数 
            }
            if ( e.di < 7 )
            {
                e.di++;					
                PushSqStack( path, e );
                curstep++;
                curpos = NextPos( e.seat, e );				
             }
        }
        //无路可走 
        else return false;          
    }while( curstep < ch.row * ch.col + 1 );                     //运行条件是马没有走够64步
    return true;    
}

#endif
