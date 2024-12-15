#include "SingleLinkedList.c"
int main() 
{
    int num;
    puts("请输入链表内元素个数：");
    scanf("%d",&num);
    link *p=initLink(num);
    printf("初始化链表为：\n");
    display(p);

    printf("请选择你要实现的功能\n1.删除单链表中值为key的所有结点\n2.删除单链表中值重复的结点\n");
    int choice;
    scanf("%d",&choice);
    plink temp=p;
    if(choice==1)
    {
        int key;
        printf("请输入要删除的key值:\n");
        scanf("%d",&key);
        while(temp->next)
        {
            if(temp->next->data==key)
            {
                link *del=temp->next;
                temp->next=temp->next->next;
                free(del);
            }
            else temp=temp->next;
        }
    }
    else if(choice==2)
    {
        plink now=p;
        while(now->next)
        {
            temp=now->next;
            while(temp->next)
            {
                if(temp->next->data==now->next->data)
                {
                    plink del=now->next;
                    now->next=now->next->next;
                    free(del);
                    temp=now->next;
                    continue;
                }
                else temp=temp->next;
            }
            now=now->next;
            printf("%d %d\n",now->data,temp->data);
        }
    }
    else
    {
        puts("输入错误");
        exit(0);
    }
    display(p);
    return 0;
}