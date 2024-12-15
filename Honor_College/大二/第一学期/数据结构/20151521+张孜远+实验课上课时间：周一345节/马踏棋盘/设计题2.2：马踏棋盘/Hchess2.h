#ifndef _Hchess_
#define _Hchess_

//�������� 
struct PosType {
    int x;      //������
    int y;      //������
};

//�Ż��棺ջ�д�ŵ�����Ԫ������  
struct SElemType {
    PosType seat;	//���������е�����λ��
    int di;                   //�Ӵ˵��ߵ���һ��ķ���0~7��ʾ1~8������
    PosType A[8];      //������λ�õĳ�������������� 
};

#include "SqStack.h"

//�������˳ʱ��˸����� 
PosType direct[ 8 ] = { { 1, 2 }, { 2, 1 }, { 2, - 1 }, { 1, - 2 }, { - 1, - 2 }, { - 2, - 1 }, { - 2, 1 }, { - 1, 2 } };

//��ά�����ʾ������ 
struct Hchess {
    int **chess;
    int row;
    int col;
};

//���̳�ʼ�� 
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

//���ٶ�ά�����ʾ������ 
void Destroychess( Hchess &ch )
{
    for ( int i = 0; i < ch.row; i++ )
	    if ( ch.chess[ i ] != NULL )
		    delete [] ch.chess[ i ];
    if ( ch.chess != NULL )	
	    delete [] ch.chess;	
}

//�����ߵ���һλ�� 
PosType NextPos( PosType &c, SElemType &e )
{
    c.x += e.A[ e.di ].x;
    c.y += e.A[ e.di ].y;
    return c;
}

//���巽����Ż�����ǰλ�õ���һ���巽�򣬰�����λ������һ����λ�õĶ��ٴ�С�����ɸѡ���൱�ڼ�֦�� 
void Resort( Hchess ch, SElemType &c )
{
    int i,  j, k, min, m, b[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    PosType e, r, q;
    for ( i = 0; i < 8; i++ ) 
    {
        //ͳ��ÿһ����λ�õĳ�����
        e.x = c.seat.x + direct[ i ].x;
        e.y = c.seat.y + direct[ i ].y;
        if ( ( e.x >= 0 && e.x < ch.row && e.y >= 0 && e.y < ch.col) && (ch.chess[ e.x ][ e.y ] == 0 ) )
        //��һ��������Ϲ���
            for ( j = 0; j < 8; j++ ) 
            {
                r.x = e.x + direct[ j ].x;
                r.y = e.y + direct[ j ].y;
                if ( ( r.x >= 0 && r.x < ch.row &&r.y >= 0 && r.y < ch.col) && (ch.chess[ r.x ][ r.y ] == 0 ) ) 
                    b[ i ]++;    
	    //ͳ��һ���м����߷�  
            }            
    }  
    for ( i = 0; i < 7; i++ )  
    {	
        //��ÿһ����λ�õĳ��������д�С���������
        //Ĭ��ӵ�еİ���·����ࣩ����Сֵ ����ʱ����
        min = 8 ; 
        k = i;            
        for ( j = i; j < 8; j++ ) 
        	if ( b[ j ] > 0 && b[ j ] < min ) 
           	{
                	min = b[ j ]; 
                	k = j;
           	}    
        //��min��¼ӵ������·����������
        m = b[ i ] ; 
        b[ i ] = b[ k ]; 
        b[ k ] = m; 
        q = c.A[ i ] ;
        c.A[ i ] = c.A[ k ];
        c.A[ k ] = q;
    }   
}

//���Ż���Ĳ�����̤����  
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
        //�жϵ�ǰλ���Ƿ����
        if ( ( curpos.x >= 0 && curpos.x < ch.row && curpos.y >= 0 && curpos.y < ch.col) && ( ch.chess[ curpos.x ][ curpos.y ] == 0 ) )
        {                                        
            compare++;                                             //ͳ��̽����� 
            ch.chess[ curpos.x ][ curpos.y ] = curstep;
            e.seat.x = curpos.x;
            e.seat.y = curpos.y;
            e.di = 0;
            for ( int i = 0; i < 8; i++ ) 
                e.A[ i ] = direct[ i ];
            Resort( ch, e );
            PushSqStack( path, e );                             //��ǰλ�ü�������ջ			
            curstep++;	                                             //�㼣��1		
            curpos = NextPos( curpos, e);                  //������һ����ǰλ��          
        }
        //ȡ���е���һλ��	
        else if ( ! SqStackEmpty( path ) )
        {		
            compare++;                                             //ͳ��̽����� 		
            PopSqStack( path, e );	                             //��ջ��ǰһλ��	    
            curstep--;
            while ( e.di == 7 && ! SqStackEmpty( path ) )   //�����һ������
            { 
                ch.chess[ e.seat.x ][ e.seat.y ] = 0 ;                  
	PopSqStack( path, e );                                    //�˻�һ��
	curstep--;
	backnum++;                                                  //ͳ�ƻ��ݴ��� 
            }
            if ( e.di < 7 )
            {
                e.di++;					
                PushSqStack( path, e );
                curstep++;
                curpos = NextPos( e.seat, e );				
             }
        }
        //��·���� 
        else return false;          
    }while( curstep < ch.row * ch.col + 1 );                     //������������û���߹�64��
    return true;    
}

#endif
