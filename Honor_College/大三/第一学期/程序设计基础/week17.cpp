// ����Ԥ����
// �ļ�����
// #include <>
// #include ""
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
// �궨��(��չ��)���������������궨�屾�����κ��﷨��飬�����䱾����ȫ�����������˺궨����ֱ���滻�ģ� ����C++����inline��������ʵ�֣��Ѻ����Ķ����ƴ���Ƕ��ָ��λ�ã� 
// C++��const double PI = 3.14;
// ���������ĺ� 
#define N 5
#define M N + 1
// �������ĺ�
#define SQR(x) ((x) * (x)) 
// �������˻��ǲ���ȫ������ 
#define ABS(x) ((x)>0:(x)?(-x))
#define TOUPPER(x) x>='a'&&x<='z'?x-32:x
int main(){
	int i;
	char ch;
	
	i = 1;
	//for (i = 1; i <= 5; ++i)
	while (i <= 5)
		printf("%d\n", SQR(i++)); // ����ģ�����
	// �����ú����Ͳ������������ 
	
	while ((ch = getchar()) != '\n'){
		if (islower(ch))
			putchar(TOUPPER(ch));
		else putchar(ch);
	}
	  
//	pritnf("%d\n", M * M);
	// == N + 1 * N + 1 = 11;
	return 0;
} 
// ��������













 
