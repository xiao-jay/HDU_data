#include <iostream>
using namespace std;

struct node{
	int data;
	node *next;
	
	// 构造函数 
	node(int data_, node *next_){
		data = data_;
		next = next_;
	}
}; 

int main(){
	node *phead = new node(0, NULL);
	node *p, *q;

	// 防止清空输入缓存区, 先读入需要删除的元素	
	printf("请输入需要删除的元素：");
	int x;
	cin>>x; 
 
	printf("请输入链表中的元素：");
	int digit;
	while (cin>>digit){
		p = new node(digit, NULL), q = phead;
		while (q->next != NULL) q = q->next;
		q->next = p;
	}
	
	p = phead;
	while (p->next->next != NULL){
		if (p->next->next->data == x){
			q = p->next, p->next = p->next->next, q->next = NULL;
			delete(q);
		}else p = p->next;
	}
	 
	printf("输出链表中剩余的元素：");
	p = phead;
	while (p->next != NULL) p = p->next, cout<<p->data<<" ";
	
	return 0;
}

