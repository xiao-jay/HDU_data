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
	//���캯�� 
	Reversed_Basic_LinkList(){
		phead = new Node(0, 0, NULL);
		phead->pre = phead;
		phead->next = phead;
	}
	
	//���������� 
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
	
	//�������� 
	virtual ~Reversed_Basic_LinkList(){
		clear();
	}
	
	//�󲻴�ͷ����ѭ����������
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
	
	//�ڲ���ͷ����ѭ���������е�i������Ԫ��֮ǰ�����µ�����Ԫ��e
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
	
	// �ڷǿ�ѭ����������ɾ����i������Ԫ�� 
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
	        	// ɾ����i��λ��� 
	        	Node *rub = p->next;
	        	p->next = rub->next;
	        	rub->next->pre = rub->pre;
	        	delete rub; 
				}                      
	    }
	    return true;        
	}
	
	//�ӵ�һ��λ���������eƥ�������Ԫ�أ��������򷵻ظ�����Ԫ�ص�λ��   
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
	
	// ����Ե������е�ÿ������Ԫ�ؽ��б�����������ÿ������Ԫ��ʱ���ú���visit()һ���ҽ�һ��
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
	
	//���ƹ��캯��  ��� 
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

	//�ƶ����캯�� ǳ���� 
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
	
	//���Ƹ�ֵ�����
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
	 
	//�ƶ���ֵ�����
	Reversed_Basic_LinkList &operator =(Reversed_Basic_LinkList <T> &&rhs) noexcept{ 
		Node *p = this->phead;
		this->phead = rhs.phead; 
		rhs.phead = p;
		return *this;
		rhs.clear();
	}
	
	//��������� 
	friend ostream &operator <<(ostream &os, Reversed_Basic_LinkList<T> &rhs)
	{
		Node *p  = rhs.phead;
		Node *q = p; 
		while (p->next != p){
			os<<"��"<<p->number<<"λ��ҳ��֣�����Я������������"<<p->data; 
			q = p->next;
			delete p;
			p = q;
		}
		os<<"��"<<p->number<<"λ��ҳ��֣�����Я������������"<<p->data; 
		return os<<endl;
	}
	
private:
	struct Node{
		T number;
		T data;
		Node *pre;
		Node *next;
		Node(){} //�޲ι��� 
		Node(Node *p, Node *q):pre(p), next(q){}
		Node(T x, T y, Node *p, Node *q):number(x), data(y), pre(p), next(q){}
	};
	Node *phead;
};


 
