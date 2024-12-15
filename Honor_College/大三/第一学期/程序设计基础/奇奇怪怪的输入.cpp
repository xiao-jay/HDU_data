#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50005
#define M 605

//student. a am I 
//    World      Hello 

char s[N][M];
char a[N], b[N];
int len[N];
int main(){
	char c;
	int top=1;
	s[top][0]='\0';
    while(scanf("%c",&c)!=EOF){
    	if(c==' '){
    		if(strlen(s[top])){
    			top++;
    			len[top]=0;
    			s[top][0]='\0';
			}
		}
    	else if(c=='\n'||c=='\r'){
    		if(strlen(s[top])==0)top--;
    		for(int i=top;i>=1;--i){
    			printf("%s%c",s[i],i==1?'\n':' ');
			}
		
    		top=1;
    		len[top]=0;
    		s[top][0]='\0';
		}
		else {
    		s[top][len[top]++]=c;
    		s[top][len[top]]='\0';
		}
	}
    if(strlen(s[1])){
		if(strlen(s[top])==0)top--;
    		for(int i=top;i>=1;--i){
    			printf("%s%c",s[i],i==1?'\n':' ');
			}
	
    		top=1;
    		len[top]=0;
    		s[top][0]='\0';
    }
    return 0;
}



// zzy
char s[N];
char ans[N];
int main(){
	int flag = 1;
	char ch;
	gets(s);
	while (flag){
		int l = strlen(s) - 1, r = strlen(s) - 1;
		int time = 0;
		for (int i = strlen(s) - 1; i >= 0 ; --i){
			int cnt = 0;
			if (s[i] != ' '){
				l--;
			}else{
				for (int j = l + 1; j <= r; ++j) if (s[j] != ' ') cnt++;
				if (cnt != 0) time++;
				printf("%d\n", time);
				if (cnt != 0 && time != 1) printf("*");
				for (int j = l + 1; j <= r; ++j) if (s[j] != ' ') printf("%c", s[j]);
				r = --l;
			}
		}
		
		int cnt = 0;
		for (int j = l + 1; j <= r; ++j) if (s[j] != ' ') cnt++;
		for (int j = l + 1; j <= r; ++j) if (s[j] != ' ') printf("%c", s[j]);
		if (gets(s)) flag = 1, printf("\n");
		else flag = 0;
	}
	return 0;
} 

