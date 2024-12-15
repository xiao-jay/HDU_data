#define Size 10000
typedef struct list
{
    int *head;
    int len;
    int size;
}list;
list Initlist()
//构造一个空的顺序表
{
    list t; 
    t.head=(int*)malloc(Size*sizeof(int));
    if (!t.head)
    {
        printf("初始化失败\n");
        exit(0);
    }
    t.len=0;
    t.size=Size;
    return t;
}
list addlist(list t,int elem,int add)
//在顺序表t中第add位置之前插入新的元素elem
{
    if(add>=t.len||add<0) 
    {
        puts("插入位置不合法");
        return t;
    }
    if(t.len==t.size) 
    {
        t.head=(int *)realloc(t.head,(t.size+1)*sizeof(int));
        if(!t.head) 
        {
            puts("存储分配失败");
            exit(0);
        }
        t.size++;
    }
    for(int i=t.len-1;i>=add;i--)  t.head[i+1]=t.head[i];
    t.head[add]=elem;
    t.len++;
    return t;
}
list dellist(list t,int add)
//在顺序表t中删除第add个位置的元素
{
    if(add>=t.len||add<0) 
    {
        printf("被删除元素的位置非法\n");
        return t;
    }
    for(int i=add+1;i<t.len;i++) t.head[i-1]=t.head[i];
    t.len--;
    return t;
}
int selectlist(list t,int elem)
//搜索第一个值为elem的元素，并返回它的位置
{
    for(int i=0;i<t.len;i++)
        if(t.head[i]==elem)
            return i;
    return -1;
}
list amendlist(list t,int elem,int newElem)
//更改函数，其中，elem为要更改的元素的值，newElem为新的数据元素
{
    int add=selectlist(t,elem);
    t.head[add]=newElem;
    return t;
}
void display(list t)
//输出顺序表
{
    printf("修改后的顺序表为：");
    for(int i=0;i<t.len;i++) printf("%d ",t.head[i]);
    puts("");
}