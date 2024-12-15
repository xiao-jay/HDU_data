#include <iostream>
using namespace std;

/*
测试样例:
(包含: 一个链表中的重复幂数情况(幂数随机排列)、两个链表长短不一情况、输出运算的化简情况) 
1 x^2 + 2 x^0 + 1 x^2 
2 x^1 + (-2) x^0 + 1 x^1 + 3 x^3 
*/ 

typedef struct node{
	// xs = 系数
	int xs;		
	// ms = 幂(指)数 
	int ms;		 
	struct node *next;	
	
	// 构造函数 
	node(int xs_, int ms_, node *next_){
		xs = xs_;
		ms = ms_;
		next = next_;
	}
}node, *Lb;

bool create(Lb *phead);
bool add(Lb *L1, Lb *L2);
void show(Lb L);
void show_(Lb L);

bool create(Lb *phead){
	// 创建的链表自带降幂 
	*phead = new node(0, 0, NULL);	
	node *p, *q;
			 
	char f;
	int cnt = 0;	
	while(1){
		cin>>f;
		cout<<"Go ahead or press 'F' to stop.";
		if(f == 'F'){
			cout<<"List has created.\n"; 
			break;		
		}
		
		
		node *temp = new node(0, 0, NULL); 
		cout<<"Enter the "<<cnt<<"th data's 系数: ", cin>>temp->xs;
		cout<<"Enter the "<<cnt<<"th data's 幂数: ", cin>>temp->ms;
		
		p = *phead, q = (*phead)->next;	
		if(cnt == 0){
			p->next = temp, temp->next = q, p = temp;
		}else{ 
			while(q != NULL && q->ms > temp->ms) p = q, q = q->next;
			if(q == NULL){
				p->next = temp, temp->next = q;
			}else if(q->ms == temp->ms){
				int sum = q->xs + temp->xs;
				q->xs = sum;
			}else{
				p->next = temp, temp->next = q;	
			}
		}	
		cnt++;		 
	}
	return true;
}

bool add(Lb *L1, Lb *L2){
	// 降幂->直接连 
	node *p1 = (*L1)->next;		
	node *p2 = (*L2)->next;	
	node *ans = *L1;	
	
	while(p1 && p2){	
		if(p1->ms == p2->ms){
			int sum = p1->xs + p2->xs;	
			if(sum != 0){
				p1->xs = sum, ans->next = p1, ans = p1;		
				p1 = p1->next, p2 = p2->next;		
			}else{
				p1 = p1->next, p2 = p2->next;	
			} 
		}else if(p1->ms < p2->ms){
			ans->next = p2, ans = p2;		 
			p2 = p2->next;	 
		}else{
			ans->next = p1, ans = p1;		
			p1 = p1->next;		
		}
	}
	 
	if(p1) ans->next = p1;	 
	else ans->next = p2;	
}

void show(Lb L){
	node *pshow = L->next;
	if(!pshow) cout<< "The list is EMPTY!\n";
	while(pshow){
		if(pshow->next != NULL) cout<<pshow->xs<<" * x ^ "<<pshow->ms<<" + ";
		else cout<<pshow->xs<<" * x ^ "<<pshow->ms;
		pshow = pshow->next;	
	}
	cout<<endl;
}

void show_(Lb L){
	node *pshow = L->next;
	if(!pshow) cerr << "This is an empty List.\n";
	while(pshow){
		if(pshow->next){
			if(pshow->xs == 0){
				pshow = pshow->next;	
				continue;
			}else if(pshow->ms == 0){
				cout << pshow->xs << " + ";
			}else if(pshow->xs == 1 && pshow->ms == 1){
				cout << "x + ";
			}else if(pshow->xs == 1 && pshow->ms != 1){
				cout << "x^" << pshow->ms << " + ";
			}else if(pshow->ms == 1){
				cout << pshow->xs << "x" << " + ";
			}else cout << pshow->xs << "x^" << pshow->ms << " + ";
		}else{
			if(pshow->xs== 0) cout << pshow->xs;
			else if(pshow->ms == 0){
				cout << pshow->xs;
			}else if(pshow->xs == 1 && pshow->ms == 1)	  {
				cout << "x";
			}else if(pshow->xs == 1 && pshow->ms != 1){
				cout << "x^" << pshow->ms;
			}else if(pshow->ms == 1){
				cout << pshow->xs << "x";
			}else cout << pshow->xs << "x^" << pshow->ms;
		}
		pshow = pshow->next;	
	}
	cout << endl;
}

int main(){
	Lb L1, L2;
	cout<<"Please create L1.\n";
	create(&L1);
	cout<<"Please create L2.\n";
	create(&L2);
	cout<<"L1 is: ";
	show(L1);
	cout<<"L2 is: ";
	show(L2);
	cout<<"L1 + L2 is: ";
	add(&L1, &L2);
	show_(L1);
	
	// 释放内存
	delete L1, L2;
	return 0;
}

