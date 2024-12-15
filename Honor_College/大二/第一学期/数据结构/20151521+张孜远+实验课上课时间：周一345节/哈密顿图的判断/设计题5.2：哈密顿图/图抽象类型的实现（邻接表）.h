#ifndef _graph_H_
#define _graph_H_
 
#include <cstring>
 
#define MAX_NAME 3 // �����ַ�������󳤶�+1
typedef int InfoType;
typedef char VertexType[ MAX_NAME ];
#define MAX_VERTEX_NUM 20
using namespace std;
 
//ͼ�����ࣺ{����ͼ,������,����ͼ,������} 
enum GraphKind{ DG, DN, UDG, UDN };  
 
//����ṹ 
struct ArcNode {
    int adjvex; // �û���ָ��Ķ����λ��
    ArcNode *nextarc; // ָ����һ������ָ��
    InfoType *info; // ����Ȩֵָ��
}; 
 
//ͷ���ṹ 
typedef struct {
    VertexType data; // ������Ϣ
    ArcNode *firstarc; // ��һ������ĵ�ַ,ָ���һ�������ö���Ļ���ָ��
}VNode, AdjList[ MAX_VERTEX_NUM ];
 
//ͼ���ڽӱ�洢�ṹ
struct ALGraph {
    AdjList vertices;     // ��������
    int vexnum,arcnum; // ͼ�ĵ�ǰ�������ͻ���
    int kind; // ͼ�������־
};
 
//����Ϊ�����ڽӱ��ͼ�Ļ���������ʵ�� 

//���Ҷ����ڶ��������е�λ�� 
int LocateVex( ALGraph G, VertexType u )
{   
    int i;
    for ( i = 0; i < G.vexnum; i++ )
        if ( strcmp( u, G.vertices[ i ].data ) == 0 )
            return i;
    return -1;
}
 
//�����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG(��һ����������4��ͼ)
bool CreateGraph( ALGraph &G )
{ 
    int i, j, k;
    int w; // Ȩֵ
    VertexType va, vb;
    ArcNode *p;
    cout << "(������ͼ������(0:����ͼ,1:������,2:����ͼ,3:������):";
    cin >> G.kind;
    cout << "������ͼ�Ķ�����Ŀ,�߻򻡵���Ŀ: ";
    cin >> G.vexnum >> G.arcnum;
    cout << "������" << G.vexnum << "�������ֵ(С��" << MAX_NAME << "���ַ�):" << endl;
    for ( i = 0; i < G.vexnum; i++ )
    {   // ���춥������
        cin >> G.vertices[ i ].data;
        G.vertices[ i ].firstarc = NULL;
    }
    if ( G.kind == 1 || G.kind == 3) // ��
        cout << "��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ:" << endl;
    else // ͼ
        cout << "��˳������ÿ����(��)�Ļ�β�ͻ�ͷ:" << endl;
    for ( k = 0; k < G.arcnum; k++ )
    {   // �����������
        if ( G.kind == 1 || G.kind == 3 ) // ��
            cin >> w >> va >> vb;
        else // ͼ
            cin >> va >> vb;
        i = LocateVex( G, va ); // ��β
        j = LocateVex( G, vb ); // ��ͷ
        p = new ArcNode;
        p->adjvex = j;
        if ( G.kind == 1 || G.kind == 3 )
        {  // ��
            p->info = new int;
            *( p->info ) = w;
        }
        else
            p->info = NULL; // ͼ
        p->nextarc = G.vertices[ i ].firstarc; // ���ڱ�ͷ
        G.vertices[ i ].firstarc = p;
        if ( G.kind >= 2 )
        {   // ����ͼ����,�����ڶ�������
            p = new ArcNode;
            p->adjvex = i;
            if ( G.kind == 3 )
            {   // ������
                p->info = new int;
                *( p->info ) = w;
            }
            else
                p->info = NULL; // ����ͼ
            p->nextarc = G.vertices[ j ].firstarc; // ���ڱ�ͷ
            G.vertices[ j ].firstarc = p;
        }
    }
    return true;
}
 
