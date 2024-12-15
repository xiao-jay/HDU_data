//ptail->next=pnew;
//pnew->num=numb;
//ptail=pnew;
//实现：先把旧指针ptail往后移一位指向pnew，再向新的指针pnew输入数据，再把ptail和pnew放到一起 ;类比：链表插入排序 

#include<stdio.h>
#include<stdlib.h>

struct Node
{
	long long int data;
	int cnt;			
	struct Node *next;
};//定义每个数据；每个数据的计数器cnt；指向下一个结点的指针 

struct Node *p;
//定义三个全局变量（p贯穿整个程序；后两者用于冒泡排序算法） 
struct Node *Add(struct Node *head, int data); 
struct Node* Add_newhead(struct Node *preHead);
void Bubble_Sort(struct Node *head); 
void Destory(struct Node *head);

int main()
{
	struct Node *head=NULL; 
	//初始化：让头指针是空的，制造一个有头结点的链表 
	long long int num;
	scanf("%d",&num); 
	while(num!= 0)
	{
		p=head;//定义head 
		while(p!=NULL){
		if(p->data==num)
		{
			++p->cnt;
		}p=p->next;
	}//以上几步达到：每输入一个数据，就把这个数据存放入链表中并且记下来该数据有几个 
		head=Add(head, num);
	 //如何插入一个头结点 
		scanf("%d", &num);
	}head=Add_newhead(head);//创造一个新的头结点
	
	Bubble_Sort(head);
	//泡沫排序法：使输出的数据由个数从高到低输出 
	
	struct Node *p=head->next;
	//使用全局变量的性质:改变指针p，为后续做铺垫 
	
	while(p!=NULL)
	{
		printf("%d:%d\n", p->data, p->cnt);
		p=p->next;
	}//打印所有的数据
	 
	while(p != NULL)
	{
		struct Node *r=p;
		p=p->next;
	}head->next=NULL; 
	//把一个个数据都删除 
	Destory(head);
	//释放链表 
	return 0;
}//此处代码进行了简化:1、无须对指针p进行两次struct结构指针；2、两个while不能合并，否则会出错 ！ 

struct Node *Add(struct Node *head,int num)
//如何插入一个头结点 
{
	struct Node *pnew, *ppre; 
	pnew=(struct Node *)malloc(sizeof(struct Node));
	//用malloc函数给一个存储空间 
	pnew->data=num;
	pnew->cnt=1;
	//把那个数字输入链表数据中，并计数为1 
	if(head==NULL)
	{
		head=pnew;
		head->next=NULL;
	}//如果head是空的，那么就把pnew赋值给head，让下一个head再变成空的（有头结点） 
	else if(pnew->data > head->data)
		{
			pnew->next=head;
			head=pnew;
		}//如果pnew存放的数据大于head中存放的数据，那么让head往前动一个成为下一个pnew，接着把pnew的值赋给head  
		else
		{
			p=head;
			while(p!=NULL && pnew->data < p->data)
			{
				ppre=p;
				p=p->next;
			}//如果p不空且pnew中数据小于p中数据，那么把p的数据赋给ppre（旧的），再把指针指向下一个 ；达到：把小的数放到前面的效果 
			if(p==NULL || pnew->data > p->data )
				{
					pnew->next=p;
					ppre->next=pnew;
				}//如果p是空的或者pnew中数据大于p中数据，那么把p的值赋给下个pnew，pnew的值赋给下个ppre；达到：把大的数往后稍稍的效果			
		}
	return head;
}

struct Node* Add_newhead(struct Node *preHead)
{
	struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
	//用malloc函数给一个存储空间 
	newHead->cnt=0;
	newHead->next = preHead;
	//新的头计数为0；在链表中，下一个新的头指针就是之前旧的头指针 
	return newHead;
}

void Bubble_Sort(struct Node *head) 
{
	int j,count = 0,num;
	struct Node *r, *tail;
	p=head;
	while(p->next!=NULL)
	{
		count++;
		p=p->next;
	}//先数一下这个链表有多少个存储的数据 
	for(j=0; j<count-1; j++)
	{
		num=count-j-1;
		p=head->next;
		r=p->next;
		tail=head; 
//形成：tail p q 的链表元素顺序 
		while(num--)
		{
			if(p->cnt < r->cnt)
			{
				p->next=r->next;
				r->next=p;
				tail->next=r;
			}
				tail = tail->next;
				p=tail->next;
				r=p->next;
		 } //遍历要排序的元素列，依次比较两个相邻的元素，如果顺序错误就把他们交换过来。走访元素的工作是重复地进行直到没有相邻元素需要交换，也就是说该元素列已经排序完成。 
	} //冒泡排序算法的每一轮都要遍历一遍所有的元素，轮转的次数和元素数量相当，所以时间复杂度为O(N^2)。 
}//参考网址：https://blog.csdn.net/lu_1079776757/article/details/80459370 

void Destory(struct Node *head)
{
	struct Node *q;
	p=q=head;
	while(p!=NULL){
	p=p->next;
	free(q);
	q=p;
	}
}

//对链表进行插入排序： 
/*struct ListNode* insertionSortList(struct ListNode* head) 
{
	//如果头节点为空或者只有一个节点，则直接返回头节点
	if ((head == NULL) || (head->next == NULL))
		return head;
	//开辟一个新的哨兵节点，其next存放头节点的地址
	struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
	newnode->next = head;
	//排序链表的最后一个节点
	struct ListNode* sortlast = head;
	struct ListNode* cur = head->next;
	//遍历链表所有节点
	while (cur)
	{
		//需要插入的结点val大于等于排序链表最后一个节点的val，直接进行头插，并更新sortlast
		if (cur->val <= sortlast->val)
		{
			sortlast->next = cur;
			sortlast = cur;
		}
		//从链表头开始寻找插入位置
		else
		{
			struct ListNode* pre = newnode;
			while (pre->next->val >= cur->val)
			{
				pre = pre->next;
			}
			sortlast->next = cur->next;
			cur->next = pre->next;
			pre->next = cur;
		}
		cur = sortlast->next;
	}
	return newnode->next;
}*/ 
