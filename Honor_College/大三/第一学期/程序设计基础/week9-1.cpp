//�ַ���ѭ���Ľ����ж�������
//'\0': �ַ����������
//EOF: �ļ��������
//
//ȫ�ֱ����;�̬�ֲ��������ѿռ�
//�ֲ�������ջ�ռ䣨����ڴ��ʹ��Ч�ʣ� 
//
//extern: ����ȫ�ֱ��������� 
//register int i ---> ѭ������i��ʱ����ʼӿ� 

//namespace ������Ч 

// ������ĳ��ȣ�int len = sizeof(a) / sizeof(int); 

#include <stdio.h>
//int f(int a){
//	int b = 6;
//	static int c = 4;
//	a = a *c, c += 1, b /= 2;
//	return a + b;
//}
//
//// Ϊʲô����x[]����Ҫ�������ȣ�
//// ����β���һ����������: �����ʵ����һ��ָ�����
//// ����ʵ�κ��β����鹲��һ��ռ䣨ָ�룺��ӷ��ʣ�����ֵ���� 
//template<typename T>
//void sort(int x[], int n){
////void sort(int *x, int n){
////void (T x[], int n, int cmp(T, T){
//	int i, j, k;
//	int temp;
//	printf("size of x = %d\n", sizeof(x));
//	// ��С��Ԫ�طŵ���ǰ�棬������n-1�� 
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
//	// a ֻ��һ����ֵַ 
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
