#ifndef _graph_H_
#define _graph_H_
 
#include <cstring>
 
#define MAX_NAME 3 // 顶点字符串的最大长度+1
typedef int InfoType;
typedef char VertexType[ MAX_NAME ];
#define MAX_VERTEX_NUM 20
using namespace std;
 
//图的种类：{有向图,有向网,无向图,无向网} 
enum GraphKind{ DG, DN, UDG, UDN };  
 
//表结点结构 
struct ArcNode {
    int adjvex; // 该弧所指向的顶点的位置
    ArcNode *nextarc; // 指向下一条弧的指针
    InfoType *info; // 网的权值指针
}; 
 
//头结点结构 
typedef struct {
    VertexType data; // 顶点信息
    ArcNode *firstarc; // 第一个表结点的地址,指向第一条依附该顶点的弧的指针
}VNode, AdjList[ MAX_VERTEX_NUM ];
 
//图的邻接表存储结构
struct ALGraph {
    AdjList vertices;     // 顶点数组
    int vexnum,arcnum; // 图的当前顶点数和弧数
    int kind; // 图的种类标志
};
 
//以下为基于邻接表的图的基本操作的实现 

//查找顶点在顶点数组中的位置 
int LocateVex( ALGraph G, VertexType u )
{   
    int i;
    for ( i = 0; i < G.vexnum; i++ )
        if ( strcmp( u, G.vertices[ i ].data ) == 0 )
            return i;
    return -1;
}
 
//采用邻接表存储结构,构造没有相关信息的图G(用一个函数构造4种图)
bool CreateGraph( ALGraph &G )
{ 
    int i, j, k;
    int w; // 权值
    VertexType va, vb;
    ArcNode *p;
    cout << "(请输入图的类型(0:有向图,1:有向网,2:无向图,3:无向网):";
    cin >> G.kind;
    cout << "请输入图的顶点数目,边或弧的数目: ";
    cin >> G.vexnum >> G.arcnum;
    cout << "请输入" << G.vexnum << "个顶点的值(小于" << MAX_NAME << "个字符):" << endl;
    for ( i = 0; i < G.vexnum; i++ )
    {   // 构造顶点向量
        cin >> G.vertices[ i ].data;
        G.vertices[ i ].firstarc = NULL;
    }
    if ( G.kind == 1 || G.kind == 3) // 网
        cout << "请顺序输入每条弧(边)的权值、弧尾和弧头:" << endl;
    else // 图
        cout << "请顺序输入每条弧(边)的弧尾和弧头:" << endl;
    for ( k = 0; k < G.arcnum; k++ )
    {   // 构造表结点链表
        if ( G.kind == 1 || G.kind == 3 ) // 网
            cin >> w >> va >> vb;
        else // 图
            cin >> va >> vb;
        i = LocateVex( G, va ); // 弧尾
        j = LocateVex( G, vb ); // 弧头
        p = new ArcNode;
        p->adjvex = j;
        if ( G.kind == 1 || G.kind == 3 )
        {  // 网
            p->info = new int;
            *( p->info ) = w;
        }
        else
            p->info = NULL; // 图
        p->nextarc = G.vertices[ i ].firstarc; // 插在表头
        G.vertices[ i ].firstarc = p;
        if ( G.kind >= 2 )
        {   // 无向图或网,产生第二个表结点
            p = new ArcNode;
            p->adjvex = i;
            if ( G.kind == 3 )
            {   // 无向网
                p->info = new int;
                *( p->info ) = w;
            }
            else
                p->info = NULL; // 无向图
            p->nextarc = G.vertices[ j ].firstarc; // 插在表头
            G.vertices[ j ].firstarc = p;
        }
    }
    return true;
}
 
