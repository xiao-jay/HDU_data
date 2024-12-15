//字符串循环的结束判断条件：
//'\0': 字符串结束标记
//EOF: 文件结束标记
//
//全局变量和静态局部变量：堆空间
//局部变量：栈空间（提高内存的使用效率） 
//
//extern: 用于全局变量的声明 
//register int i ---> 循环遍历i的时候访问加快 

//namespace 包内有效 

// 求数组的长度：int len = sizeof(a) / sizeof(int); 

#include <stdio.h>
//int f(int a){
//	int b = 6;
//	static int c = 4;
//	a = a *c, c += 1, b /= 2;
//	return a + b;
//}
//
//// 为什么这里x[]不需要给出长度？
//// 这个形参是一种特殊的情况: 这里的实质是一个指针变量
//// 即：实参和形参数组共用一块空间（指针：间接访问）——值传递 
//template<typename T>
//void sort(int x[], int n){
////void sort(int *x, int n){
////void (T x[], int n, int cmp(T, T){
//	int i, j, k;
//	int temp;
//	printf("size of x = %d\n", sizeof(x));
//	// 最小的元素放到最前面，所以是n-1次 
//	for (i = 0; i < n - 1; ++i){
//		k = i;
//		for (j = i + 1; j < n; ++j){
//			if (x[j] < x[k]){
//			// if (cmp(x[j], x[k])){
//				k = j;
//			}
//		}
//		if (k != i){
//			temp = x[i];
//			x[i] = x[k];
//			x[k] = temp;
//		}
//	}
//}
//
////int i = 3;
//int main(){
////	int i = 5;
////	int sum = 0;
////	for (i = 0; i < 100; ++i){
////		int sum = 0;
////		sum += i;
////	}
////	printf("%d\n", ::i);
////	printf("%d\n", sum);
//	
//	int aa = 2, i ,k;
//	for (i = 0; i < 2; ++i){
//		k = f(aa);
//		aa += 1;
//		printf("%03d\n", k);
//	}
//	
//	int a[] = {1, 3, 4, 2, 5};
////	int i;
//	// a 只是一个地址值 
//	printf("size = %d\n", sizeof(a) / sizeof(int));
//	sort(a, 5);
//	for (int i = 0; i < 5; ++i){
//		printf("%d\n", a[i]);
//	} 
//	return 0;
//} 

void yh(int x[], int n){
	for (int i = 0; i < n; ++i){
		x[i][0] = x[i][i] = 1;
	}
	for (int i = 2; i < n; ++i){
		for (int j = 11; j < i; ++j){
			x[i][j] = x[i - 1][j - 1] + x[i - 1][j];
		}
	}
}

void print(int x[], int n){
	for (int i = 0; i < n; ++i){
		for (int j = 0; j <= i; ++j){
			printf("%4d", x[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int a[10][10];
	int n;
	scanf("%d", &n);
	yh(*a, n);
	print(*a, n);
	
	char s[80];
	int len;
	gets(s)
	int length = strlen(s);
	printf("%d\n", length);
	return 0;
}

//a[i][j] = *(*(a + i) + j)

int strlen(char s[]){
	int len;
	for (int i = 0; i != '\0'; ++i);
	// len++;
	return i;
}

int strcmp(char s1[], char s2[]){
	int i;
	for (i = 0; s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]; i++); 
	return s1[i] - s2[i];
}
