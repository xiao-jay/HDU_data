#include <stdio.h>
#include <stdlib.h>
#define N 10000

int main(){
	int a = 1, b;
	int *p; // ָ�����������������������Ұָ��; *������һ���﷨����ʽ 
	// ------> int *p = &a; // ��a���׵�ַ��ֵ����p 
	p = p + 100;
	p = (int *)0x114514;
	// ��Щ���Ƕ�p���ָ������ĸ�ֵ����������ָ��������ڴ�Ŀռ��㶼�ܲ����ˣ�һ���в���ʧ��ĵط����ͻ�����ڴ�ķǷ����� 
	 
	printf("a = %d\n", a);
	p = &a; // a�Ǳ�����&a�Ǳ�����ָ�룬�ѱ�����ָ�븳ֵ����һ��ָ�����p����ô���ָ�����p����һ��ָ�������ָ����� 
    b = *p + 1; // �������ָ�����p��ֵ���Ǿͻᵼ���ڴ�ķǷ����� 
//    b = a + 1;
	// *p + 1 �� a + 1��Ч�ʸ��ͣ��ɶ��Ը��� 
	p = &b;
	*p = a + 1; // д������ 
	printf("b = %d\n", b);
	return 0;
} 

// ��ַ����
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

// &�ڱ��ʽ��������ʱ�򣬲���ȡ��ַ������������ڱ�������ĵط��������� 
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
	// ����ab��������ֵ��������
	
	swap2(&a, &b); // �����Ĵ��ݷ�ʽ��ֵ���ݣ�ֻ�Ǵ��ݵ�ֵ�ǵ�ַ ����by value 
	printf("a = %d, b = %d\n", a, b); 
	// ����ab��������ֵ���ù���
	
	swap3(a, b); // �����Ĵ��ݷ�ʽ�ǵ�ַ���ݣ�����ab�ĵ�ַ��xy��xy����ab�ı��� ����by reference 
	printf("a = %d, b = %d\n", a, b); 
	// ����ab��������ֵ���ù���
	return 0;
}

// �������е�max��min
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
	maxmin(a, 5, &max, &min); // ����ָ�� 
	printf("max number = %d, min number = %d\n", max, min);
	return 0;
}

// C++ ����Ϊ int* ��һ���������������
// ָ�뷨���ʣ���ά������ 
int main(){
	// ������������һ��������ֻ�б�����������ֵ������һ��������ָ�루��ַ��
	int a[] = {1, 2, 3, 4 ,5};
	int *p; // ����ָ��p 
	int i = 0, sum = 0;
	for (i = 0, p = a; i < 5; ++i, ++p)
//		sum += a[i];
//		sum += *(a + i); // i����ƫ������������±귨��ʵ�� 
		sum += *p;
	printf("sum = %d\n", sum);
	return 0;
}
 
// *p++: ++����������ȼ���*����������ȼ�һ���ߣ������������ʱ��ʹ������ҽ�ϵĹ���
// ����*p++�ı��ʾ��ǣ���p++����ȡ*(p++) 
// (*p)++����˼�ǣ�ȡ��a[0]��ֵ�����ϸı�a[0]��ֵ��ÿ��+1��������ȡa[0]��ֵ���������Ľ���ǣ�3+4+5+6+7

// αָ�뷨��*(a + i)��������ʾ����±귨 
// ָ�뷨
for (p = a; p < a + 5; p++) sum += *p; 
// ���ӣ�
// �������е�max��min��ָ�뷨�� 
void maxmin(int x[], int n, int *pmax, int *pmin){
	// int x[] == int *x
//	int i = 0;
//	*pmax = *pmin = x[0];
//	for (i = 1; i < n; ++i){
//		if (x[i] > *pmax) *pamx = x[i];
//		if (x[i] < *pmin) *pmin = x[i];
//	}
	int *p;
	// p���Բ�Ҫ����x��Ϊ��Ѱָ�룬�Լ�Ų 
//	pmax = pmin = x; // a[0]�ַ������ֵ���ַ�����Сֵ�����н������
	int *p1, *p2;
	p1 = p2 = x; 
	for (p = x + 1; p < x + n; ++p){ // p <= x + n - 1
	// x��Ϊ�������ʼ��ַ��һ�㲻����Ķ�x��λ�� 
//	for (x = x + 1, i = 1; i < n; x++, i++) 
		if (*p > *pmax) *pamx = *p;
		if (*p > *p1) p1 = p;
//		if (*x > *p1) p1 = x;
		if (*p < *pmin) *pmin = *p;
		if (*p < *p2) p2 = p;
//		if (*x < *p2) p2 = x;
	}
	*pmax = *p1, *pmin = *p2;
	// ���д�� pmax = p, pmin = p ���Ե�ԭ����ǣ�����������ˣ���ʹ��¼�����ֵ����Сֵ��Ҳ��������	
}  

// ��ôдҲ�ǲ��Եģ���Ϊֻ��¼x��y��ֵ�������������֮����Ҳ�ͽ����ˣ�������ȥ 
void swap4(int *x, int *y){
	int *temp;
	temp = x;
	x = y;
	y = temp;
} 

void swap4(int *x, int *y){
	// ��������ֵ 
	int *temp; // temp��Ұָ�룬tempָ��˭�������ڴ�ķǷ����� 
	*temp = *x;
	*x = *y;
	*y = *temp;
} 

int main(){
//	swap4(&a, &b); 
	swap5(&a, &b);
	return 0;
}
 
// ð������
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