// 初始条件: 图G存在。操作结果: 销毁图G
void DestroyGraph( ALGraph &G )
{ 
    int i;
    ArcNode *p, *q;
    for ( i = 0; i < G.vexnum; i++ )
    {
        p = G.vertices[ i ].firstarc;
        while ( p )
        {
            q = p->nextarc;
            if ( G.kind % 2 ) // 网
                delete p->info;
            delete p;
            p = q;
        }
    }
    G.vexnum = 0;
    G.arcnum = 0;
}
 
//初始条件: 图G存在,v是G中某个顶点的序号。操作结果: 返回v的值
VertexType& GetVex( ALGraph G, int v )
{ 
    if ( v >= G.vexnum || v < 0 )
        exit( false );
    return G.vertices[ v ].data;
}
 
//初始条件: 图G存在,v是G中某个顶点,操作结果: 对v赋新值value
bool PutVex( ALGraph &G, VertexType v, VertexType value )
{ 
    int i;
    i = LocateVex( G,v );
    if ( i > - 1 ) 
    {   // v是G的顶点
        strcpy( G.vertices[ i ].data, value );
        return true;
    }
    return false;
}
 
// 初始条件: 图G存在,v是G中某个顶点
// 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1
int FirstAdjVex( ALGraph G, int v )
{ 
    ArcNode *p;
    p = G.vertices[ v ].firstarc;
    if(p)
        return p->adjvex;
    else
        return -1;
}
 
// 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点
// 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。
//           若w是v的最后一个邻接点,则返回-1
int NextAdjVex( ALGraph G, int v, int w )
{ 
    ArcNode *p;
    p = G.vertices[ v ].firstarc;
    while ( p && p->adjvex != w ) // 指针p不空且所指表结点不是w
        p = p->nextarc;
    if ( ! p || ! p->nextarc ) // 没找到w或w是最后一个邻接点
        return -1;
    else // p->adjvex==w
        return p->nextarc->adjvex; // 返回v的(相对于w的)下一个邻接顶点的序号
}
 
// 初始条件: 图G存在,v和图中顶点有相同特征
// 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)
void InsertVex( ALGraph &G, VertexType v )
{ 
    strcpy( G.vertices[ G.vexnum ].data, v ); // 构造新顶点向量
    G.vertices[ G.vexnum ].firstarc = NULL;
    G.vexnum++; // 图G的顶点数加1
}
 
// 初始条件: 图G存在,v是G中某个顶点
// 操作结果: 删除G中顶点v及其相关的弧
bool DeleteVex( ALGraph &G, VertexType v )
{
    int i, j;
    ArcNode *p, *q;
    j = LocateVex( G, v ); // j是顶点v的序号
    if ( j < 0 ) // v不是图G的顶点
        return false;
    p = G.vertices[ j ].firstarc; // 删除以v为出度的弧或边
    while ( p )
    {
        q = p;
        p = p->nextarc;
        if ( G.kind % 2 ) // 网
            delete q->info;
        delete q;
        G.arcnum --; // 弧或边数减1
    }
    G.vexnum--; // 顶点数减1
    for ( i = j; i < G.vexnum; i++ ) // 顶点v后面的顶点前移
        G.vertices[ i ] = G.vertices[ i + 1 ];
    for ( i = 0; i < G.vexnum; i++ ) 
    {   // 删除以v为入度的弧或边且必要时修改表结点的顶点位置值
        p = G.vertices[ i ].firstarc; // 指向第1条弧或边
        while ( p )
        {   // 有弧
            if ( p->adjvex == j )
            {
                if ( p == G.vertices[ i ].firstarc )
                {    // 待删结点是第1个结点
                    G.vertices[ i ].firstarc = p->nextarc;
                    if ( G.kind % 2 ) // 网
                        delete p->info;
                    delete p;
                    p = G.vertices[ i ].firstarc;
                    if ( G.kind < 2 ) // 有向
                        G.arcnum--; // 弧或边数减1
                }
                else
                {
                    q->nextarc = p->nextarc;
                    if ( G.kind % 2 ) // 网
                        delete p->info;
                    delete p;
                    p = q->nextarc;
                    if ( G.kind < 2 ) // 有向
                        G.arcnum --; // 弧或边数减1
                }
            }
            else
            {
                if ( p->adjvex > j )
                    p->adjvex--; // 修改表结点的顶点位置值(序号)
                q = p;
                p = p->nextarc;
            }
        }
    }
    return true;
}
 
