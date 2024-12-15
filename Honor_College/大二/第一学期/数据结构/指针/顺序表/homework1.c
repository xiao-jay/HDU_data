#include <stdio.h>
#include <stdlib.h>
#include "sequenceList.c"
int main()
{
    list t1=Initlist();
    puts("请输入顺序表内元素的个数:");
    scanf("%d",&t1.len);
    puts("请依次输入这些元素");
    for(int i=0;i<t1.len;i++) scanf("%d",&t1.head[i]);
    printf("原顺序表：\n");
    display(t1);
    printf("请选择你要实现的功能\n1.删除顺序表中值为key的所有结点\n2.删除顺序表中值重复的结点\n");
    int choice;
    scanf("%d",&choice);
    if(choice==1)
    {
        int key;
        printf("请输入要删除的key值:\n");
        scanf("%d",&key);
        while(1)
        {
            int now=selectlist(t1,key);
            if(now==-1) break;
            t1=dellist(t1,now);
        }
    }
    else if(choice==2)
    {
        for(int i=0;i<t1.len;i++)
            for(int j=i+1;j<t1.len;j++)
                if(t1.head[i]==t1.head[j])
                    t1=dellist(t1,i--);
    }
    else
    {
        puts("输入错误");
        exit(0);
    }

    display(t1);
    return 0;
}
