 // c2-5.h 带头结点的线性链表类型
 typedef struct LNode // 结点类型
 {
   ElemType data;
   LNode *next;
 }*Link,*Position;

 struct LinkList // 链表类型
 {
   Link head,tail; // 分别指向线性链表中的头结点和最后一个结点
   int len; // 指示线性链表中数据元素的个数
 };
