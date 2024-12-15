#include <iostream>
#include <queue>
#define MAXSIZE 50

using namespace std;

typedef struct BiTNode{
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree *T){
	// ���ն��������������˳���������� 
    char ch;
    scanf("%c", &ch);
    if(ch == '#') *T = NULL;
    else{
    	// ���������� 
        *T = (BiTree)malloc(sizeof(BiTNode));
        if(!*T) exit(-1);
        (*T)->data = ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}

void printTree(BiTree T){
	//ģ����ҵ1�е������ 
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
	// �ݹ���������� 
	int m, n;
	if (T == NULL) return 0;
	else{
		m = Depth(T->lchild);
		n = Depth(T->rchild);
		// + 1 ������ڵ� 
		if(m > n) return(m + 1);
		else return(n + 1);
	}
}

int Width(BiTree T){
	// �ö�����ģ���α��� 
	BiTNode *p, *Q[MAXSIZE];
    int front = -1, rear = -1, final = 0;
    int width = 0;
    
    if (!T){
        printf("�ö�����Ϊ�գ�\n");
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
        // front������ĳ������һ���ڵ�final 
        if (final == front){
            if(rear - front > width){
                width = rear - front;
            }
            // ����final
            final = rear;
        }
    }
    // �������Ŀ�Ⱦ��Ǹö�����ĳ�����ڵ���� 
    return width;
}

int LeafNodeCount(BiTree T){
	// �ݹ����Ҷ�ӽڵ����� 
	if (T == NULL) return 0;
	if (T->lchild == NULL && T->rchild == NULL) return 1;
	else return LeafNodeCount(T->lchild) + LeafNodeCount(T->rchild);
}

int NodeCount(BiTree T) {
	// �ݹ����ڵ����� + 1 �����ڵ㣩 
	if (T == NULL) return 0;
	else return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

int main(){
	BiTree myTree;
	int height, width, num_node, num_leaf_node;
	
	cout<<"�밴�ն��������������˳�������������Ԫ��!\n";
	cout<<"������������ĳһ���û�� XXX �����ӣ������� XXX �� '#' ���ű�ʾ!\n";
	
	CreateBiTree(&myTree);
	printTree(myTree);
	width = Width(myTree);
	height = Depth(myTree);
	num_leaf_node  = LeafNodeCount(myTree);
	num_node = NodeCount(myTree);
	
	cout<<"�ö������߶�Ϊ��"; 
	cout<<height<<endl;
	cout<<"�ö��������Ϊ��"; 
	cout<<width<<endl;
	cout<<"�ö������������Ϊ��"; 
	cout<<num_node<<endl; 
	cout<<"�ö�����Ҷ�ӽ������Ϊ��"; 
	cout<<num_leaf_node<<endl;
	
	return 0;
}