//初始条件: 图G存在,v和w是G中两个顶点
// 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v>
bool InsertArc( ALGraph &G, VertexType v, VertexType w )
{ 
    ArcNode *p;
    int w1, i, j;
    i = LocateVex( G, v ); // 弧尾或边的序号
    j = LocateVex( G, w ); // 弧头或边的序号
    if ( i < 0 || j < 0 )
        return false;
    G.arcnum++; // 图G的弧或边的数目加1
    if ( G.kind % 2 ) 
    {   // 网
        cout << "请输入弧(边)<<v<<","<<w<<的权值: ";
        cin >> w1;
    }
    p = new ArcNode;
    p->adjvex = j;
    if( G.kind % 2 ) 
    {   // 网
        p->info = new int;
        *( p->info ) = w1;
    }
    else
        p->info = NULL;
    p->nextarc = G.vertices[ i ].firstarc; // 插在表头
    G.vertices [i ].firstarc = p;
    if ( G.kind >= 2 )
    {   // 无向,生成另一个表结点
        p = new ArcNode;
        p->adjvex = i;
        if ( G.kind == 3 )  
        {   // 无向网
            p->info = new int;
            *( p->info ) = w1;
        }
        else
            p->info = NULL;
        p->nextarc = G.vertices [ j ].firstarc; // 插在表头
        G.vertices[ j ].firstarc = p;
    }
    return true;
}
 
// 初始条件: 图G存在,v和w是G中两个顶点
// 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v>
bool DeleteArc( ALGraph &G, VertexType v, VertexType w )
{
    ArcNode *p, *q;
    int i, j;
    i = LocateVex( G, v ); // i是顶点v(弧尾)的序号
    j = LocateVex( G, w ); // j是顶点w(弧头)的序号
    if ( i < 0 || j < 0 || i == j )
        return false;
    p = G.vertices[ i ].firstarc; // p指向顶点v的第一条出弧
    while ( p && p->adjvex != j ) 
    {   // p不空且所指之弧不是待删除弧<v,w>，则p指向下一条弧
        q = p;
        p = p->nextarc;
    }
    if ( p && p->adjvex == j )
    {   // 找到弧<v,w>
        if ( p == G.vertices[ i ].firstarc ) // p所指是第1条弧
            G.vertices[ i ].firstarc = p->nextarc; // 指向下一条弧
        else
            q->nextarc = p->nextarc; // 指向下一条弧
        if ( G.kind % 2 ) // 网
            delete p->info;
        delete p; // 释放此结点
        G.arcnum --; // 弧或边数减1
    }
    if ( G.kind >= 2 )
    {   // 无向,删除对称弧<w,v>
        p = G.vertices[ j ].firstarc; // p指向顶点w的第一条出弧
        while ( p && p->adjvex != i )
        {   // p不空且所指之弧不是待删除弧<w,v>，则 p指向下一条弧
            q = p;
            p = p->nextarc;
        }
        if ( p && p->adjvex == i )
        {   // 找到弧<w,v>
            if ( p == G.vertices[ j ].firstarc ) // p所指是第1条弧
                G.vertices[ j ].firstarc = p->nextarc; // 指向下一条弧
            else
                q->nextarc = p->nextarc; // 指向下一条弧
            if ( G.kind == 3 ) // 无向网
                delete p->info;
            delete p; // 释放此结点
        }
    }
    return true;
}

bool visited[MAX_VERTEX_NUM]; // 访问标志数组(全局量)
void( *VisitFunc )( char* v ); // 函数变量(全局量)
 
