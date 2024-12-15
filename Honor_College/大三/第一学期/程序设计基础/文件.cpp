// 文件重定向：freopen

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	FILE *fp1, *fp2; 
	char ch;
	int count = 0;
	int bAlpha = 0; // 标志位 
//	char infilename[20];
//	char outfilename[20];
//	scanf("%s", infilename);
//	scanf("%s", outfilename);
	if (argc != 3) printf("error argument count!\n");
//	fp1 = fopen(infilename, "r"); // 打开文件
//	fp2 = fopen(outfilename, "w"); 
	fp1 = fopen(argv[1], "r"); // 打开文件
	fp2 = fopen(argv[2], "w"); 
	// "a" = append
	if (fp1 == NULL){
		printf("open file failed!\n");
		exit(0);
	}
//	while ((ch = getchar()) != EOF){
	while ((ch = fgetc(fp1)) != EOF){
		putchar(ch);
		fputc(ch, fp2); // 写入fp2中 
		if (isalpha(ch)){
			if (bAlpha == 0){
				count++;		
			}
			bAlpha = 1;
		}else{
			bAlpha = 0;
		}
	}
	printf("Alpha Count = %d\n", count);
	fclose(fp1);
	fclose(fp2);
	
	
	
	return 0;
} 

 
