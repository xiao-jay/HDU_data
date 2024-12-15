#include<cstdio> 
template<typename T>
class Sen_Stack;

template<typename T>
class Sen_Stack{
public:
	void Init(int n){
		base = new T[n];
		size = n;
		_top = 0;
	}
	
	void clear(){
		_top = 0;
	}
	
	void Destroy(){
		delete[] base;
		size = 0;
		_top = 0;
	}
	
	int length(){
		//ջ��Ԫ�صĸ��� 
		return _top;
	}
	
	T Get_top(){
		//��ȡջ��Ԫ�� 
		if (Sen_Stack_Empty()) return NULL;
		else return base[_top - 1];
	} 
	
	bool push(T x){
		if (_top >= size){
			T *newbase;
	        newbase = new T[size+10];
	        for(int j = 0; j < _top; j++) 
	            newbase[j] = base[j];   
	        delete[] base;
	        base = newbase;
		    size += 10;
		    //���� 
		}else{
			base[_top++] = x;
			return true;		
		}
	}
	
	bool pop(){
		if(Sen_Stack_Empty()) return false;
		else{
			--_top;
			return true;	
		} 	
	}
	
	bool Sen_Stack_Empty(){
		return _top == 0;
	}
	
protected:
	T* base;
	int _top; //ջ��ָ���λ�� 
	int size; //ջ��������� 
}; 
