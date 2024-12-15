#include <stdio.h>
#include <stdlib.h>
typedef struct link
{
    int data;
    struct link *next;
} link,*plink;
plink initLink(int Size)
{
    plink p = (plink)malloc(sizeof(link)); //创建一个头结点
    plink temp = p;                                        //声明一个指针指向头结点，用于遍历链表

    for (int i = 1; i <= Size; i++)
    {
        plink a = (plink)malloc(sizeof(link));
        printf("请输入第%d个元素的值：", i);
        scanf("%d", &a->data);
        a->next = NULL;
        temp->next = a;
        temp = temp->next;
    }
    return p;
}
int getElem(plink p, int i)
//获取链表p中第i个元素的值
{
    plink q = p->next;
    int j = 1;
    while (q && j < i)
        q = q->next, ++j;
    if (!q || j > i)
    {
        puts("该元素不存在！");
        return -1;
    }
    return q->data;
}
plink insertdata(plink p, int data, int add)
//链表插入的函数，p是链表，data是插入的结点的数据域，add是插入的位置
{
    plink temp = p; //创建临时结点temp
    //首先找到要插入位置的上一个结点
    for (int i = 1; i < add; i++)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            printf("插入位置无效\n");
            return p;
        }
    }
    //创建插入结点c
    plink c = (plink)malloc(sizeof(link));
    c->data = data;
    //向链表中插入结点
    c->next = temp->next;
    temp->next = c;
    return p;
}
plink deldata(plink p, int add)
//删除结点的函数，p代表操作链表，add代表删除节点的位置
{
    plink temp = p;
    //遍历到被删除结点的上一个结点
    for (int i = 1; i < add; i++)
    {
        temp = temp->next;
        if (temp->next == NULL)
        {
            printf("没有该结点\n");
            return p;
        }
    }
    plink del = temp->next;        //单独设置一个指针指向被删除结点，以防丢失
    temp->next = temp->next->next; //删除某个结点的方法就是更改前一个结点的指针域
    free(del);                     //手动释放该结点，防止内存泄漏
    return p;
}
int selectdata(plink p, int data)
//查找结点的函数，data为目标结点的数据域的值（从0开始）
{
    plink t = p;
    int i = 0;
    while (t->next)
    {
        t = t->next;
        if (t->data == data)
            return i;
        i++;
    }
    return -1;
}
plink amenddata(plink p, int add, int newdata)
//更新结点的函数，newdata为新的数据域的值
{
    plink temp = p;
    temp = temp->next; //tamp指向首元结点
    //temp指向被删除结点
    for (int i = 1; i < add; i++)
        temp = temp->next;
    temp->data = newdata;
    return p;
}
void display(plink p)
{
    printf("修改后的链表为：");
    plink temp = p; //将temp指针重新指向头结点
    //只要temp指针指向的结点的next不是NULL，就执行输出语句。
    while (temp->next)
    {
        temp = temp->next;
        printf("%d ", temp->data);
    }
    printf("\n");
}