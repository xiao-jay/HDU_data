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
		else if (f_) printf("��һ����ֵ�Ӵ�����ʼλ�����ַ����е�%dλ\n", i + 1), f = 1, f_ = 0, start = i;
	}
	
	for (int i = start; ; ++i){
		if (s[i] == s[i + 1]){
			 printf("%c", s[i]), my_length++;
		}else break;
	}
	printf("\n");
	if (s[length - 1] == s[length - 2] && s[length - 1]== s[start]) printf("%c", s[length - 1]), my_length++;
	if (f) printf("�õ�ֵ�ִ��ĳ����ǣ�%d\n", my_length);
	if (!f) printf("�޵�ֵ�Ӵ�\n"); 
	return 0;
} 

// ���㷨��ʱ�临�Ӷ���: ���ڳ���Ϊ n �������ַ�����˵, ��ʱ�临�Ӷ���: O(n)�� 