// ��ʼ����: ͼG���ڡ��������: ����ͼG
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
            if ( G.kind % 2 ) // ��
                delete p->info;
            delete p;
            p = q;
        }
    }
    G.vexnum = 0;
    G.arcnum = 0;
}
 
//��ʼ����: ͼG����,v��G��ĳ���������š��������: ����v��ֵ
VertexType& GetVex( ALGraph G, int v )
{ 
    if ( v >= G.vexnum || v < 0 )
        exit( false );
    return G.vertices[ v ].data;
}
 
//��ʼ����: ͼG����,v��G��ĳ������,�������: ��v����ֵvalue
bool PutVex( ALGraph &G, VertexType v, VertexType value )
{ 
    int i;
    i = LocateVex( G,v );
    if ( i > - 1 ) 
    {   // v��G�Ķ���
        strcpy( G.vertices[ i ].data, value );
        return true;
    }
    return false;
}
 
// ��ʼ����: ͼG����,v��G��ĳ������
// �������: ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1
int FirstAdjVex( ALGraph G, int v )
{ 
    ArcNode *p;
    p = G.vertices[ v ].firstarc;
    if(p)
        return p->adjvex;
    else
        return -1;
}
 
// ��ʼ����: ͼG����,v��G��ĳ������,w��v���ڽӶ���
// �������: ����v��(�����w��)��һ���ڽӶ������š�
//           ��w��v�����һ���ڽӵ�,�򷵻�-1
int NextAdjVex( ALGraph G, int v, int w )
{ 
    ArcNode *p;
    p = G.vertices[ v ].firstarc;
    while ( p && p->adjvex != w ) // ָ��p��������ָ���㲻��w
        p = p->nextarc;
    if ( ! p || ! p->nextarc ) // û�ҵ�w��w�����һ���ڽӵ�
        return -1;
    else // p->adjvex==w
        return p->nextarc->adjvex; // ����v��(�����w��)��һ���ڽӶ�������
}
 
// ��ʼ����: ͼG����,v��ͼ�ж�������ͬ����
// �������: ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)
void InsertVex( ALGraph &G, VertexType v )
{ 
    strcpy( G.vertices[ G.vexnum ].data, v ); // �����¶�������
    G.vertices[ G.vexnum ].firstarc = NULL;
    G.vexnum++; // ͼG�Ķ�������1
}
 
// ��ʼ����: ͼG����,v��G��ĳ������
// �������: ɾ��G�ж���v������صĻ�
bool DeleteVex( ALGraph &G, VertexType v )
{
    int i, j;
    ArcNode *p, *q;
    j = LocateVex( G, v ); // j�Ƕ���v�����
    if ( j < 0 ) // v����ͼG�Ķ���
        return false;
    p = G.vertices[ j ].firstarc; // ɾ����vΪ���ȵĻ����
    while ( p )
    {
        q = p;
        p = p->nextarc;
        if ( G.kind % 2 ) // ��
            delete q->info;
        delete q;
        G.arcnum --; // ���������1
    }
    G.vexnum--; // ��������1
    for ( i = j; i < G.vexnum; i++ ) // ����v����Ķ���ǰ��
        G.vertices[ i ] = G.vertices[ i + 1 ];
    for ( i = 0; i < G.vexnum; i++ ) 
    {   // ɾ����vΪ��ȵĻ�����ұ�Ҫʱ�޸ı���Ķ���λ��ֵ
        p = G.vertices[ i ].firstarc; // ָ���1�������
        while ( p )
        {   // �л�
            if ( p->adjvex == j )
            {
                if ( p == G.vertices[ i ].firstarc )
                {    // ��ɾ����ǵ�1�����
                    G.vertices[ i ].firstarc = p->nextarc;
                    if ( G.kind % 2 ) // ��
                        delete p->info;
                    delete p;
                    p = G.vertices[ i ].firstarc;
                    if ( G.kind < 2 ) // ����
                        G.arcnum--; // ���������1
                }
                else
                {
                    q->nextarc = p->nextarc;
                    if ( G.kind % 2 ) // ��
                        delete p->info;
                    delete p;
                    p = q->nextarc;
                    if ( G.kind < 2 ) // ����
                        G.arcnum --; // ���������1
                }
            }
            else
            {
                if ( p->adjvex > j )
                    p->adjvex--; // �޸ı���Ķ���λ��ֵ(���)
                q = p;
                p = p->nextarc;
            }
        }
    }
    return true;
}
 
