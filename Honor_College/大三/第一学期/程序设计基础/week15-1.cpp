// random access���������������ʣ�Ҫ���ǿռ��������ģ�
//VLA: �ɱ䳤������
// �ѵĿռ䲻������ջ�������� 

#include <stdio.h>
#include <stdlib.h>
#define N 10

enum Type{INT, DOUBLE};

void swap_enum(void *p1, void *p2, enum Type type){
	if (type == INT){
		int temp;
		int *x, *y;
		x = (int *)p1;
		y = (int *)p2;
		temp = *x;
		*x = *y;
		*y = temp;
	}
	
	if (type == DOUBLE){
		double temp;
		double *x, *y;
		x = (double *)p1;
		y = (double *)p2;
		temp = *x;
		*x = *y;
		*y = temp;
	}	
}

int main(){
	int a = 3, b = 4;
	double x = 1.4, y = 3.5;
//	swap(&a, &b, INT);
//	swap(&x, &y, DOUBLE);
	swap(&a, &b);
	swap(&x, &y);
	printf("%d %d %f %f\n", a, b, x, y);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define N 10

template<typename T>
void free(T *p){
	
}

int main(){
	int x; 
	int n = 5; 
	int a[n]; // �ϰ汾�У�����������Ϊ����ĳ��� 
	// ��Ҫʹ�ö�̬�ռ�����
	double y;
	int *b;
	b = (int *)malloc(sizeof(int) * n); //sizeof��Ŀ���Ǿ��и��õĿ���ֲ�� 
	// ��̬����Ŀռ䲻�ͷŵĻ���main�����˳���Ҳ�����ͷ�(ϵͳ����Ϊ���ռ���Ȼ��ĳ������ռ��)
	p = (struct student*)malloc(sizeof(struct student) * n);
	free(p);
	
	
	
	
	return 0;
}

 

