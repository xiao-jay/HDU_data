//ptail->next=pnew;
//pnew->num=numb;
//ptail=pnew;
//ʵ�֣��ȰѾ�ָ��ptail������һλָ��pnew�������µ�ָ��pnew�������ݣ��ٰ�ptail��pnew�ŵ�һ�� ;��ȣ������������ 

#include<stdio.h>
#include<stdlib.h>

struct Node
{
	long long int data;
	int cnt;			
	struct Node *next;
};//����ÿ�����ݣ�ÿ�����ݵļ�����cnt��ָ����һ������ָ�� 

struct Node *p;
//��������ȫ�ֱ�����p�ᴩ�������򣻺���������ð�������㷨�� 
struct Node *Add(struct Node *head, int data); 
struct Node* Add_newhead(struct Node *preHead);
void Bubble_Sort(struct Node *head); 
void Destory(struct Node *head);

int main()
{
	struct Node *head=NULL; 
	//��ʼ������ͷָ���ǿյģ�����һ����ͷ�������� 
	long long int num;
	scanf("%d",&num); 
	while(num!= 0)
	{
		p=head;//����head 
		while(p!=NULL){
		if(p->data==num)
		{
			++p->cnt;
		}p=p->next;
	}//���ϼ����ﵽ��ÿ����һ�����ݣ��Ͱ�������ݴ���������в��Ҽ������������м��� 
		head=Add(head, num);
	 //��β���һ��ͷ��� 
		scanf("%d", &num);
	}head=Add_newhead(head);//����һ���µ�ͷ���
	
	Bubble_Sort(head);
	//��ĭ���򷨣�ʹ����������ɸ����Ӹߵ������ 
	
	struct Node *p=head->next;
	//ʹ��ȫ�ֱ���������:�ı�ָ��p��Ϊ�������̵� 
	
	while(p!=NULL)
	{
		printf("%d:%d\n", p->data, p->cnt);
		p=p->next;
	}//��ӡ���е�����
	 
	while(p != NULL)
	{
		struct Node *r=p;
		p=p->next;
	}head->next=NULL; 
	//��һ�������ݶ�ɾ�� 
	Destory(head);
	//�ͷ����� 
	return 0;
}//�˴���������˼�:1�������ָ��p��������struct�ṹָ�룻2������while���ܺϲ����������� �� 

struct Node *Add(struct Node *head,int num)
//��β���һ��ͷ��� 
{
	struct Node *pnew, *ppre; 
	pnew=(struct Node *)malloc(sizeof(struct Node));
	//��malloc������һ���洢�ռ� 
	pnew->data=num;
	pnew->cnt=1;
	//���Ǹ������������������У�������Ϊ1 
	if(head==NULL)
	{
		head=pnew;
		head->next=NULL;
	}//���head�ǿյģ���ô�Ͱ�pnew��ֵ��head������һ��head�ٱ�ɿյģ���ͷ��㣩 
	else if(pnew->data > head->data)
		{
			pnew->next=head;
			head=pnew;
		}//���pnew��ŵ����ݴ���head�д�ŵ����ݣ���ô��head��ǰ��һ����Ϊ��һ��pnew�����Ű�pnew��ֵ����head  
		else
		{
			p=head;
			while(p!=NULL && pnew->data < p->data)
			{
				ppre=p;
				p=p->next;
			}//���p������pnew������С��p�����ݣ���ô��p�����ݸ���ppre���ɵģ����ٰ�ָ��ָ����һ�� ���ﵽ����С�����ŵ�ǰ���Ч�� 
			if(p==NULL || pnew->data > p->data )
				{
					pnew->next=p;
					ppre->next=pnew;
				}//���p�ǿյĻ���pnew�����ݴ���p�����ݣ���ô��p��ֵ�����¸�pnew��pnew��ֵ�����¸�ppre���ﵽ���Ѵ�����������Ե�Ч��			
		}
	return head;
}

struct Node* Add_newhead(struct Node *preHead)
{
	struct Node* newHead = (struct Node*)malloc(sizeof(struct Node));
	//��malloc������һ���洢�ռ� 
	newHead->cnt=0;
	newHead->next = preHead;
	//�µ�ͷ����Ϊ0���������У���һ���µ�ͷָ�����֮ǰ�ɵ�ͷָ�� 
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
	}//����һ����������ж��ٸ��洢������ 
	for(j=0; j<count-1; j++)
	{
		num=count-j-1;
		p=head->next;
		r=p->next;
		tail=head; 
//�γɣ�tail p q ������Ԫ��˳�� 
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
		 } //����Ҫ�����Ԫ���У����αȽ��������ڵ�Ԫ�أ����˳�����Ͱ����ǽ����������߷�Ԫ�صĹ������ظ��ؽ���ֱ��û������Ԫ����Ҫ������Ҳ����˵��Ԫ�����Ѿ�������ɡ� 
	} //ð�������㷨��ÿһ�ֶ�Ҫ����һ�����е�Ԫ�أ���ת�Ĵ�����Ԫ�������൱������ʱ�临�Ӷ�ΪO(N^2)�� 
}//�ο���ַ��https://blog.csdn.net/lu_1079776757/article/details/80459370 

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

//��������в������� 
/*struct ListNode* insertionSortList(struct ListNode* head) 
{
	//���ͷ�ڵ�Ϊ�ջ���ֻ��һ���ڵ㣬��ֱ�ӷ���ͷ�ڵ�
	if ((head == NULL) || (head->next == NULL))
		return head;
	//����һ���µ��ڱ��ڵ㣬��next���ͷ�ڵ�ĵ�ַ
	struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
	newnode->next = head;
	//������������һ���ڵ�
	struct ListNode* sortlast = head;
	struct ListNode* cur = head->next;
	//�����������нڵ�
	while (cur)
	{
		//��Ҫ����Ľ��val���ڵ��������������һ���ڵ��val��ֱ�ӽ���ͷ�壬������sortlast
		if (cur->val <= sortlast->val)
		{
			sortlast->next = cur;
			sortlast = cur;
		}
		//������ͷ��ʼѰ�Ҳ���λ��
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
