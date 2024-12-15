#include <iostream>
#include <iomanip>
#include "ͼ�������͵�ʵ�֣��ڽӱ�.h"
using namespace std;
//���ʺ���ʵ�� 

void print( char *i )
{
    cout << setw( 3 ) << i;
}

typedef int SElemType; // ջ����
#include"SqStack.h" 

// �ӵ�v���������,������ȷ�ʽ���ݹ飩�������ܶ�·��
void HMDDFS( ALGraph G, int v, int &u, int &count, SqStack &S1, SqStack &S2, bool &tag1, bool &tag2 )
{ 
    visited[ v ] = true; // ���÷��ʱ�־ΪTRUE(�ѷ���)
    PushSqStack( S1, v );
    if ( ! tag2 ) PushSqStack( S2, v ); 
        count++;
    ArcNode *p;
    if ( count < G.vexnum )
    { 
        for ( p = G.vertices[ v ].firstarc; p && ! tag1; p = p->nextarc )   
            if ( ! visited[ p->adjvex ] )// ��v����δ���ʵ��ڽӵ�w�ݹ����HMDDFS
                HMDDFS( G, p->adjvex, u, count, S1, S2,tag1, tag2 );
        if ( ! tag1 )
        {
            count--;
            PopSqStack( S1, v ); //���� 
            if ( ! tag2 ) 
                PopSqStack( S2, v );
            visited[ v ] = false; 
        }
         
    }    
    else 
    {
        tag2 = true; //�ҵ����ܶ�ͨ· 
        for ( p = G.vertices[ v ].firstarc; p; p = p->nextarc )   
            if ( p->adjvex == u )
            {
                tag1 = true;//�ҵ����ܶٻ�· 
                PushSqStack( S1, u );
            }
        if( ! tag1 )
        {
            count--;
            PopSqStack( S1, v );//���� 
            visited[ v ] = false; 
        }        
          
    }
}

// �Թ��ܶ�ͼ���ж�
void HMDSearch( ALGraph G, void( *Visit )( char* ) )
{ 
    SqStack S1, S2, T;
    InitSqStack( S1, G.vexnum + 1 );//��ͼGΪ���ܶ�ͼ��ջs1 ��Ź��ܶٻ�· 
    InitSqStack( S2, G.vexnum + 1 );//��ͼGΪ����ܶ�ͼ��ջs2 ��Ź��ܶ�ͨ·
    InitSqStack( T, G.vexnum + 1 );//TΪ����ջ��������� ���ܶٻ�·����ܶ�ͨ· 
    int v;
    for ( v = 0; v < G.vexnum; v++ )
        visited[ v ] = false; // ���ʱ�־�����ʼ��; 
    v = 0; 
    int count = 0; 
     //��tag1Ϊtrue����ͼG�ǹ��ܶ�ͼ����tag2Ϊtrue��ͼG�ǰ���ܶ�ͼ
    bool tag1 = false, tag2 = false; 
     // ���й��ܶٻ�·��ͼΪ���ܶ�ͼ����ˣ�v����Դ�㣬Ҳ���յ� 
    HMDDFS( G, v, v, count, S1, S2, tag1, tag2 );     
    if( tag1 )
    {
        cout << endl << "��ͼΪ���ܶ�ͼ��һ�����ܶٻ�·Ϊ:" << endl; 
        while ( ! SqStackEmpty( S1 ) )
        {
            PopSqStack( S1, v );
            PushSqStack( T, v );        
        }
        while ( ! SqStackEmpty( T ) )
        {
            PopSqStack( T, v );
            Visit( G.vertices[ v ].data );
        }
    } 
    else
    { //��ͼG�ǹ��ܶ�ͼ������£����δ�ÿһ�������̽����ܶ�ͨ·          
        for ( v = 1; ! tag2 && v < G.vexnum; v++)
            HMDDFS(G, v, v, count, S1, S2, tag1, tag2); 
        if ( tag2 )
        {
            cout << endl << "��ͼΪ����ܶ�ͼ��һ�����ܶ�ͨ·Ϊ:" << endl; 
            while ( ! SqStackEmpty( S2 ) )
            {
                PopSqStack( S2, v );
                PushSqStack( T, v );        
            }
            while ( ! SqStackEmpty( T ) )
            {
                PopSqStack( T, v );
                Visit( G.vertices[ v ].data );
            }
        } 
        else
            cout << endl << "��ͼ���ǹ��ܶ�ͼ��" << endl;  
    }
    cout << endl;    
}

int main()
{
    ALGraph g;
    CreateGraph( g );
    Display( g );
    HMDSearch( g, print );
    cout << endl;
  
    system( "pause" );
    return 0;
}
