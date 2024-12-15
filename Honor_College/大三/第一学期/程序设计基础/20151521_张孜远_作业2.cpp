#include<stdio.h>
#include<ctype.h>

int main(){
	char s[10000] = "\0";
	gets(s);
	int length = 0;
	for (int i = 0; i < 10000; ++i) if (s[i] != '\0') length++;
		
	int my_length = 0;
	int f = 0, f_ = 1, start = 0;
	for (int i = 0; i < length - 1; ++i){
		if (s[i] != s[i + 1] ) continue;
		else if (f_) printf("第一个等值子串的起始位置是字符串中第%d位\n", i + 1), f = 1, f_ = 0, start = i;
	}
	
	for (int i = start; ; ++i){
		if (s[i] == s[i + 1]){
			 printf("%c", s[i]), my_length++;
		}else break;
	}
	printf("\n");
	if (s[length - 1] == s[length - 2] && s[length - 1]== s[start]) printf("%c", s[length - 1]), my_length++;
	if (f) printf("该等值字串的长度是：%d\n", my_length);
	if (!f) printf("无等值子串\n"); 
	return 0;
} 

// 该算法的时间复杂度是: 对于长度为 n 的输入字符串来说, 其时间复杂度是: O(n)。 

