#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// �����в���

int main(int argc, char *argv[]){
	// ��Ҫ�����������������β�: ���ֿ��Ա䣬���������Ͳ��� 
	puts(argv[0]);
	puts(argv[1]);
	printf("argc = %d\n", argc);
	if (argc != 2){
		printf("Invalid Argument Count.\n");
		exit(0);
	}
	
	// ָ�������һ����ָ������������е��ַ����������������ݲ��ܱ��޸ģ� 
//	deldigit(argv[1]);
//	puts(argv[1]); 
	// ��������д��������ȷ�� 
	char s[80];
	strcpy(s, argv[1]);
	deldigit(s);
	puts(s); 
	 
	 
	
	char s1[80] = "jdiojawiod", s2[] = "73883";
	char *p;
	char ch; 
	p = strcat(s1, s2);
	// ����ƴ�Ӻ����ĵ�һ���ַ� 
	ch = *strcat(s1, s2);
	puts(p);
	putchar(ch); 
	return 0;
	// ���ظ� DOS 
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
			// �������ҵ����ַ���ָ�룿���� 
			// ���ص���ֵ�����ص���ָ��ֵ������ֵַ��
			// ����ֵֻ����Ϊ��ֵ������Ϊ��ֵ 
			return sname[i];
	return NULL;
} 

int func(int n){
	if (n == 1) f(1) = 1;
	// ���Ǵ���ģ�f(n) ������Ϊ��ֵ 
	else f(n) = f(n - 1) * n;
	return f(n);
} 

// ����ָ��
int func(int n){
	if (n == 0 || n == 1) return 1;
	else return func(n - 1) * n;
} 
 
int main(){
	int n, f;
	scanf("%d", &n);
	// ָ��ָ�������ϰ汾�� 
//	int (*p)();
	// �°汾�������βΣ��͸�������
	// �β���int����������Ҳ��int 
	int (*p)(int); // Ұָ�� 
	// int *p(int): ����һ����������������ȣ�char *mystrcat(char *, char *)������������ʱ���ø����βε����� 
	p = func; // ��������� 
//	f = func(n);
	f = p(n);
	printf("func = %d\n", f);
	return 0;
} 

// stack���ڲ���������ռ䣬heap���ѣ� ��ȫ�ֱ�������ռ�
// ��һ���������ں�������Ψһ�ģ�ͨ�����������ֺ���ָ�� 

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
	// f�൱������ģ��ĸо� ---> ���� generic 
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



