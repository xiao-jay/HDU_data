#include <iostream>
#include <cstring>
#include "Sen_Stack.h"
#define TElemtype char 
using namespace std;

class TreeList{
public:
	struct TNode{
		TNode *lchild;
		TNode *rchild;
		TElemtype data; 
	};	
	
	char letter[200]; //���ڴ�����ʽ�е���ĸ
	int lettertag[260]; //��Ԫӳ��(A->1, B->2, C->3)
	int num; //��Ԫ����:�����߼�������ʽ������Ҫ�ж� 2^num �� 
	TNode* root;
	
public:	
	
	void InitBTree(TNode* &T){
		for (int i = 0; i < 260; i++)
			lettertag[i] = -1;
		T = NULL;	
		num=0;
	}

	void DestroyBTree(TNode* &T){
	    if(T){
	    	DestroyBTree(T->lchild);
	        DestroyBTree(T->rchild);
	        delete T;
	    }
	    T = NULL;  
	}
	
	bool Judge_Punc(char &c){ 
	    switch(c){
	        case'&':
	        case'|':
	        case'~':
	        case'(':
	        case')':
	        case'=': return true;
	        default: return false;
	    }
	}
	
	bool Judge_Compare(char &c1, char &c2){ 
		//char &c2 > char &c1
	    switch (c2){
	    	case '|':
	        	if(c1 == '(') 
					return 0;
				else
					return 1;
	            break;
	          
			case '^':
            if(c1 == '(' || c1 == '|')
                return 0;
            else
                return 1;
            break;
			    
	        case '&':
	            if(c1 == '(' || c1 == '|' || c1 == '^')
	                return 0;
	            else
	                return 1;
	            break;
		
	        case '~':
	         	if(c1 == '(' || c1 == '|' || c1 =='^' || c1 == '&')
	                return 0;
	            else
	                return 1;
	            break;
	            
	        case '(':
	            return 1;
	            break;
	             
	        case ')':
	            return 0;
	            break;
	    }
	}
	 
	int Operator(int a, char punctutation, int b){
	    int c;
	    switch(punctutation){
	        case'|': 
	            c = a | b;
	            break;
	            
	        case'&': 
	            c = a & b;
	            break;
	    }
	    return c;
	} 
	
	void visit(TNode* &T, char c){
		printf("%c", c);
	}
	
	bool Pre_Calc(TNode* &T, int *a){
		if(T){
			if(T->data=='1')return 1;
			if(T->data=='0')return 0;
			if(~lettertag[T->data]) return a[lettertag[T->data]]; 
			if(T->data == '~') return !Pre_Calc(T->lchild, a);
			return Operator(Pre_Calc(T->lchild, a), T->data, Pre_Calc(T->rchild, a)); //�ݹ� 
		}
	} 
	
	//�ú�������ķ�ʽ�������ʽ�������ı��ʽֵ   
	void Calculation(TNode* &T, int num){
		int a[40];
		int res = 0;
		for(int n = 0; n < 1 << num; n++){
			for(int i = 0; i < num; i++)
				a[i] = n >> i & 1;
             res += Pre_Calc(T, a);
		}
		
		if(res == (1<<num))
			cout<<"True"<<endl;
		else if(res == 0)
			cout<<"False"<<endl;
		else cout<<"Satisfactible"<<endl;
	}
	
	TNode* New_Node(char c){ 
		TNode* p = new TNode;
		p->data = c;	
		p->lchild = p->rchild = NULL;
		return p;
	}
	
	bool Build_Tree(char *s){
		int length = strlen(s);
		Sen_Stack<TNode* > letterStack;
		letterStack.Init(length);
		Sen_Stack<TNode* > puncStack;
		puncStack.Init(length);
		
		for(int i = 0; i < length; i++){
			if(Judge_Punc(s[i])){
				if(s[i]==')'){
					while(!puncStack.Sen_Stack_Empty() && puncStack.Get_top()->data != '('){
						//ջ�����������ţ����һ��������Ͳ����� ������Ϊ����������letterStack�� 
						if(letterStack.length() < 2) return false;
						//��ֹջ��� 
						TNode *p = puncStack.Get_top();
						puncStack.pop();
						TNode *p1 = letterStack.Get_top();
						letterStack.pop();
						TNode *p2 = letterStack.Get_top();
						letterStack.pop();
						p->lchild = p2;
						p->rchild = p1;
						///��ʱp�����һ��combined letter
						letterStack.push(p);
					}
					puncStack.pop(); //����������
				}else{
					//���s[i]���������� �Ǿ��½�һ��'��'���  
					TNode *q = New_Node(s[i]);
					if(s[i]=='('){
						puncStack.push(q);
						continue;
					}
					
					while(!puncStack.Sen_Stack_Empty() && Judge_Compare(puncStack.Get_top()->data, q->data)){
						//�Ƚ��½��������ջ������������ȼ�
						//����puncStackջ�е�������������ȼ���������  
						if(letterStack.length() < 2) return false;
						TNode *p = puncStack.Get_top();
						puncStack.pop();
						TNode *p1 = letterStack.Get_top();
						letterStack.pop();
						TNode *p2 = letterStack.Get_top();
						letterStack.pop();
						p->lchild = p2;
						p->rchild = p1;
						letterStack.push(p);
						}
						puncStack.push(q); //���������ѹ��ջ 
						continue;
				}
				
			}else{
				//�´���Ĳ�������� �Ǳ�Ԫ 
				if(lettertag[s[i]] < 0 && s[i] != '1' && s[i] != '0'){
					lettertag[s[i]] = num++;
					letter[num-1] = s[i];
					//�����µ��߼����� 
				}
				
				TNode *p = New_Node(s[i]);
				letterStack.push(p);
				}
				
				while(!puncStack.Sen_Stack_Empty() && puncStack.Get_top()->data == '~'){
					//�����������:ȡ������ 
					TNode *p = puncStack.Get_top();
					puncStack.pop();
					TNode *p1 = letterStack.Get_top();
					letterStack.pop();
					p->lchild = p1;
					letterStack.push(p);
				}
		}
		
		while(!puncStack.Sen_Stack_Empty()){
			if(letterStack.length() < 2) return false;
			TNode *p = puncStack.Get_top();
			puncStack.pop();
			TNode *p1 = letterStack.Get_top();
			letterStack.pop();
			TNode *p2 = letterStack.Get_top();
			letterStack.pop();
			p->lchild = p2;
			p->rchild = p1;
			letterStack.push(p);
		}
		
		root = letterStack.Get_top();
		return true;
		//root���ڴ���ľ������Ա��ʽ 
	} 
	
	//����ݹ����������          
	void PreorderTraverse(TNode* &T){  
	    if(T){
	        if(T->data)
	            visit(T,T->data);
			PreorderTraverse(T->lchild);
	        PreorderTraverse(T->rchild);
	    }  
	} 
	
	//����ݹ����������    
	void InorderTraverse(TNode* &T){  
	    if(T){
	        InorderTraverse(T->lchild);
	        if(T->data)
	        	visit(T, T->data);
	        InorderTraverse(T->rchild);
	    }  
	}
	
	//����ݹ����������            
	void PostorderTraverse(TNode* &T){  
	    if(T){
	    	PostorderTraverse(T->lchild);
	        PostorderTraverse(T->rchild);
	        if(T->data)
	        	visit(T, T->data);
	    }  
	}
};

