#include<stdio.h>
#include<ctype.h>
// 这个头文件中有isalpha判断函数 

#include<string>
using namespace std;

int main(){
//	char ch;
//	scanf("%c", &ch);
//	printf("ch = %c", ch);
//	ch = getchar()
	 
//	ch = 'A';
//	ch = '\101';
//	ch = '\x41'; 
	// 这里存放的是字符串常量的地址（首地址），用一个指针去指向该字符串的首地址
	// 每个字节都有自己的地址

//	char* ch1;
//	ch1 = "abcd"; 
	// 字符指针变量
	// 字符串的长度是不限定的
	
	// C语言不是强类型安全语言
	// 一块 28 * 80的屏幕，我要去定位输出的位置：windows.h 
	
	// 将输入的很多很多很多字符串中第一个字符改成大写
//	char ch;
//	int f = 0;
//	int cnt = 0;
//	while ((ch = getchar()) != '\n'){
//// while (scanf("%c", &ch) != EOF) 
//		if ((ch >= 'a' && ch <= 'z') || ch >= 'A' && ch <= 'Z'){
//			if (f == 0){
//				cnt++;
//				if (ch >= 'a' && ch <= 'z') ch = ch - 32;
//			}
//			f = 1;
//		}else{
//			f = 0;
//		}
//		putchar(ch);
//	}
//	printf("%d", cnt);
	
	// 统计最长的单词以及出现次数最多的单词是什么？ （自己作业）
	// 将中文歌中的中文和英文分开来
	 
	
	// 文件重定向：freopen("sample.txt", "r", stdin);
	// ch = getchar() < 0 的是中文 
	return 0;
} 
