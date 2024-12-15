 // c7-3.h 有向图的十字链表存储表示
 #define MAX_VERTEX_NUM 20
 struct ArcBox // 弧结点
 {
   int tailvex,headvex; // 该弧的尾和头顶点的位置
   ArcBox *hlink,*tlink; // 分别为弧头相同和弧尾相同的弧的链域
   InfoType *info; // 该弧相关信息的指针(可无)
 };
 struct VexNode // 顶点结点
 {
   VertexType data;
   ArcBox *firstin,*firstout; // 分别指向该顶点第一条入弧和出弧
 };
 struct OLGraph
 {
   VexNode xlist[MAX_VERTEX_NUM]; // 表头向量(数组)
   int vexnum,arcnum; // 有向图的当前顶点数和弧数
 };