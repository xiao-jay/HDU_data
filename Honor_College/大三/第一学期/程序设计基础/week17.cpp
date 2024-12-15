// 编译预处理
// 文件包含
// #include <>
// #include ""
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
// 宏定义(宏展开)：带不带参数；宏定义本身不做任何语法检查，所以其本身不安全，后面遇到了宏定义是直接替换的； ——C++中用inline内联函数实现（把函数的二进制代码嵌入指定位置） 
// C++：const double PI = 3.14;
// 不带参数的宏 
#define N 5
#define M N + 1
// 带参数的宏
#define SQR(x) ((x) * (x)) 
// 这样改了还是不安全！！！ 
#define ABS(x) ((x)>0:(x)?(-x))
#define TOUPPER(x) x>='a'&&x<='z'?x-32:x
int main(){
	int i;
	char ch;
	
	i = 1;
	//for (i = 1; i <= 5; ++i)
	while (i <= 5)
		printf("%d\n", SQR(i++)); // 错误的！！！
	// 但是用函数就不会出现这个情况 
	
	while ((ch = getchar()) != '\n'){
		if (islower(ch))
			putchar(TOUPPER(ch));
		else putchar(ch);
	}
	  
//	pritnf("%d\n", M * M);
	// == N + 1 * N + 1 = 11;
	return 0;
} 
// 条件编译













 
