 // c9-4.h 双链树的存储结构
 #define MAXKEYLEN 16 // 关键字的最大长度
 struct KeysType // 关键字类型
 {
   char ch[MAXKEYLEN]; // 关键字
   int num; // 关键字长度
 };

 struct Record // 记录类型
 {
   KeysType key; // 关键字
   Others others; // 其它部分(由主程定义)
 };

 enum NodeKind{LEAF,BRANCH}; // 结点种类:{叶子,分支}
 typedef struct DLTNode // 双链树类型
 {
   char symbol;
   DLTNode *next; // 指向兄弟结点的指针
   NodeKind kind;
   union
   {
     Record *infoptr; // 叶子结点的记录指针
     DLTNode *first; // 分支结点的孩子链指针
   };
 }DLTNode,*DLTree;
