#include <iostream>
using namespace std;

struct node{
	int data;
	node *next;
	
	// ���캯�� 
	node(int data_, node *next_){
		data = data_;
		next = next_;
	}
}; 

int main(){
	node *phead = new node(0, NULL);
	node *p, *q;

	// ��ֹ������뻺����, �ȶ�����Ҫɾ����Ԫ��	
	printf("��������Ҫɾ����Ԫ�أ�");
	int x;
	cin>>x; 
 
	printf("�����������е�Ԫ�أ�");
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
	 
	printf("���������ʣ���Ԫ�أ�");
	p = phead;
	while (p->next != NULL) p = p->next, cout<<p->data<<" ";
	
	return 0;
}

