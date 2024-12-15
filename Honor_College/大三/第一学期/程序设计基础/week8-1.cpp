#include <stdio.h>

int main(){
	int year;
	scanf("%d", &year);
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		printf("%d is leap year.\n", year);
	else
		printf("G.\n");
	return 0;
	
	// C语言只有值传送，没有引用传递（数组也是值传送）


} 

void f(){
	extern int count; // 声明
}

int count; // 开堆 

// 全局变量有static，但static int得放在最前面，#include之后
// 全局变量 static int count是指仅在本文件中有效
// static void和static int 是一样的（防止为了函数名一样导致的使用冲突 


