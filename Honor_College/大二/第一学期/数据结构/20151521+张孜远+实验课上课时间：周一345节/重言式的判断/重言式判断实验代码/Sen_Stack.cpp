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
		//栈内元素的个数 
		return _top;
	}
	
	T Get_top(){
		//获取栈顶元素 
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
		    //扩容 
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
	int _top; //栈顶指针的位置 
	int size; //栈的最大容量 
}; 
