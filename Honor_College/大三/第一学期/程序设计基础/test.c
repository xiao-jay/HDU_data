#include <stdio.h>
#include <stdlib.h> 
#define N 10000

// �ṹ������ 
struct time{
	int hour;
	int minute;
	int second;
//	int operator > (); // ���غ��� 
}t = {1, 2, 3};
// ��ʼ��һ��ȫ�ֱ��� 

// �Զ������� 
typedef struct time Time;

struct date{
	int year;
	int month;
	int day;
	// �����������ǽṹ�����͵� ��Ա���� / �ֶ� / �� 
};

struct point{
	double x, y;	
}; 

struct student{
	char id[8];
	char name[20];
	int score;
	// ����Ƕ�ף�����������һ��date���͵�birthda���ݣ����壬����������Ƕ�� (���޴�) 
	struct date birthday;
//	struct student classmate[50]; 
	// ������ṹ��ָ�� 
	struct student *classmate[50]; 
};

// ��������������ӣ� 

typedef struct time{
	int hour;
	int minute;
	int second;
}Time;

// �ٽ��� 

typedef struct{
	int hour;
	int minute;
	int second;
}Time;

//	void *p; // ��ָ������
//  void *f(); // ����ֵ�����ǿ� 

void show(Time t){
	printf("%02d : %02d : %02d\n", t.hour, t.minute, t.second);
	// . �ṹ�壨��Ա������������ȼ���һ������������ͬ 
} 

void show_(Time *pt){
	printf("%02d : %02d : %02d\n", pt->hour, pt->minute, pt->second);
	// . �ṹ�壨��Ա������������ȼ���һ������������ͬ 
} 

void show_cpp(Time &pt){
	printf("%02d : %02d : %02d\n", pt.hour, pt.minute, pt.second);
	// . �ṹ�壨��Ա������������ȼ���һ������������ͬ 
} 

int seconds(struct time t){
	return t.hour * 3600 + t.minute * 60 + t.second;
} 

int greater(struct time t1, struct time t2){
	return seconds(t1) > second(t2);
} 

//void sort(struct time x[], int n){
void sort(struct time *x, int n){
	int i, j;
	struct time temp;
	struct time *p1, *p2;
	for (i = 0; i < n - 1; ++i){
//		for (j = 0; j < n - 1 - i; ++j){
		for (p1 = x, p2 = x + 1; p1 < x + n - 1; ++p1, ++p2){
//			if (greater(x[j], x[j + 1])){
//				// ϵͳ��Ĭ�ϵĸ�ֵ���� = ������ > û�У����ԱȲ���
//				temp = x[j];
//				x[j] = x[j + 1];
//				x[j + 1] = temp; 
//			}
			
			if (greater(*p1, *p2)){
				temp = *p1;
				*p1 = *p2;
				*p2 = temp;
			}
			
		}
	}
}

int main(){
//	struct time t1, t2;
	Time t1;
	Time *t2 = {2, 3, 4};
	show_(&t2); 
	show_cpp(t2); // ��ַ���� 
	scanf("%d %d %d", &t1.hour, &t1.minute, &t1.second);
	t1 = t2; 
	show(t1);
	
	// ��ֵ: t1��t2�������һ�����ͣ�t2��Ĭ�ϵĸ�ֵ��������غ���
	// �����Ĵ����Ǹ��ƹ��캯������������Ч�ʵͣ� 
	
	Time t[3] = {{0, 0, 0}}; 
	int i;
	for (i = 0; i < 3; ++i){
		scanf("%d %d %d", &t[i].hour, &t[i].minute, &t[i].second);
	}
	// �йؽṹ��ı���⣺�ṹ�����������
	sort(t, 3);
	for (i = 0; i < 3; ++i){
		show(t[i]);	
	}
	 
	 
	
//	int n;
//	scanf("%d", &n);
	return 0;	
}



