#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//void print(int a[][3], int n, int m){
void print(int (*a)[3], int n, int m){
	// ����ȥ����һ����ָ����� 
	// Ҫ�涨�м��� 
	int (*p)[3]; 	// 3����ָ��һ�е�Ԫ�ظ��� 
	int *q;
	for (p = a; p < a + n; ++p){	
		for (q = *p; q < *p + m; ++q){
			printf("%3d", *q);
		}
		printf("\n");
	}
}

// �������n��m�е����� 
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
	// ��whileѭ���������
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
	// ����ָ�� 
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
	// [] ���±�����������ϣ�������������������ꣻa[i]��һ��������	 
	// ��ָ�� == ָ��һά�����ָ��
	// *(a + i)��ָ��(a + i)��һ�У��� i �У����׵�ַ (��һ��Ԫ�صĵ�ַ)��ָ�� (����һ��ָ�����) 
	// ---> a[i][j] = *(a[i] + j) ---> *(*(a + i) + j)
	
	int a[2][3] = {1, 2, 3, 4, 5, 6};
	int i, j;
	// ����һ��ָ�����
	int (*p)[3]; 	// 3����ָ��һ�е�Ԫ�ظ��� 
	int *q;
//	int *p[3]; // ����������Ļ����Ǿ���int *(p[3])��p��һ������ ------> ����һ��ָ������ 
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
	print2(*a, 2, 3); // a��һ����ָ�룬ָ���ά����ĵ�һ�У�*a��ʾָ���ά����ĵ�һ�еĵ�һ��Ԫ�ص�ָ�� 
	
	int b[3][2] = {4, 5, 6, 7, 8, 9};
	print2(*b, 3, 2); 
	printf("\n");
	printf("a[0][0] = %d\n", **a);
	// ����**a����ָ���ָ�루���Ƕ���ָ�룺ָ��ָ�������ָ������� 
	
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
	
	// ��ָ��ķ���ʵ�֣�
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
	// ��whileѭ���������
	while (*pp != '\0'){
		if (isdigit(*pp)){
			strcpy(pp, pp + 1);
		}else{
			pp++;
		}
	} 
	
	deldigit(s);
	puts(s);
	
	// �ַ�ָ�봦���ַ�������������
	// �ַ��������е�ַ������������û��ַ 
	char *p = "I miss you."; // ���ַ������׵�ַ��ֵ����p (��Լ�ռ�) 
	char a[] = "I miss you."; // ���ַ��������Ŀռ临��һ�ݸ�����a���൱���ڴ��������ݿռ�洢����ַ�����Ϣ
	// ����ȥ�޸��ַ���������ֵô���𣺲����ԡ�windowsϵͳ�����ڴ�ķǷ������Ǻ��ϸ�ģ����ԾͲ����ԣ����Ƕ���dos��linux��˵���ǿ��Ըĵ� 
//	*p = 'U'; <===> *p[0] = 'U';   ���������C++����const������������� 
	p = "huaeiechc"; // ��Ȼ�ǿ��Եģ�ֻ���������ָ��ָ������һ���ַ������ˡ�
//	a = "huaeiechc"; // ��Ȼ�����ԣ���Ϊa����һ������
	// ��ȷ������
	strcpy(a, "nduiwaduiawwuic"); // ��a[] �滻Ϊ�µ��ַ���
	
	// ָ�������ָ���ָ��
	char word[5][20] = {"China", "Russia", "America", "Japan", "Korea"};
	my_sort(word, 5);
	my_print(word, 5);
	
	// ָ������
	char *word[5] = {"China", "Russia", "America", "Japan", "Korea"}; 
	my_sort_(word, 5);
	my_print_(word, 5);
	
	// ����ָ���ָ�������ָ�������
//	��ά����� a[i] ���ǵ�ַ�����Ǳ���
	// ָ�������ָ����ǿ�һ�����飬��ŵ��Ƕ�ά�����е�ַ���׵�ַ���������ڵ����ݿ��Ի���
	// ָ�������ָ���Ǽ��Ѱַ������ָ���൱����ֱ��Ѱַ 
	return 0;
}



