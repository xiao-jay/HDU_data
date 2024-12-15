#include <stdio.h>
#include <stdlib.h>
#define N 10000

int main(){
	int a = 1, b;
	int *p; // 指针变量（变量！！！）——野指针; *仅仅是一个语法的形式 
	// ------> int *p = &a; // 把a的首地址赋值给了p 
	p = p + 100;
	p = (int *)0x114514;
	// 这些都是对p这个指针变量的赋值操作，有了指针变量，内存的空间你都能操作了，一旦有操作失误的地方，就会造成内存的非法访问 
	 
	printf("a = %d\n", a);
	p = &a; // a是变量，&a是变量的指针，把变量的指针赋值给了一个指针变量p，那么这个指针变量p就是一个指向变量的指针变量 
    b = *p + 1; // 如果不对指针变量p赋值，那就会导致内存的非法访问 
//    b = a + 1;
	// *p + 1 比 a + 1的效率更低，可读性更差 
	p = &b;
	*p = a + 1; // 写入数据 
	printf("b = %d\n", b);
	return 0;
} 

// 地址传递
void swap1(int x, int y){
	int temp;
	temp = x;
	x = y;
	y = temp;
} 

void swap2(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
} 

// &在表达式或者语句的时候，才是取地址运算符；出现在变量定义的地方就是引用 
void swap3(int &x, int &y){
	int temp;
	temp = x;
	x = y;
	y = temp;
} 

int main(){
	int a = 1, b = 2;
	swap1(a, b);
	printf("a = %d, b = %d\n", a, b);
	// 这样ab两个数的值换不过来
	
	swap2(&a, &b); // 这样的传递方式是值传递，只是传递的值是地址 ——by value 
	printf("a = %d, b = %d\n", a, b); 
	// 这样ab两个数的值换得过来
	
	swap3(a, b); // 这样的传递方式是地址传递，即把ab的地址给xy，xy就是ab的别名 ——by reference 
	printf("a = %d, b = %d\n", a, b); 
	// 这样ab两个数的值换得过来
	return 0;
}

// 求数组中的max和min
void maxmin(int x[], int n, int *pmax, int *pmin){
	int i = 0;
	*pmax = *pmin = x[0];
	for (i = 1; i < n; ++i){
		if (x[i] > *pmax) *pamx = x[i];
		if (x[i] < *pmin) *pmin = x[i];
	}
} 

int main(){
	int a[] = {3, 5, 4, 1, 2};
	int max, min;
	maxmin(a, 5, &max, &min); // 传递指针 
	printf("max number = %d, min number = %d\n", max, min);
	return 0;
}

// C++ 中认为 int* 是一个整体的数据类型
// 指针法访问（多维）数组 
int main(){
	// 数组名本身不是一个变量（只有变量才能做左值），是一个变量的指针（地址）
	int a[] = {1, 2, 3, 4 ,5};
	int *p; // 遍历指针p 
	int i = 0, sum = 0;
	for (i = 0, p = a; i < 5; ++i, ++p)
//		sum += a[i];
//		sum += *(a + i); // i就是偏移量，这个是下标法的实质 
		sum += *p;
	printf("sum = %d\n", sum);
	return 0;
}
 
// *p++: ++的运算符优先级和*的运算符优先级一样高（二级），这个时候就触发了右结合的规则
// 所以*p++的本质就是，先p++，再取*(p++) 
// (*p)++的意思是：取出a[0]的值，不断改变a[0]的值（每次+1），不断取a[0]的值，所以最后的结果是：3+4+5+6+7

// 伪指针法：*(a + i)，这个本质就是下标法 
// 指针法
for (p = a; p < a + 5; p++) sum += *p; 
// 例子：
// 求数组中的max和min（指针法） 
void maxmin(int x[], int n, int *pmax, int *pmin){
	// int x[] == int *x
//	int i = 0;
//	*pmax = *pmin = x[0];
//	for (i = 1; i < n; ++i){
//		if (x[i] > *pmax) *pamx = x[i];
//		if (x[i] < *pmin) *pmin = x[i];
//	}
	int *p;
	// p可以不要，让x作为搜寻指针，自己挪 
//	pmax = pmin = x; // a[0]又放了最大值，又放了最小值，运行结果不对
	int *p1, *p2;
	p1 = p2 = x; 
	for (p = x + 1; p < x + n; ++p){ // p <= x + n - 1
	// x作为数组的起始地址，一般不建议改动x的位置 
//	for (x = x + 1, i = 1; i < n; x++, i++) 
		if (*p > *pmax) *pamx = *p;
		if (*p > *p1) p1 = p;
//		if (*x > *p1) p1 = x;
		if (*p < *pmin) *pmin = *p;
		if (*p < *p2) p2 = p;
//		if (*x < *p2) p2 = x;
	}
	*pmax = *p1, *pmin = *p2;
	// 如果写成 pmax = p, pmin = p 不对的原因就是，生存域结束了，即使记录了最大值和最小值，也传不回来	
}  

// 这么写也是不对的，因为只记录x和y的值，在生存域结束之后那也就结束了，传不回去 
void swap4(int *x, int *y){
	int *temp;
	temp = x;
	x = y;
	y = temp;
} 

void swap4(int *x, int *y){
	// 交换的是值 
	int *temp; // temp是野指针，temp指向谁？——内存的非法访问 
	*temp = *x;
	*x = *y;
	*y = *temp;
} 

int main(){
//	swap4(&a, &b); 
	swap5(&a, &b);
	return 0;
}
 
// 冒泡排序
void bubble(int x[], int n){
	int i, j;
	int temp;
	
	for (i = 0; i < n - 1; ++i){
		for (j = 0; j < n - 1- i; ++j){
			if (x[j] > x[j + 1]){
				temp = x[j];
				x[j] = x[j + 1];
				x[j + 1] = temp;
			}
		}
	}
	
	//	int *p;
	int *p1, *p2;
	int temp;
	for (int i = 0; i < n - 1; ++i){
		for (p1 = x, p2 = x + 1, j = 0; j < n - 1 - i; j++, p1++, p2++){
			if (*p1 > *p2){
//				*p = *p1;
				temp = *p1;
				*p1 = *p2;
//				*p2 = *p;
				*p2 = temp;
			}
		}
	}
} 

int main(){
	int a[] = {1, 3, 5, 4, 2};
	bubble(a, 5);
	for (int i = 0; i < 5; ++i){
		printf("%d ", a[i]);
	}
	return 0;
}



