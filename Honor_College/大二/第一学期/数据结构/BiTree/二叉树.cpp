//对称矩阵  
//矩阵下标aij(i>=j)->一维数组下标B[k] 
//行优先原则: 1+2+3+...+i-1+j = i(i-1)/2 + j 
//k = i(i-1)/2 + j - 1  (下标从0开始) 
#include <stdio.h>

//(只适用于完全二叉树)顺序存储——一定要把二叉树的结点编号与完全二叉树对应起来 
#define MaxSize 105
struct TreeNode{
	int value;  //结点中的数据元素 
	bool isEmpty;  //结点是否为空 
};
//让数组t[0]空缺,保证数组下标和结点编号一致 

TreeNode t[MaxSize];
//定义一个长度为MaxSize的数组t, 按照从上到下、从左到右的顺序依次存储完完全二叉树中的各个结点 

for (int i = 0; i < MaxSize; i++){
	//初始化所有结点标记为空 
	t[i].isEmpty = true;
} 

//链式存储
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild, *rchild;  //左右孩子指针 
}BiTNode, *BiTree; 

//n个结点 2n个指针 n个结点的二叉链表有n+1个空链域(用于构造线索二叉树) 
struct ElemType{
	int value;
}; 

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild; 
}BiTNode, *BiTree;

//定义一个空树
BiTree root = NULL;

//插入根结点
root = (BiTree)malloc(sizeof(BiTNode));
root->data = {1};
root->lchild = NULL;
root->rchild = NULL; 
 
//插入新结点
BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
p->data = {2};
p->lchild = NULL;
p->rchild = NULL;
root->lchild = p;  //作为根节点的左孩子

typedef struct BiTNode{
	//三叉链表 
	ElemType data;
	struct BiTNode *lchild, *rchild;
	struct BiTNode *parent;  //父节点指针——方便找父节点 
}BiTNode, *BiTree; 

//层次遍历
//1、初始化一个辅助队列; 2、根节点入队; 
//3、若队列非空, 则队头结点出队, 访问该结点, 并将其左右孩子插入队尾(若有) 
//4、重复步骤3直到队列为空 

//二叉树结点(链式存储) 
typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, &rchild;
}BiTNode, *BiTree; 

//链式队列结点
typedef struct LinkNode{
	BiTNode *data;  //保存指针,减少空间 
	struct LinkNode *next;
}LinkNode;

typedef struct{
	LinkNode *front, *rear;  //队头队尾指针 
}LinkQueue;
 
void Level0rder(BiTree T){
	LinkQueue Q;
	//初始化辅助队列 
	InitQueue(Q);
	BiTree p;
	EnQueue(Q, T);  //根节点入队 
	while ( !IsEmpty(Q) ){
		//队列不空则循环 
		DeQueue(Q, p);  //队头结点出队 
		visit(p);
		if (p->lchild != NULL)
			EnQueue(Q, p->lchild);
		 if (p->rchild != NULL)
			EnQueue(Q, p->rchild);
	}
} 



//先/中/后序遍历是基于树的递归特性确定的次序规则  
//   根左右/左根右/左右根 

//先序遍历
void PreOrder(BiTree T){
	if (T != NULL){
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild); 
	}
}

//中序遍历 
void InOrder(BiTree T){
	if (T != NULL){
		InOrder(T->lchild);
		visit(T);
		InOrder(T->rchild); 
	}
}

//后序遍历 
void PostOrder(BiTree T){
	if (T != NULL){
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		visit(T); 
	}
}

void visit(BiTNode *p){
	printf("%c", p->data);
}

int treeDeepth(BiTree T){
	if (T == NULL){
		return 0;
	}else{
		int l = treeDepth(T->lchild);
		int r = treeDepth(T->rchild);
		//树的深度 = Max(左子树深度, 右子树深度) + 1
		//访问根节点 
		return l > r ? l + 1 : r + 1; 
	}
}

//层/先/后序遍历三选一+中序 能唯一确定一棵二叉树
//前序+中序; 后序+中序; 层序+中序 

//找到树的根节点,并根据中序序列划分左右子树,再找到左右子树根节点 

//线索二叉树(线索链表)
typedef struct ThreadNode{ 
	int data;
	struct ThreeNode *lchild, *rchild;
	int ltag, rtag;
}ThreadNode *ThreadTree;

//tag==0表示指针指向孩子, tag==1表示指针指向线索 



int main(){
	
	return 0;
} 


