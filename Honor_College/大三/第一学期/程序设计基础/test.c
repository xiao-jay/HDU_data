#include <stdio.h>
#include <stdlib.h> 
#define N 10000

// 结构体类型 
struct time{
	int hour;
	int minute;
	int second;
//	int operator > (); // 重载函数 
}t = {1, 2, 3};
// 初始化一个全局变量 

// 自定义名字 
typedef struct time Time;

struct date{
	int year;
	int month;
	int day;
	// 上述三个都是结构体类型的 成员变量 / 字段 / 域 
};

struct point{
	double x, y;	
}; 

struct student{
	char id[8];
	char name[20];
	int score;
	// 可以嵌套（例如下面是一个date类型的birthda数据）定义，但不允许自嵌套 (无限大) 
	struct date birthday;
//	struct student classmate[50]; 
	// 允许定义结构体指针 
	struct student *classmate[50]; 
};

// 进化成下面的样子： 

typedef struct time{
	int hour;
	int minute;
	int second;
}Time;

// 再进化 

typedef struct{
	int hour;
	int minute;
	int second;
}Time;

//	void *p; // 空指针类型
//  void *f(); // 返回值类型是空 

void show(Time t){
	printf("%02d : %02d : %02d\n", t.hour, t.minute, t.second);
	// . 结构体（成员）运算符的优先级是一级，和括号相同 
} 

void show_(Time *pt){
	printf("%02d : %02d : %02d\n", pt->hour, pt->minute, pt->second);
	// . 结构体（成员）运算符的优先级是一级，和括号相同 
} 

void show_cpp(Time &pt){
	printf("%02d : %02d : %02d\n", pt.hour, pt.minute, pt.second);
	// . 结构体（成员）运算符的优先级是一级，和括号相同 
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
//				// 系统有默认的赋值函数 = ，但是 > 没有，所以比不了
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
	show_cpp(t2); // 地址传递 
	scanf("%d %d %d", &t1.hour, &t1.minute, &t1.second);
	t1 = t2; 
	show(t1);
	
	// 赋值: t1和t2本身就是一个类型，t2有默认的赋值运算符重载函数
	// 参数的传递是复制构造函数（参数传递效率低） 
	
	Time t[3] = {{0, 0, 0}}; 
	int i;
	for (i = 0; i < 3; ++i){
		scanf("%d %d %d", &t[i].hour, &t[i].minute, &t[i].second);
	}
	// 有关结构体的编程题：结构体数组的排序
	sort(t, 3);
	for (i = 0; i < 3; ++i){
		show(t[i]);	
	}
	 
	 
	
//	int n;
//	scanf("%d", &n);
	return 0;	
}



