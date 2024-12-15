#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 命令行参数

int main(int argc, char *argv[]){
	// 需要给主函数赋予两个形参: 名字可以变，但变量类型不行 
	puts(argv[0]);
	puts(argv[1]);
	printf("argc = %d\n", argc);
	if (argc != 2){
		printf("Invalid Argument Count.\n");
		exit(0);
	}
	
	// 指针数组第一个（指向的是命令行中的字符串常量，本身内容不能被修改） 
//	deldigit(argv[1]);
//	puts(argv[1]); 
	// 下面这种写法才是正确的 
	char s[80];
	strcpy(s, argv[1]);
	deldigit(s);
	puts(s); 
	 
	 
	
	char s1[80] = "jdiojawiod", s2[] = "73883";
	char *p;
	char ch; 
	p = strcat(s1, s2);
	// 返回拼接后结果的第一个字符 
	ch = *strcat(s1, s2);
	puts(p);
	putchar(ch); 
	return 0;
	// 返回给 DOS 
} 

char *mystrcat(char *s, char *t){
	char *p;
	for (p = s; *s != '\0'; s++)
	for (; *t != '\0'; s++, t++)
		*s = *t;
	*s = '\0';
	return p;
}

char *search(char *s, char *sname[], int n){
	int i;
	for (i = 0; i < n; ++i)
		if (strcmp(s, sname[i]) == 0)
			// 返回已找到的字符串指针？？？ 
			// 返回的是值（返回的是指针值——地址值）
			// 返回值只能作为右值不能作为左值 
			return sname[i];
	return NULL;
} 

int func(int n){
	if (n == 1) f(1) = 1;
	// 这是错误的，f(n) 不能作为左值 
	else f(n) = f(n - 1) * n;
	return f(n);
} 

// 函数指针
int func(int n){
	if (n == 0 || n == 1) return 1;
	else return func(n - 1) * n;
} 
 
int main(){
	int n, f;
	scanf("%d", &n);
	// 指针指向函数（老版本） 
//	int (*p)();
	// 新版本：给出形参（和个数？）
	// 形参是int，返回类型也是int 
	int (*p)(int); // 野指针 
	// int *p(int): 这是一个函数的声明；类比：char *mystrcat(char *, char *)：函数声明的时候不用给出形参的名字 
	p = func; // 体现灵活性 
//	f = func(n);
	f = p(n);
	printf("func = %d\n", f);
	return 0;
} 

// stack给内部变量分配空间，heap（堆） 给全局变量分配空间
// 在一个作用域内函数名是唯一的，通过函数名区分函数指针 

template <typename T> 
int greater(T x, T y){
	return x > y;
}

int less(int x, int y){
	return x < y;
}

int absgreater(itn x, int y){
	return abs(x) > abs(y);
}

template <typename T> 
//void bubble(int x[], int n, int (*f)(int, int)){
void bubble(T x[], int n, int (*f)(T, T)){
	int i, j;
//	int temp;
	T temp;
//	int *p, *q;
	T *p, *q;
	for (i = 0; i < n - 1; +i){
		for (p = x, q = x + 1, j = 0; j < n - i - 1; ++p, ++q, ++j){
			if (f(*p, *q)){
				temp  = *p;
				*p = *q;
				*q = temp; 
			}
		}
	}
	
} 

int main(){
	// f相当于是类模板的感觉 ---> 泛型 generic 
	bubble(a, 5, greater);
	bubble(a, 5, less);
	bubble(a, 5, absgreater);
}

#include <stdio.h>
#include <math.h>
double integral(double a, double b, double (*f)(double)){
	double s0, s1;
	double h, x;
	int n, i;
	h = b - a;
	n = 1;
	s1 = (f(a) + f(b)) * h / 2.0;
	x = a;
	do {
		s0 = s1;
		h = h / 2.0;
		n = n * 2;
		s1 = 0.0;
		for (i = 1; i <= n; ++i){
//			s1 += (f(a + i * h) + f(a + (i + 1) * h)) * h / 2.0;
			s1 += (f(x) + f(x + h)) * h / 2.0;
			x += h;
		}
		s1 = (f(a) + f(b)) * h / 2.0;
	}while (fabs(s1 - s0) > 1e-10)
	return s1;
}

double f1(double x){ return x;}

int main(){
	printf(".10lf\n", integral(0, 1, f1));
	return 0;
}



