#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//void print(int a[][3], int n, int m){
void print(int (*a)[3], int n, int m){
	// 传进去的是一个行指针变量 
	// 要规定有几列 
	int (*p)[3]; 	// 3代表指向一行的元素个数 
	int *q;
	for (p = a; p < a + n; ++p){	
		for (q = *p; q < *p + m; ++q){
			printf("%3d", *q);
		}
		printf("\n");
	}
}

// 输出任意n行m列的数组 
void print2(int *a, int n, int m){
	int i, j;
	int *p;
	for (p = a, i = 0; i < n; ++i){
		for (j = 0; j < m; ++j, ++p)
			printf("%4d", *p);
		printf("\n");
	}
	// *(a + n - 1) = *(a + (n - 1) * m)
}

void deldigit(char *s){
	char *pp;
	pp = s 
	// 用while循环更好理解
	while (*pp != '\0'){
		if (isdigit(*pp)){
			strcpy(pp, pp + 1);
		}else{
			p++;
		}
	} 
}

//void my_sort(char w[][20], int n){
void my_sort(char (*w)[20], int n){ 
	int i, j;
	char temp[20];
	for (i = 0; i < n - 1; ++i){
		for (j = 0; j < n - 1 - i; ++j){
			if (strcmp(w[j], w[j + 1]) > 0){
				strcpy(temp, w[j]);
				strcpy(w[j], w[j + 1]);
				strcpy(w[j + 1], temp);
			}
		}
	}
}

//void my_sort_(char *w[], int n){
void my_sort_(char **w, int n){
	// 二级指针 
	int i, j;
	char *temp;
	for (i = 0; i < n - 1; ++i){
		for (j = 0; j < n - 1 - i; ++j){
			if (strcmp(w[j], w[j + 1]) > 0){
//				strcpy(temp, w[j]);
//				strcpy(w[j], w[j + 1]);
//				strcpy(w[j + 1], temp);
				temp = w[j];
				w[j] = w[j + 1];
				w[j + 1] = temp;
			}
		}
	}
	
	char **q1, **q2;
	for (i = 0; i < n - 1; ++i){
		for (q1 = w, q2 = w + 1, j = 0; j < n - 1 - i; q1++, q2++, ++j){
			if (strcmp(*q1, *q2) > 0){
//				strcpy(temp, w[j]);
//				strcpy(w[j], w[j + 1]);
//				strcpy(w[j + 1], temp);
				temp = *q1;
				*q1 = *q2;
				*q2 = temp;
			}
		}
	}
}

void my_print(char w[][20], int n){
	int i;
	for (i = 0; i < n; ++i){
		puts(w[i]);
	}
}

void my_print_(char *w[], int n){
	int i;
	for (i = 0; i < n; ++i){
		puts(w[i]);
	}
}

int main(){
//	x = a[i][j];
	// [] 是下标运算符，左结合；所以先运算的是列坐标；a[i]是一个数组名	 
	// 行指针 == 指向一维数组的指针
	// *(a + i)：指向(a + i)这一行（第 i 行）的首地址 (第一个元素的地址)的指针 (不是一个指针变量) 
	// ---> a[i][j] = *(a[i] + j) ---> *(*(a + i) + j)
	
	int a[2][3] = {1, 2, 3, 4, 5, 6};
	int i, j;
	// 定义一个指针变量
	int (*p)[3]; 	// 3代表指向一行的元素个数 
	int *q;
//	int *p[3]; // 如果是这样的话，那就是int *(p[3])；p是一个数组 ------> 这是一个指针数组 
//	for (i = 0; i < 2; ++i){
	for (p = a; p < a + 2; ++p){		
//		for (j = 0; j < 3; ++j){
		for (q = *p; q < *p + 3; ++q){
//			printf("%3d", a[i][j]);
//			printf("%3d", p[j]);
			printf("%3d", *q);
		}
		printf("\n");
	}
	
	// print(a, 2, 3);
	print2(*a, 2, 3); // a是一个行指针，指向二维数组的第一行；*a表示指向二维数组的第一行的第一个元素的指针 
	
	int b[3][2] = {4, 5, 6, 7, 8, 9};
	print2(*b, 3, 2); 
	printf("\n");
	printf("a[0][0] = %d\n", **a);
	// 这里**a不是指针的指针（不是二级指针：指向指针变量的指针变量） 
	
	char s[80];
	 
	gets(s);
	for (i = 0; s[i] != '\0'; ++i)
		if (isdigit(s[i])){
//			putchar(s[i]);
			for (j = i + 1; s[j] != '\0'; ++j){
				s[j - 1] = s[j];
			}
			s[j - 1] = '\0';
			i--;
		}
	puts(s);
	
	// 用指针的方法实现：
	char *pp, *qq;
	gets(s);
	for (pp = s; *pp != '\0'; ++pp)
		if (isdigit(*pp)){
//			for (qq = pp + 1; *qq != '\0'; ++qq){
//				*(qq - 1) = *qq;
//			}
//			*(qq - 1) = '\0';
			strcpy(pp, pp + 1);
			pp--;
		}
	puts(s);
	 
	pp = s 
	// 用while循环更好理解
	while (*pp != '\0'){
		if (isdigit(*pp)){
			strcpy(pp, pp + 1);
		}else{
			pp++;
		}
	} 
	
	deldigit(s);
	puts(s);
	
	// 字符指针处理字符串常量的问题
	// 字符串常量有地址，整数常量等没地址 
	char *p = "I miss you."; // 把字符串的首地址赋值给了p (节约空间) 
	char a[] = "I miss you."; // 把字符串常量的空间复制一份给数组a，相当于内存中有两份空间存储这个字符串信息
	// 可以去修改字符串常量的值么？答：不可以。windows系统下是内存的非法访问是很严格的，所以就不可以；但是对于dos和linux来说，是可以改的 
//	*p = 'U'; <===> *p[0] = 'U';   解决方法：C++中用const来保护这个变量 
	p = "huaeiechc"; // 当然是可以的，只不过是这个指针指向了另一个字符串罢了。
//	a = "huaeiechc"; // 当然不可以，因为a不是一个变量
	// 正确方法：
	strcpy(a, "nduiwaduiawwuic"); // 将a[] 替换为新的字符串
	
	// 指针数组和指针的指针
	char word[5][20] = {"China", "Russia", "America", "Japan", "Korea"};
	my_sort(word, 5);
	my_print(word, 5);
	
	// 指针数组
	char *word[5] = {"China", "Russia", "America", "Japan", "Korea"}; 
	my_sort_(word, 5);
	my_print_(word, 5);
	
	// 二级指针和指向数组的指针的区别
//	二维数组的 a[i] 都是地址，不是变量
	// 指向数组的指针就是开一个数组，存放的是二维数组行地址的首地址，其数字内的内容可以互换
	// 指向数组的指针是简介寻址，二级指针相当于是直接寻址 
	return 0;
}



