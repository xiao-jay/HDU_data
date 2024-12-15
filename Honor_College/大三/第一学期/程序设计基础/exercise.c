#include <stdio.h>
#include <stdlib.h>
#define N 30
#define M 5

struct Singers{
	int id;
	char name[10];
	float score[10];
	float finalscore;
};

// 从score_file.txt中读入数据 
//int Read_info(struct Singers *sin, char *filename){
int Read_info(struct Singers *sin){
	int n = 0;
	int i;
	
//	FILE *fp;
//	fp = fopen(filename, "r");
//	if (fp = =NULL){
//		printf("file open error.\n");
//		exit(-1);
//	}
//	while (fscanf(fp, "%d %s", &sin[n].id, sin[n].name) != EOF){

	while (scanf("%d %s", &sin[n].id, sin[n].name) != EOF){
		for (i = 0; i < M; ++i){
			scanf("%f", &sin[n].score[i]);
//			fscanf(fp, "%f", &sin[n].score[i]);
		}
		n++;
	}
	// fclose(fp);
	return n;
}

void calc(struct Singers *sin, int num){
	int i, j;
	for (i = 0; i < num; ++i){
		float sum = 0;
		float maxx = -1;
		float minn = 100;
		for (j = 0 ; j < M; ++j){
			sum += sin[i].score[j];
			if (maxx < sin[i].score[j]) maxx = sin[i].score[j];
			if (minn > sin[i].score[j]) minn = sin[i].score[j];
		}
		sum = (sum - maxx - minn) / (M - 2);
		sin[i].finalscore = sum;	
	}
}

void sort(struct Singers *sin, int num){
	int i, j;
	struct Singers temp;
	for (i = 0; i < num - 1; ++i){
		for (j = 0; j < num - 1 - i; ++j){
			if (sin[j].finalscore < sin[j + 1].finalscore){
				temp = sin[j];
				sin[j] = sin[j + 1];
				sin[j + 1] = temp;
			}
		}
	}
}

void WriteToFile(struct Singers *sin, int num){
	int i, j;
	for (i = 0; i < num; ++i){
		printf("%10d %10s", sin[i].id, sin[i].name);
		for (j = 0; j < M; ++j){
			printf("%7.2f", sin[i].score[j]);
		}
		printf("%7.2f\n", sin[i].finalscore);
	}
}

int main(){
	struct Singers sin[N];
	int count = 0;
//	count = Read_info(sin, "data.txt");
	count = Read_info(sin);
	calc(sin, count);
	sort(sin, count); 
	WriteToFile(sin, count);
	return 0;
} 


