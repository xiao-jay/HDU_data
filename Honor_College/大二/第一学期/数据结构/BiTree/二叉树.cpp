//�Գƾ���  
//�����±�aij(i>=j)->һά�����±�B[k] 
//������ԭ��: 1+2+3+...+i-1+j = i(i-1)/2 + j 
//k = i(i-1)/2 + j - 1  (�±��0��ʼ) 
#include <stdio.h>

//(ֻ��������ȫ������)˳��洢����һ��Ҫ�Ѷ������Ľ��������ȫ��������Ӧ���� 
#define MaxSize 105
struct TreeNode{
	int value;  //����е�����Ԫ�� 
	bool isEmpty;  //����Ƿ�Ϊ�� 
};
//������t[0]��ȱ,��֤�����±�ͽ����һ�� 

TreeNode t[MaxSize];
//����һ������ΪMaxSize������t, ���մ��ϵ��¡������ҵ�˳�����δ洢����ȫ�������еĸ������ 

for (int i = 0; i < MaxSize; i++){
	//��ʼ�����н����Ϊ�� 
	t[i].isEmpty = true;
} 

//��ʽ�洢
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild, *rchild;  //���Һ���ָ�� 
}BiTNode, *BiTree; 

//n����� 2n��ָ�� n�����Ķ���������n+1��������(���ڹ�������������) 
struct ElemType{
	int value;
}; 

typedef struct BiTNode{
	ElemType data;
	struct BiTNode *lchild, *rchild; 
}BiTNode, *BiTree;

//����һ������
BiTree root = NULL;

//��������
root = (BiTree)malloc(sizeof(BiTNode));
root->data = {1};
root->lchild = NULL;
root->rchild = NULL; 
 
//�����½��
BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
p->data = {2};
p->lchild = NULL;
p->rchild = NULL;
root->lchild = p;  //��Ϊ���ڵ������

typedef struct BiTNode{
	//�������� 
	ElemType data;
	struct BiTNode *lchild, *rchild;
	struct BiTNode *parent;  //���ڵ�ָ�롪�������Ҹ��ڵ� 
}BiTNode, *BiTree; 

//��α���
//1����ʼ��һ����������; 2�����ڵ����; 
//3�������зǿ�, ���ͷ������, ���ʸý��, ���������Һ��Ӳ����β(����) 
//4���ظ�����3ֱ������Ϊ�� 

//���������(��ʽ�洢) 
typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, &rchild;
}BiTNode, *BiTree; 

//��ʽ���н��
typedef struct LinkNode{
	BiTNode *data;  //����ָ��,���ٿռ� 
	struct LinkNode *next;
}LinkNode;

typedef struct{
	LinkNode *front, *rear;  //��ͷ��βָ�� 
}LinkQueue;
 
void Level0rder(BiTree T){
	LinkQueue Q;
	//��ʼ���������� 
	InitQueue(Q);
	BiTree p;
	EnQueue(Q, T);  //���ڵ���� 
	while ( !IsEmpty(Q) ){
		//���в�����ѭ�� 
		DeQueue(Q, p);  //��ͷ������ 
		visit(p);
		if (p->lchild != NULL)
			EnQueue(Q, p->lchild);
		 if (p->rchild != NULL)
			EnQueue(Q, p->rchild);
	}
} 



//��/��/��������ǻ������ĵݹ�����ȷ���Ĵ������  
//   ������/�����/���Ҹ� 

//�������
void PreOrder(BiTree T){
	if (T != NULL){
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild); 
	}
}

//������� 
void InOrder(BiTree T){
	if (T != NULL){
		InOrder(T->lchild);
		visit(T);
		InOrder(T->rchild); 
	}
}

//������� 
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
		//������� = Max(���������, ���������) + 1
		//���ʸ��ڵ� 
		return l > r ? l + 1 : r + 1; 
	}
}

//��/��/���������ѡһ+���� ��Ψһȷ��һ�ö�����
//ǰ��+����; ����+����; ����+���� 

//�ҵ����ĸ��ڵ�,�������������л�����������,���ҵ������������ڵ� 

//����������(��������)
typedef struct ThreadNode{ 
	int data;
	struct ThreeNode *lchild, *rchild;
	int ltag, rtag;
}ThreadNode *ThreadTree;

//tag==0��ʾָ��ָ����, tag==1��ʾָ��ָ������ 



int main(){
	
	return 0;
} 


