#include <cstdio>
#include <cstdlib> 
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
class RecycList;

template <typename T>
struct Node{
	Node(int _num, int _data):num(_num), data(_data), pre(NULL), next(NULL){}
	int num;
	T data;
	Node<T> *pre, *next;
}; 

template <typename T>
class RecycList{
public:
	RecycList(int nums[], int length){
		phead = new Node<T> (0, nums[0]);
		if (phead == NULL){
			cout<<"There is no empty space.";
			return;	
		}
		phead->next = phead;
		phead->pre = phead;
		
		Node<T> *p = phead;
		for (int i = 1; i < length; i++){
			Node<T> *rub = new Node<T>(i, nums[i]);
			if (rub == NULL){
				cout<<"There is no empty space.";
				return;
			}
			p->next = rub, rub->pre = p;
			rub->next = phead, phead->pre = rub;
			p = rub;
		}
	}
	
	int Node_delete(int length, int m, Node<T> *p){
		m = (p->data - 1) % length;
		p->pre->next = p->next;
		p->next->pre = p->pre;
		delete p;
		return m;
	}
	
	void Node_move(int length, int m){
		Node<T> *p;
		p = phead; 
		
		if (m <= 0) return;
		else m = (m - 1) % length;
	
		while (p->next != p){
			if (length >= m * 2){
				//�ж�����:length - m >= m ָ������ƶ�,������ǰ�ƶ� 
				for (int i = 1; i <= m; i++) p = p->next;
				cout << setw(4) << setfill(' ') << p->num+1 << endl;
				length--;
				Node<T> *q = p->next;
				m = Node_delete(length, m, p);
				p = q;
			}else{
				for (int i = 1; i <= length - m; i++) p = p->pre;
				cout << setw(4) << setfill(' ') << p->num+1 << endl;
				length--;
				Node<T> *q = p->next;
				m = Node_delete(length, m, p);
				p = q;
			}
		}
		cout<<p->num+1<<endl;
		delete p;
	}  
	
	Node<T> *get_phead(void){
		return phead;
	}
	
	void clear(){
		while (phead->next != phead){
			Node<T> *p = phead->next;
			delete phead;
			phead = p;
		}
	}
	
	bool empty(){
		return phead == NULL;
	}
	
private:
	Node<T> *phead;
};
