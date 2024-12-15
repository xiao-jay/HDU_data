#include <stdio.h>
#include <stdlib.h>
#include "dynamic_stack_c.h"
typedef int Status;
typedef char TElemType;
#define MAX_TREE_SIZE 100
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define OK 1

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

Status CreateBiTree(BiTree *T)
{
    char ch;
    scanf("%c", &ch);
    if (ch == ' ')
        T = NULL;
    else
    {
        if (!((*T) = (BiTNode *)malloc(sizeof(BiTNode))))
            exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(&((*T)->lchild));
        CreateBiTree(&((*T)->rchild));
    }
    return OK;
}

Status Visit(TElemType e)
{
    printf("%c ", e);
}

Status PreOrderTraverse(BiTree T)//先序遍历
{
    if (T)
    {
        if (Visit(T->data))
            if (PreOrderTraverse(T->lchild))
                if (PreOrderTraverse(T->rchild))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}

Status InOrderTraverse(BiTree T)//中序遍历
{
    if (T)
    {
        if (PreOrderTraverse(T->lchild))
            if (Visit(T->data))
                if (PreOrderTraverse(T->rchild))
                    return OK;
        return ERROR;
    }
    else
        return OK;
}