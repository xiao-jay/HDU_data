#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	char ch;
	ch = getchar(); 
	char ch[50];
//	gets(ch);
	int i = 2;
	// �±�Ϊ0�����±�Ϊ2��Ԫ�ؿ�ʼ��� 
//	printf("%s", ch+i);
	while (scanf("%s", ch) != EOF){
		// ���з��������� 
		printf("%s", ch);
	}
	return 0;
}                              
