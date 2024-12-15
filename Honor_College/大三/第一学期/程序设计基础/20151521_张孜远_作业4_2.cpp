#include <iostream>
#include <queue>
#define MAXSIZE 50

using namespace std;

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree *T){
	// 按照二叉树先序遍历的顺序建立二叉树 
    char ch;
    scanf("%c", &ch);
    if(ch == '#') *T = NULL;
    else{
    	// 建立二叉树 
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(!*T) exit(-1);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

void printTree(BiTree T){
	//模仿作业1中的输出树 
	if (T == NULL) return;
	static int depth = -1;
	depth++;
	printTree(T->rchild);
	for (int i = 0; i < depth; i++) printf("\t");
	printf("%c\n", T->data);
	printTree(T->lchild);
	depth--;
}

int Depth(BiTree T) {
	// 递归求树的深度 
	int m, n;
	if (T == NULL) return 0;
	else{
		m = Depth(T->lchild);
		n = Depth(T->rchild);
		// + 1 代表根节点 
		if(m > n) return(m + 1);
		else return(n + 1);
	}
}

int Width(BiTree T){
	// 用队列来模拟层次遍历 
	BiTNode *p, *Q[MAXSIZE];
    int front = -1, rear = -1, final = 0;
    int width = 0;
    
    if (!T){
        printf("该二叉树为空！\n");
        return 0;
    }
    
    Q[++rear] = T;
    width = 1;
    while (front < rear){
        p = Q[++front];
        if (p->lchild){
            Q[++rear] = p->lchild;
        }
        if (p->rchild){
            Q[++rear] = p->rchild;
        }
        // front来到了某层的最后一个节点final 
        if (final == front){
            if(rear - front > width){
                width = rear - front;
            }
            // 更新final
            final = rear;
        }
    }
    // 二叉树的宽度就是该二叉树某层最大节点个数 
    return width;
}

int LeafNodeCount(BiTree T){
	// 递归计算叶子节点总数 
	if (T == NULL) return 0;
	if (T->lchild == NULL && T->rchild == NULL) return 1;
	else return LeafNodeCount(T->lchild) + LeafNodeCount(T->rchild);
}

int NodeCount(BiTree T) {
	// 递归计算节点总数 + 1 （根节点） 
	if (T == NULL) return 0;
	else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

int main(){
	BiTree myTree;
	int height, width, num_node, num_leaf_node;
	
	cout<<"请按照二叉树先序遍历的顺序输入二叉树的元素!\n";
	cout<<"如若二叉树中某一结点没有 XXX 个孩子，请输入 XXX 个 '#' 符号表示!\n";
	
	CreateBiTree(&myTree);
	printTree(myTree);
	width = Width(myTree);
	height = Depth(myTree);
	num_leaf_node  = LeafNodeCount(myTree);
	num_node = NodeCount(myTree);
	
	cout<<"该二叉树高度为："; 
	cout<<height<<endl;
	cout<<"该二叉树宽度为："; 
	cout<<width<<endl;
	cout<<"该二叉树结点总数为："; 
	cout<<num_node<<endl; 
	cout<<"该二叉树叶子结点总数为："; 
	cout<<num_leaf_node<<endl;
	
	return 0;
}