//��ʼ����: ͼG����,v��w��G����������
// �������: ��G������<v,w>,��G�������,������Գƻ�<w,v>
bool InsertArc( ALGraph &G, VertexType v, VertexType w )
{ 
    ArcNode *p;
    int w1, i, j;
    i = LocateVex( G, v ); // ��β��ߵ����
    j = LocateVex( G, w ); // ��ͷ��ߵ����
    if ( i < 0 || j < 0 )
        return false;
    G.arcnum++; // ͼG�Ļ���ߵ���Ŀ��1
    if ( G.kind % 2 ) 
    {   // ��
        cout << "�����뻡(��)<<v<<","<<w<<��Ȩֵ: ";
        cin >> w1;
    }
    p = new ArcNode;
    p->adjvex = j;
    if( G.kind % 2 ) 
    {   // ��
        p->info = new int;
        *( p->info ) = w1;
    }
    else
        p->info = NULL;
    p->nextarc = G.vertices[ i ].firstarc; // ���ڱ�ͷ
    G.vertices [i ].firstarc = p;
    if ( G.kind >= 2 )
    {   // ����,������һ������
        p = new ArcNode;
        p->adjvex = i;
        if ( G.kind == 3 )  
        {   // ������
            p->info = new int;
            *( p->info ) = w1;
        }
        else
            p->info = NULL;
        p->nextarc = G.vertices [ j ].firstarc; // ���ڱ�ͷ
        G.vertices[ j ].firstarc = p;
    }
    return true;
}
 
// ��ʼ����: ͼG����,v��w��G����������
// �������: ��G��ɾ����<v,w>,��G�������,��ɾ���Գƻ�<w,v>
bool DeleteArc( ALGraph &G, VertexType v, VertexType w )
{
    ArcNode *p, *q;
    int i, j;
    i = LocateVex( G, v ); // i�Ƕ���v(��β)�����
    j = LocateVex( G, w ); // j�Ƕ���w(��ͷ)�����
    if ( i < 0 || j < 0 || i == j )
        return false;
    p = G.vertices[ i ].firstarc; // pָ�򶥵�v�ĵ�һ������
    while ( p && p->adjvex != j ) 
    {   // p��������ָ֮�����Ǵ�ɾ����<v,w>����pָ����һ����
        q = p;
        p = p->nextarc;
    }
    if ( p && p->adjvex == j )
    {   // �ҵ���<v,w>
        if ( p == G.vertices[ i ].firstarc ) // p��ָ�ǵ�1����
            G.vertices[ i ].firstarc = p->nextarc; // ָ����һ����
        else
            q->nextarc = p->nextarc; // ָ����һ����
        if ( G.kind % 2 ) // ��
            delete p->info;
        delete p; // �ͷŴ˽��
        G.arcnum --; // ���������1
    }
    if ( G.kind >= 2 )
    {   // ����,ɾ���Գƻ�<w,v>
        p = G.vertices[ j ].firstarc; // pָ�򶥵�w�ĵ�һ������
        while ( p && p->adjvex != i )
        {   // p��������ָ֮�����Ǵ�ɾ����<w,v>���� pָ����һ����
            q = p;
            p = p->nextarc;
        }
        if ( p && p->adjvex == i )
        {   // �ҵ���<w,v>
            if ( p == G.vertices[ j ].firstarc ) // p��ָ�ǵ�1����
                G.vertices[ j ].firstarc = p->nextarc; // ָ����һ����
            else
                q->nextarc = p->nextarc; // ָ����һ����
            if ( G.kind == 3 ) // ������
                delete p->info;
            delete p; // �ͷŴ˽��
        }
    }
    return true;
}

bool visited[MAX_VERTEX_NUM]; // ���ʱ�־����(ȫ����)
void( *VisitFunc )( char* v ); // ��������(ȫ����)
 