// 从第v个顶点出发递归地深度优先遍历图G
void DFS( ALGraph G, int v )
{ 
    int w;
    visited[ v ] = true; // 设置访问标志为TRUE(已访问)
    VisitFunc( G.vertices[ v ].data ); // 访问第v个顶点
    for ( w = FirstAdjVex( G, v ); w >= 0; w = NextAdjVex( G, v, w ) )
        if ( ! visited[ w ] )
            DFS( G, w ); // 对v的尚未访问的邻接点w递归调用DFS
}
 
// 对图G作深度优先遍历。
void DFSTraverse( ALGraph G, void( *Visit )( char* ) )
{ 
    int v;
    VisitFunc = Visit; // 使用全局变量VisitFunc,使DFS不必设函数指针参数
    for ( v = 0; v < G.vexnum; v++ )
        visited[ v ] = false; // 访问标志数组初始化
    cout << "深度优先遍历的结果是:" << endl; 
    for ( v = 0; v < G.vexnum; v++ )
        if ( ! visited[ v ] )
            DFS( G, v ); // 对尚未访问的顶点调用DFS
    cout << endl;
}

typedef int QElemType; // 队列类型
#include"LinkQueue.h"
 
//按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited 
void BFSTraverse( ALGraph G, void( *Visit )( char* ) )
{
    int v, u, w;
    VertexType u1, w1;
    LinkQueue Q;
    for ( v = 0; v < G.vexnum; v++ )
        visited[ v ] = false; // 置初值
    InitQueue( Q ); // 置空的辅助队列Q
    cout << "广度优先遍历的结果是:" << endl; 
    for ( v = 0; v < G.vexnum; v++) // 如果是连通图,只v=0就遍历全图
        if ( ! visited[ v ] )
        { // v尚未访问
            visited[ v ] = true;
            Visit( G.vertices[ v ].data );
            EnQueue( Q, v ); // v入队列
            while ( ! QueueEmpty( Q ) )
            {  // 队列不空
                DeQueue( Q, v ); // 队头元素出队并置为u
                for ( w = FirstAdjVex( G, v ); w >= 0; w = NextAdjVex( G, v, w ) )
                    if ( ! visited[ w ] )
                    { // w为u的尚未访问的邻接顶点
                        visited[ w ] = true;
                        Visit( G.vertices[ w ].data );
                        EnQueue( Q, w ); // w入队
                    }
            }
        }
    cout << endl;
}
 
// 输出图的邻接矩阵G
void Display( ALGraph G )
{ // 输出图的邻接矩阵G
    int i;
    ArcNode *p;
    switch ( G.kind )
    {
        case DG:  
            cout << endl << "该图为有向图,";
            break;
        case DN:  
            cout << endl << "该图为有向网,";
            break;
        case UDG: 
            cout << endl << "该图为无向图,";
            break;
        case UDN: 
            cout << endl << "该图为无向网,";
    }
    cout << "其中有" << G.vexnum << "个顶点,各顶点值分别为:" << endl;
    for ( i = 0; i < G.vexnum; i++ )
        cout << G.vertices[ i ].data << " ";
    cout << endl << "该图有" << G.arcnum << "条弧(边),所建邻接表为:" << endl;         
    for ( i = 0; i < G.vexnum; i++ )
    {
        p = G.vertices[ i ].firstarc;
        while ( p )
        {
            if ( G.kind <= 1 ) 
            {   // 有向
                cout << G.vertices[ i ].data << "->" << G.vertices[ p->adjvex ].data;
                if ( G.kind == DN ) // 网
                    cout << ":" << *( p->info ) << " ";
            }
            else
            {  // 无向(避免输出两次)
                cout << G.vertices[ i ].data << "--" << G.vertices[ p->adjvex ].data << "  ";
                if ( G.kind == UDN ) // 网
                    cout << ":" << *( p->info ) << " ";
            }       
            p = p->nextarc;
        }
        cout << endl;
    }
}
  
#endif
