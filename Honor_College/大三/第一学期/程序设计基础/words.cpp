#include<stdio.h>
#include<string.h>

int cnt = 0;
char s[1000];
int main(){
	char ch; 
    freopen("sample.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while(scanf("%c", &ch) != EOF){
//    	printf("%c", ch); 
//    while(scanf("%s", s) != EOF){
		printf("%c", ch);
        int len = strlen(s);
        int last = 0;
        for(int i = 0; i < len; ++i){
            int p = 0;
            if(s[i] <= 'z' && s[i] >= 'a') p = 1;
            if(s[i] <= 'Z' && s[i] >= 'A') p = 1;
            if(s[i] <= '9' && s[i] >= '0') p = 1;
            if(s[i] =='-') p = 1;
            if(p){
                last = 0;
                printf("%c", s[i]);
//                printf("%c", ch);
            }
            else {
                if(last == 0){
                	printf(" ");
					cnt++;	
				}
                last = 1;
            }
        }
        if(last == 0){
        	printf(" ");	
			cnt++;
		}
    }
    printf("%d\n", cnt);
    return 0;
}

