 // c6-3.h 二叉树的二叉线索存储表示
 enum PointerTag // 枚举
 {Link,Thread}; // Link(0):指针,Thread(1):线索
 struct BiThrNode
 {
   TElemType data;
   BiThrNode *lchild,*rchild; // 左右孩子指针
   PointerTag LTag,RTag; // 左右标志
 };
 typedef BiThrNode *BiThrTree;