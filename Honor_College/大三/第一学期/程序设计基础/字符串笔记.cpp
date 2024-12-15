#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char ch;
	ch = getchar(); 
	char ch[50];
//	gets(ch);
	int i = 2;
	// 下标为0，从下标为2的元素开始输出 
//	printf("%s", ch+i);
	while (scanf("%s", ch) != EOF){
		// 换行符读不进来 
		printf("%s", ch);
	}
	return 0;
}                              
