#include <stdio.h>

int main(){
	int year;
	scanf("%d", &year);
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		printf("%d is leap year.\n", year);
	else
		printf("G.\n");
	return 0;
	
	// C����ֻ��ֵ���ͣ�û�����ô��ݣ�����Ҳ��ֵ���ͣ�


} 

void f(){
	extern int count; // ����
}

int count; // ���� 

// ȫ�ֱ�����static����static int�÷�����ǰ�棬#include֮��
// ȫ�ֱ��� static int count��ָ���ڱ��ļ�����Ч
// static void��static int ��һ���ģ���ֹΪ�˺�����һ�����µ�ʹ�ó�ͻ 


