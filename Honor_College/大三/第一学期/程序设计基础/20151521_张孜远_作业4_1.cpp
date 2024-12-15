#include <stdio.h>
#include <stdlib.h>

typedef struct BTNode{
    int data;
    struct BTNode *left, *right;
}BTNode, *BiTree;

BiTree creat(int A[], int B[], int l1, int r1, int l2, int r2){
	// ����ռ�����ڵ㣬������������ĵ�һ���ڵ�浽�����У��϶��Ǹ��ڵ㣩 
    BiTree root = (BiTree)malloc(sizeof(BTNode));
    root->data = A[l1];
    int i = l2;
    //  �ҵ�������������г��ֵĸ��ڵ㣬�������������� 
    for(i = l2; B[i] != A[l1]; i++); 
	  
    int llen = i - l2;  
    int rlen = r2 - i;
	    
	// �ݹ鴴���������� 
    if(llen > 0)
        root->left = creat(A, B, l1 + 1, l1 + llen, l2, llen + l2 - 1);
    else
        root->left = NULL;
        
    if(rlen > 0)
        root->right = creat(A, B, r1 - rlen + 1, r1, r2 - rlen + 1, r2);
    else
        root->right = NULL;

	// ���ش����õ��� 
    return root;
}

void printTree(BiTree bt){
	// ���������״ 
	if (bt == NULL) return;
	// static������������printTree������ 
	static int depth = -1;
	depth++;
	// ��ʱ����ת90�ȴ�ӡ������״
	// �ȴ�ӡ���������ٴ�ӡ������ 
	printTree(bt->right);
	for (int i = 0; i < depth; i++) printf("\t");
	printf("%d\n", bt->data);
	printTree(bt->left);
	depth--;
}

int main(){
    printf("������������Ľ�������\n"); 
	int n;
    scanf("%d", &n);
    int A[n + 1], B[n + 1];
    
    int x;
    printf("�����������������������У�\n");
    for(int i = 1; i <= n; i++){
        scanf("%d", &x);
        A[i] = x;
    }
    
    printf("�����������������������У�\n");
	for(int i = 1; i <= n; i++){
        scanf("%d", &x);
        B[i] = x;
    }
    
    BiTree bt = creat(A, B, 1, n, 1, n);
    // ����һ�����������Ķ������������ 
    printTree(bt);
    return 0;
}