// �ӵ�v����������ݹ��������ȱ���ͼG
void DFS( ALGraph G, int v )
{ 
    int w;
    visited[ v ] = true; // ���÷��ʱ�־ΪTRUE(�ѷ���)
    VisitFunc( G.vertices[ v ].data ); // ���ʵ�v������
    for ( w = FirstAdjVex( G, v ); w >= 0; w = NextAdjVex( G, v, w ) )
        if ( ! visited[ w ] )
            DFS( G, w ); // ��v����δ���ʵ��ڽӵ�w�ݹ����DFS
}
 
// ��ͼG��������ȱ�����
void DFSTraverse( ALGraph G, void( *Visit )( char* ) )
{ 
    int v;
    VisitFunc = Visit; // ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ�����
    for ( v = 0; v < G.vexnum; v++ )
        visited[ v ] = false; // ���ʱ�־�����ʼ��
    cout << "������ȱ����Ľ����:" << endl; 
    for ( v = 0; v < G.vexnum; v++ )
        if ( ! visited[ v ] )
            DFS( G, v ); // ����δ���ʵĶ������DFS
    cout << endl;
}

typedef int QElemType; // ��������
#include"LinkQueue.h"
 
//��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited 
void BFSTraverse( ALGraph G, void( *Visit )( char* ) )
{
    int v, u, w;
    VertexType u1, w1;
    LinkQueue Q;
    for ( v = 0; v < G.vexnum; v++ )
        visited[ v ] = false; // �ó�ֵ
    InitQueue( Q ); // �ÿյĸ�������Q
    cout << "������ȱ����Ľ����:" << endl; 
    for ( v = 0; v < G.vexnum; v++) // �������ͨͼ,ֻv=0�ͱ���ȫͼ
        if ( ! visited[ v ] )
        { // v��δ����
            visited[ v ] = true;
            Visit( G.vertices[ v ].data );
            EnQueue( Q, v ); // v�����
            while ( ! QueueEmpty( Q ) )
            {  // ���в���
                DeQueue( Q, v ); // ��ͷԪ�س��Ӳ���Ϊu
                for ( w = FirstAdjVex( G, v ); w >= 0; w = NextAdjVex( G, v, w ) )
                    if ( ! visited[ w ] )
                    { // wΪu����δ���ʵ��ڽӶ���
                        visited[ w ] = true;
                        Visit( G.vertices[ w ].data );
                        EnQueue( Q, w ); // w���
                    }
            }
        }
    cout << endl;
}
 
// ���ͼ���ڽӾ���G
void Display( ALGraph G )
{ // ���ͼ���ڽӾ���G
    int i;
    ArcNode *p;
    switch ( G.kind )
    {
        case DG:  
            cout << endl << "��ͼΪ����ͼ,";
            break;
        case DN:  
            cout << endl << "��ͼΪ������,";
            break;
        case UDG: 
            cout << endl << "��ͼΪ����ͼ,";
            break;
        case UDN: 
            cout << endl << "��ͼΪ������,";
    }
    cout << "������" << G.vexnum << "������,������ֵ�ֱ�Ϊ:" << endl;
    for ( i = 0; i < G.vexnum; i++ )
        cout << G.vertices[ i ].data << " ";
    cout << endl << "��ͼ��" << G.arcnum << "����(��),�����ڽӱ�Ϊ:" << endl;         
    for ( i = 0; i < G.vexnum; i++ )
    {
        p = G.vertices[ i ].firstarc;
        while ( p )
        {
            if ( G.kind <= 1 ) 
            {   // ����
                cout << G.vertices[ i ].data << "->" << G.vertices[ p->adjvex ].data;
                if ( G.kind == DN ) // ��
                    cout << ":" << *( p->info ) << " ";
            }
            else
            {  // ����(�����������)
                cout << G.vertices[ i ].data << "--" << G.vertices[ p->adjvex ].data << "  ";
                if ( G.kind == UDN ) // ��
                    cout << ":" << *( p->info ) << " ";
            }       
            p = p->nextarc;
        }
        cout << endl;
    }
}
  
#endif
