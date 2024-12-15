// random access：数组可以随机访问（要求是空间是连续的）
//VLA: 可变长度数组
// 堆的空间不连续，栈是连续的 

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
	int a[n]; // 老版本中，变量不能作为数组的长度 
	// 需要使用动态空间申请
	double y;
	int *b;
	b = (int *)malloc(sizeof(int) * n); //sizeof的目的是具有更好的可移植性 
	// 动态申请的空间不释放的话，main程序退出了也不会释放(系统会认为这块空间仍然被某个进程占用)
	p = (struct student*)malloc(sizeof(struct student) * n);
	free(p);
	
	
	
	
	return 0;
}

 

