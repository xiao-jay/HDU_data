#include <iostream>
#include <iomanip>
#include "图抽象类型的实现（邻接表）.h"
using namespace std;
//访问函数实体 

void print( char *i )
{
    cout << setw( 3 ) << i;
}

typedef int SElemType; // 栈类型
#include"SqStack.h" 

// 从第v个顶点出发,深度优先方式（递归）搜索哈密顿路径
void HMDDFS( ALGraph G, int v, int &u, int &count, SqStack &S1, SqStack &S2, bool &tag1, bool &tag2 )
{ 
    visited[ v ] = true; // 设置访问标志为TRUE(已访问)
    PushSqStack( S1, v );
    if ( ! tag2 ) PushSqStack( S2, v ); 
        count++;
    ArcNode *p;
    if ( count < G.vexnum )
    { 
        for ( p = G.vertices[ v ].firstarc; p && ! tag1; p = p->nextarc )   
            if ( ! visited[ p->adjvex ] )// 对v的尚未访问的邻接点w递归调用HMDDFS
                HMDDFS( G, p->adjvex, u, count, S1, S2,tag1, tag2 );
        if ( ! tag1 )
        {
            count--;
            PopSqStack( S1, v ); //回溯 
            if ( ! tag2 ) 
                PopSqStack( S2, v );
            visited[ v ] = false; 
        }
         
    }    
    else 
    {
        tag2 = true; //找到哈密顿通路 
        for ( p = G.vertices[ v ].firstarc; p; p = p->nextarc )   
            if ( p->adjvex == u )
            {
                tag1 = true;//找到哈密顿回路 
                PushSqStack( S1, u );
            }
        if( ! tag1 )
        {
            count--;
            PopSqStack( S1, v );//回溯 
            visited[ v ] = false; 
        }        
          
    }
}

// 对哈密顿图的判断
void HMDSearch( ALGraph G, void( *Visit )( char* ) )
{ 
    SqStack S1, S2, T;
    InitSqStack( S1, G.vexnum + 1 );//若图G为哈密顿图，栈s1 存放哈密顿回路 
    InitSqStack( S2, G.vexnum + 1 );//若图G为半哈密顿图，栈s2 存放哈密顿通路
    InitSqStack( T, G.vexnum + 1 );//T为辅助栈，用以输出 哈密顿回路或哈密顿通路 
    int v;
    for ( v = 0; v < G.vexnum; v++ )
        visited[ v ] = false; // 访问标志数组初始化; 
    v = 0; 
    int count = 0; 
     //若tag1为true，则图G是哈密顿图，若tag2为true则图G是半哈密顿图
    bool tag1 = false, tag2 = false; 
     // 具有哈密顿回路的图为哈密顿图，因此，v既是源点，也是终点 
    HMDDFS( G, v, v, count, S1, S2, tag1, tag2 );     
    if( tag1 )
    {
        cout << endl << "该图为哈密顿图，一条哈密顿回路为:" << endl; 
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
    { //在图G非哈密顿图的情况下，依次从每一顶点出发探测哈密顿通路          
        for ( v = 1; ! tag2 && v < G.vexnum; v++)
            HMDDFS(G, v, v, count, S1, S2, tag1, tag2); 
        if ( tag2 )
        {
            cout << endl << "该图为半哈密顿图，一条哈密顿通路为:" << endl; 
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
            cout << endl << "该图不是哈密顿图。" << endl;  
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
