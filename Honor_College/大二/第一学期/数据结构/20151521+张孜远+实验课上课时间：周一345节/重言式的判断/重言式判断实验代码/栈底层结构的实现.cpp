#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

template <typename T>
class CStack;
template <typename T>
istream &operator >>(istream& is, CStack<T>& rhs);
template <typename T>
ostream &operator <<(ostream& out, CStack<T>& rhs);

template<typename T>
class CStack{
public:
	//构造函数 
	CStack(){
		phead = new Node(0, NULL);
	}
	
	//清空链表操作 
	void clear()
	{
		Node *p = phead;
		while (phead != NULL)
		{
			p = p->next;
			delete phead;
			phead = p;	
		}
	}
	
	//析构函数 
	virtual ~CStack(){
		clear();
	}
	
	//复制构造函数  深拷贝 
	CStack(const CStack <T> &rhs)
	{
		phead = new Node(0,NULL);
		Node *p = phead;
		Node *q = rhs.phead;
		while(rhs.phead != NULL)
		{
			p->next = new Node(q->next->data, NULL);
			p = p->next;
			q = q->next;
		}	
    }

	//移动构造函数 浅拷贝 
	CStack(CStack <T> &&rhs) noexcept{
		phead = rhs.phead;
		rhs.phead = NULL;
	}
	
	//Push
	void push(const T &x)
	{
		Node *p = phead;
		while (p->next != NULL) p = p->next;
		p->next = new Node(x, NULL);
	}
	
	//pop
	void pop()
	{
		Node *p = phead;
		while (p->next->next != NULL)
			p = p->next;	
		delete p->next, p->next = NULL;
	}
	
	//top
	const T& top()const
	{
		Node *p = phead;
		while (p->next != NULL) p = p->next;
		return p->data;
	}
	
	//empty
	bool empty()
	{
		if(phead->next) return false;
		return true;
	}
	
	//用链表写stack不会出现stack full的情况（链表动态分配空间） 
	
	//复制赋值运算符
	CStack &operator =(const CStack &rhs)
	{
		if (this == &rhs) return *this;
		if (phead) delete[]phead; 
		Node *p = phead;
		Node *q = rhs.head;
		while(rhs.phead != NULL)
		{
			p->next = new Node(q->next->data, NULL);
			p = p->next;
			q = q->next;
		}	
		return *this;
	 }
	 
	//移动赋值运算符
	CStack &operator =(CStack <T> &&rhs) noexcept{ 
		Node *p = this->phead;
		this->phead = rhs.phead; 
		rhs.phead = p;
		return *this;
		rhs.clear();
	}
	
	//输入输出流重载 
	friend istream &operator >>(istream &is, CStack<T> &rhs)
	{
		rhs.clear();
		rhs.phead = new Node(NULL);
		T x;
		Node *p = rhs.phead;
		while (is >> x)
		{
			p->next = new Node(x,NULL);
			p = p->next;
		}
		return is;
	}
	
	friend ostream &operator <<(ostream &os, CStack<T> &rhs)
	{
		int count = 0; 
		do{
			Node *p = rhs.phead;
			while (p->next->next != NULL) p = p->next, count++;
			os << fixed << setprecision(2) << setw(4) << p->next->data; //空四格
			delete p->next, p->next = NULL, count = 0;
		}while(count >= 0);
		return os << endl;
	}
	
private:
	struct Node{
		T data;
		Node *next;
		Node(){} //无参构造 
		Node(Node *p):next(p){}
		Node(T x, Node *p):data(x),next(p){}
	};
	Node *phead;
};

int main(void){
	//输入1 5 3 9 2 5 输出 5 2 9 3 5 1 
	CStack<int>c;
	int rubbish;
	while (cin>>rubbish) c.push(rubbish);
	//c.push(3);
	//c.pop();	
	cout<<c;
	
	return 0;
}
