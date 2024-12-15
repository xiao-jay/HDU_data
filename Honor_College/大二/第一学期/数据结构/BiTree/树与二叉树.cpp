//二叉树或为空树，或为至多划分成两个互不相交的子树（有次序）->二叉树中不存在度大于2的结点+一个根节点 ，或只有一个根节点
//基本操作：五个重要的性质

#include <stdio.h>
#include <stdlib.h>

/*
性质1：(书p123,用数学归纳法证明) 
	在二叉树的第i层至多有2^(i-1)个结点(i>=1)，最少有一个结点(要有叶子结点) 
	
性质2：
	深度为k的二叉树的最大结点数为: 2^k - 1(k>=1) 
	
性质3：
	对任何一颗二叉树，若它含有n0个叶子结点，n2个度为2的结点，那必存在关系式：n0 = n2 + 1
	sum = n0 + n1 + n2
	分支引出角度:B_sum = 2n2 + n1
	分支引入角度：B_sum = sum - 1
	化简可得:n0 = n2 + 1
	
满二叉树:深度为k的二叉树每一层都是满的(结点能有多少就有多少) 
完全二叉树:树中所含的n个结点和满二叉树中编号为1~n的结点一一对应 
拟满二叉树:前k-1层的结点是满二叉树的结点序号，最后一层的结点不按照满二叉树序号排列而是在第k层结点随机分布 
满二叉树是完全二叉树，满二叉树是拟满二叉树
完全二叉树不一定是满二叉树
完全二叉树一定是拟满二叉树 
拟满二叉树不一定是完全/满二叉树 
正则二叉树:在树中只有度为0或度为2的结点 

性质4：
	具有n个结点的完全二叉树的深度为: [log2n] + 1
	由题意：2^(k-1) - 1 < n <= 2^k - 1
	易得：2^(k-1)<=n<2^k
	易得:k>log2n && k <= log2n + 1
	
除了根节点外的任意编号为i的结点的双亲编号是[i/2]
对任意编号为i的结点，左孩子编号为2i，右孩子编号为2i+1 

性质5：
	若对任意编号为i的结点，若2i>n，(2i+1>n)则无左孩子，否则编号为2i(2i+1)的结点为其左(右)孩子结点
证明：用数学归纳法p125 

二叉树的遍历(对结构下的数据元素访问且访问一次)

顺序存储：(理论可行 现实不可行)——空间复杂度太高 
链式存储： 二叉链表(左指针lchild+data+右指针rchild)
 
三叉链表：增加一个parent指针域(动态链表结构) 
*/ 

struct ElemType{
	int value;
}; 

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild; 
}BiTNode, *BiTree;

//计算机中工作栈  
//非线性结构线性化 
//先序遍历算法(递归) p129
void Preorder(BiTree T, void(*visit)(TElemType &e)){
	if (T){
		visit(T->data);//访问结点
		Preorder(T->lchild, visit);//遍历左子树 
		Preorder(T->rchild, visit);//遍历右子树 
	}
} 

//求二叉树的深度(后序遍历)
int Depth(BiTree T){
	if (!T) depth = 0;
	else{
		depleft = Depth(T->lchild);
		depleft = Depth(T->rchild);
		depth = 1 + (depthleft > depthright ? depthleft : depthright);
	}
	return depth;
} 

//先序遍历：DLR 
void Count_leaf(BiTree T, int &count){
	if (T){
		if ((!T->lchild) && (!T->rchild))
			count++;
		Count_leaf(T->lchild, count);
		Count_leaf(T->rchild, count);
	}
}

void Destroy(//后序遍历，把visit函数改为free函数) 
 
