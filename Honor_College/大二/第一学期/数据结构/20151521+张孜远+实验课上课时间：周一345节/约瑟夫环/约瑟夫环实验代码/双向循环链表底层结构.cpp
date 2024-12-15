#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

template <typename T>
class Reversed_Basic_LinkList;
template <typename T>
ostream &operator <<(ostream& out, Reversed_Basic_LinkList<T>& rhs);

template<typename T>
class Reversed_Basic_LinkList{
public:
	//构造函数 
	Reversed_Basic_LinkList(){
		phead = new Node(0, 0, NULL);
		phead->pre = phead;
		phead->next = phead;
	}
	
	//清空链表操作 
	void clear()
	{
		Node *p = phead;
		while (phead->next != phead)
		{
			p = phead->next;
			phead->pre->next = p;
			p->pre = phead->pre;
			phead = p;	
		}
		delete phead;
		phead = NULL;
	}
	
	//析构函数 
	virtual ~Reversed_Basic_LinkList(){
		clear();
	}
	
	//求不带头结点的循环单链表长度
	int Reversed_Basic_LinkList_length() 
	{   
	    if (!phead)  
	        return 0;
	    int count = 1;
	    Node *p = phead;
	    while (p->next != p)
	    {
	        p = p->next;
	        count++;
	    }
	    return count;
	}
	
	bool GetElem(Reversed_Basic_LinkList L, T &e, int i)
	{
	    if ( i < 1 || !L.phead )  
	        return false;
	    Node *p = L.phead; 
	    if ( i == 1 )
			e = p->data;
	    else{     
			int length = Reversed_Basic_LinkList_length();  
	        if (i > length) return false;
			else{
				while (i > 1){
	        		p = p->next;
	        		i--;
				}    
				e = p->data;
			} 
	    }
	    return true;
	}
	
	//在不带头结点的循环单链表中第i个数据元素之前插入新的数据元素e
	bool ListInsert(Reversed_Basic_LinkList &L, int i, T e){         
	    if (i < 1 || !L.phead) 
	        return false;
	    Node *p = L.phead;
	    int length = Reversed_Basic_LinkList_length();
    	if (i > length) return false;
    	else{
    		int j = 0;
    		if (i < length - i){
	    			while (j < i - 1){
	    				p = p->next;
	    				j++;
					}
				}else{
					while (j < length - i - 1){
						p = p->pre;
						j++;
					}
				} 
			Node *rub;
			rub = new Node(p->pre->number+1, e, NULL);
			rub->pre = p->pre;
			p->pre->next = rub;
			rub->next = p;
			p->pre = rub;
		}
	} 
	
	// 在非空循环单链表中删除第i个数据元素 
	bool ListDelete(Reversed_Basic_LinkList &L, int i, T &e )
	{   
		int length = Reversed_Basic_LinkList_length();
		Node *p;
	    p = L.phead;
	    if ( i < 1 || !L.phead ) 
	        return false;
	    if (i == 1 && length == 1){
	    	delete p; 
			p = NULL; 
	    }else{
	    	if (i > length) return false;
	    	else{
	    		int j = 0;
	    		if (i < length - i){
	    			while (j < i - 1){
	    				p = p->next;
	    				j++;
					}
				}else{
					while (j < length - i - 1){
						p = p->pre;
						j++;
					}
				}
	        	// 删除第i个位结点 
	        	Node *rub = p->next;
	        	p->next = rub->next;
	        	rub->next->pre = rub->pre;
	        	delete rub; 
				}                      
	    }
	    return true;        
	}
	
	//从第一个位置起查找与e匹配的数据元素，若存在则返回该数据元素的位置   
	int LocateElem(Reversed_Basic_LinkList &L, T &e, bool( *Compare )(T &e1, T &e2))
	{
	    if (! L.head)  
	        return 0;
	    Node *p = L.phead;
	    int cnt = 1;
	    while (p->next != p && !Compare(p->data, e)){
	    	cnt++;
	    	p->next = p;
		}
	    if (Compare(p->data, e))
	        return cnt;
	    else
	        return 0;
	}
	
	// 依序对单链表中的每个数据元素进行遍历，遍历到每个数据元素时调用函数visit()一次且仅一次
	void ListTraverse(Reversed_Basic_LinkList &L, void( *Visit )(T &e)) 
	{
	    Node *p = L.head;
	    if (p){
	        while (p->next != p){
	            Visit(p->data);
	            p = p->next;
	        }
	        Visit(p->data);
	    }
	} 
	
	//复制构造函数  深拷贝 
	Reversed_Basic_LinkList(const Reversed_Basic_LinkList <T> &rhs)
	{
		phead = new Node(0, 0, NULL);
		Node *p = phead;
		Node *q = rhs.phead;
		Node *rub;
		while(rhs.phead != NULL)
		{
			rub = new Node(q->number, q->data, NULL);
			p->next = rub;
			rub->pre = p;
			rub->next = phead;
			phead->pre = rub;
			p = rub;
			q = q->next;
		}	
		rub = new Node(q->number, q->data, NULL);
		p->next = rub;
		rub->pre = p;
		rub->next = phead;
		phead->pre = rub;
    }

	//移动构造函数 浅拷贝 
	Reversed_Basic_LinkList(Reversed_Basic_LinkList <T> &&rhs) noexcept{
		phead = rhs.phead;
		rhs.phead = NULL;
	}
	
	//empty
	bool empty()
	{
		if(phead) return false;
		else return true;
	}
	
	//复制赋值运算符
	Reversed_Basic_LinkList &operator =(const Reversed_Basic_LinkList &rhs)
	{
		if (this == &rhs) return *this;
		if (phead) delete[]phead; 
		Node *p = phead;
		Node *q = rhs.head;
		Node *rub;
		while(rhs.phead != NULL)
		{
			rub = new Node(q->number, q->data, NULL);
			p->next = rub;
			rub->pre = p;
			rub->next = phead;
			phead->pre = rub;
			p = rub;
			q = q->next;
		}	
		rub = new Node(q->number, q->data, NULL);
		p->next = rub;
		rub->pre = p;
		rub->next = phead;
		phead->pre = rub;
		return *this;
	 }
	 
	//移动赋值运算符
	Reversed_Basic_LinkList &operator =(Reversed_Basic_LinkList <T> &&rhs) noexcept{ 
		Node *p = this->phead;
		this->phead = rhs.phead; 
		rhs.phead = p;
		return *this;
		rhs.clear();
	}
	
	//输出流重载 
	friend ostream &operator <<(ostream &os, Reversed_Basic_LinkList<T> &rhs)
	{
		Node *p  = rhs.phead;
		Node *q = p; 
		while (p->next != p){
			os<<"第"<<p->number<<"位玩家出局，其所携带的密码数是"<<p->data; 
			q = p->next;
			delete p;
			p = q;
		}
		os<<"第"<<p->number<<"位玩家出局，其所携带的密码数是"<<p->data; 
		return os<<endl;
	}
	
private:
	struct Node{
		T number;
		T data;
		Node *pre;
		Node *next;
		Node(){} //无参构造 
		Node(Node *p, Node *q):pre(p), next(q){}
		Node(T x, T y, Node *p, Node *q):number(x), data(y), pre(p), next(q){}
	};
	Node *phead;
};


 
