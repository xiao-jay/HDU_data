#include<stdio.h>
#include<stdlib.h>
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void CreateBiTree(BiTree *T) //先序创建二叉树 
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiTree  )malloc(sizeof(BiTNode));
        if(!*T)
            exit(-1);
        (*T)->data=ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
}
void PreOrderTraverse(BiTree T)//二叉树的先序遍历
{
    if(T==NULL)
        return ;
    printf("%c ",T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
void InOrderTraverse(BiTree T)//二叉树的中序遍历
{
   if(T==NULL)
       return ;
   InOrderTraverse(T->lchild);
    printf("%c ",T->data);
   InOrderTraverse(T->rchild);
}
void PostOrderTraverse(BiTree T)//后序遍历
{
    if(T==NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c ",T->data);
}
void LeafOfTree(BiTree T)//打印树的叶子节点函数定义
{
    if (T == NULL)    
        return ;
 
    else {
        if (T->lchild == NULL&&T->rchild == NULL)
            putchar(T->data);
        else {
            LeafOfTree(T->lchild);
            LeafOfTree(T->rchild);
        }
    }
        
}
int Get_Leaf_Num(BiTree T) //获取树的叶子节点个数函数定义
{
    if (T== NULL)
        return 0;
    if (T->lchild == NULL&&T->rchild == NULL)
        return 1;
    //递归整个树的叶子节点个数 = 左子树叶子节点的个数 + 右子树叶子节点的个数
    return Get_Leaf_Num(T->lchild) + Get_Leaf_Num(T->rchild);
}
int Get_Height(BiTree T) //获取树高的函数定义
{
    int Height = 0;
    if (T == NULL)
        return 0;
    
    //树的高度 = max(左子树的高度，右子树的高度) + 1
    else
    {
        int L_Height = Get_Height(T->lchild);
        int R_Height = Get_Height(T->rchild);
        Height = L_Height >= R_Height ? L_Height + 1 : R_Height + 1;
    }
    return Height;
}
void PrintTree(BiTree T,int h)
{
    if(T!=NULL)
    {
        PrintTree(T->rchild, h + 1);
        for (int i = 0; i < h;i++)
            printf("  ");
        printf("%c", T->data);
        print(T->lchild, h + 1);
    }
    puts("");
}
int main()//测试用例 ABDG##H###CE#I##F##
{
    BiTree T;
    CreateBiTree(&T);
    PreOrderTraverse (T);
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");
    LeafOfTree(T);
    printf("\n");
    printf("\n叶子节点个数为：%d", Get_Leaf_Num(T));
    printf("\n");
    printf("\n二叉树的高度为：%d", Get_Height(T));
    return 0;
}