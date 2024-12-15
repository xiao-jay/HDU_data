 // c6-4.h 树的双亲表存储表示
 #define MAX_TREE_SIZE 100
 struct PTNode
 {
   TElemType data;
   int parent; // 双亲位置域
 };
 struct PTree
 {
   PTNode nodes[MAX_TREE_SIZE];
   int n; // 结点数
 };
