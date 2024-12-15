#include <stdio.h>
#include <stdlib.h>

typedef struct BTNode{
    int data;
    struct BTNode *left, *right;
}BTNode, *BiTree;

BiTree creat(int A[], int B[], int l1, int r1, int l2, int r2){
	// 申请空间给根节点，并把先序遍历的第一个节点存到数组中（肯定是根节点） 
    BiTree root = (BiTree)malloc(sizeof(BTNode));
    root->data = A[l1];
    int i = l2;
    //  找到中序遍历过程中出现的根节点，以区分左右子树 
    for(i = l2; B[i] != A[l1]; i++); 
	  
    int llen = i - l2;  
    int rlen = r2 - i;
	    
	// 递归创建左右子树 
    if(llen > 0)
        root->left = creat(A, B, l1 + 1, l1 + llen, l2, llen + l2 - 1);
    else
        root->left = NULL;
        
    if(rlen > 0)
        root->right = creat(A, B, r1 - rlen + 1, r1, r2 - rlen + 1, r2);
    else
        root->right = NULL;

	// 返回创建好的树 
    return root;
}

void printTree(BiTree bt){
	// 输出树的形状 
	if (bt == NULL) return;
	// static代表作用于在printTree函数中 
	static int depth = -1;
	depth++;
	// 逆时针旋转90度打印树的形状
	// 先打印右子树，再打印左子树 
	printTree(bt->right);
	for (int i = 0; i < depth; i++) printf("\t");
	printf("%d\n", bt->data);
	printTree(bt->left);
	depth--;
}

int main(){
    printf("请输入二叉树的结点个数：\n"); 
	int n;
    scanf("%d", &n);
    int A[n + 1], B[n + 1];
    
    int x;
    printf("请输入二叉树的先序遍历序列：\n");
    for(int i = 1; i <= n; i++){
        scanf("%d", &x);
        A[i] = x;
    }
    
    printf("请输入二叉树的中序遍历序列：\n");
	for(int i = 1; i <= n; i++){
        scanf("%d", &x);
        B[i] = x;
    }
    
    BiTree bt = creat(A, B, 1, n, 1, n);
    // 到这一步，二叉树的二叉链表建立完成 
    printTree(bt);
    return 0;
}

