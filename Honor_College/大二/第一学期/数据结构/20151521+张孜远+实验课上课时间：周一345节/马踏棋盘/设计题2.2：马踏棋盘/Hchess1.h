#ifndef _Hchess_
#define _Hchess_

//���̵�λ������ 
struct PosType {
    int x;     //������
    int y;	//������
};

//ջ������Ԫ������ 
struct SElemType {
    PosType seat;	//���������е�����λ��
    int di;                   //�Ӵ˵��ߵ���һ��ķ���0~7��ʾ1~8������
};

#include "SqStack.h"

//���̽ṹ 
struct Hchess {
    int **chess;
    int row;       //����
    int col;        //����
};

//���̳�ʼ�� 
void Initchess( Hchess &ch, int m, int n )
{
    int i, j;
    ch.row = m;
    ch.col = n;
    ch.chess = new int *[ ch.row ];
    for ( i = 0; i < ch.row; i++ )
	    ch.chess[ i ] = new int[ ch.col ];
    //�ö�ά�����¼�����е�ÿһ��������꣺�ȿ�һ�����飬�ٶ������е�ÿ��Ԫ�ؿ�һ������
    //��ʹ�����������ÿ��λ�õ�����
    for ( i = 0; i < ch.row; i++ )
	    for ( j = 0; j < ch.col; j++ )
		    ch.chess[ i ][ j ] = 0;
     //��ÿ��λ�õ������ʼ��Ϊ0	
}

//��������
void Destroychess( Hchess &ch )
{
    //������С���飬�����ٴ�����
    for ( int i = 0; i < ch.row; i++ )
	    if ( ch.chess[ i ] != NULL )
		    delete [] ch.chess[ i ];
    if ( ch.chess != NULL )
	    delete [] ch.chess;
}

//��˳ʱ���ѡ���8���������� 
PosType NextPos( PosType c, int d )
{
    //��¼��һ�����ܵ��������λ�������֮ǰλ�õ�����仯
    PosType direct[ 8 ] = { { 1, 2 }, { 2, 1 }, { 2, - 1 }, { 1, - 2 }, { - 1, - 2 }, { - 2, - 1 }, { - 2, 1 }, { - 1, 2 } };
    c.x += direct[ d ].x;
    c.y += direct[ d ].y;
    return c;
}

//δ�Ż���̤���̹��� 
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
        //�жϸ�λ���Ƿ����
        if ( ( curpos.x >= 0 && curpos.x < ch.row && curpos.y >= 0 && curpos.y < ch.col) && ( ch.chess[ curpos.x ][ curpos.y ] == 0 ) )
        //�����ǣ����������̵ı߽�������㻹û�б����ʹ�
        {                                     
            compare++;  
            //ͳ��̽����� 
            ch.chess[ curpos.x ][ curpos.y ] = curstep;
            e.seat.x = curpos.x;
            e.seat.y = curpos.y;
            e.di = 0;
            PushSqStack( path, e );                   //��ǰλ�ü�������ջ
            curstep++;	                                   //������1				
            curpos = NextPos( curpos,e.di );      
        }
        //ȡ��һ���е�λ��	
        else if( ! SqStackEmpty( path ) )
        {								
        	compare++;                           //ͳ��̽����� 
                PopSqStack( path, e );            //��ջ��ǰһλ��
	curstep--;
	while ( e.di == 7 && ! SqStackEmpty( path ) )      //�����һ������
                {
                ch.chess[ e.seat.x ][ e.seat.y ] = 0 ;                    				
                PopSqStack( path, e );    //��ջ��ǰһλ��
	curstep--;
	backnum++;                  //ͳ�ƻ��ݴ���
                }

	if ( e.di < 7 )
	{
		e.di++;
	                PushSqStack( path, e );
	                curstep++;
	                curpos = NextPos( e.seat, e.di );				
	 }
        }
        //��·���� 
       else return false; 	
    }while( curstep < ch.row * ch.col + 1 ); 
    //��̤������Ϸ��������������û���߹�64��
    return true;	    
}

#endif
