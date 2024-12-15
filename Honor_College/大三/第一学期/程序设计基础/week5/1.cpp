#include<stdio.h>
#include<ctype.h>

int main(){
	char s[1000] = "\0";
	int ans[1000] = {0};
	gets(s);
	int length = 0;
	for (int i = 0; i < 1000; ++i)
		if (s[i] != '\0') length++;
	int l = length, r = 0;
	for (int i = length; i >= 1; --i){
		if(s[i] == ')')
			if(!r) r = i;
		if(s[i] == '('){
			if(r && l == length) l = i;
		}
	}
	
	for (int i = l + 1; i < r; ++i)
		if (s[i] == ')') r = i;
	
	int f = 0;
	int flag;
	int rb = 0;
	int xb = 0;
	for(int i = l + 1; i < r; ++i){
		if (isdigit(s[i])){
			flag = (rb - i) == -1 ? 1 : 0;
			rb = i;
			if (flag){
				ans[xb] = i;
				xb++;	
			}else{
				ans[xb] = 404;
				xb++; 
				ans[xb] = i;
				xb++;
			}
		}else continue; 
	}
	ans[xb] = 404;
	xb++; 
	
//	for (int i = 0; i < xb; ++i) printf("%d ", ans[i]);
//	printf("\n");
	int loc[100] = {0};
	int loc_xb = 0;
	for (int i = 0; i < xb; ++i)
		if (ans[i] == 404) loc[loc_xb] = i, loc_xb++;	
//	for (int i = 0; i < loc_xb; ++i) printf("%d ", loc[i]);
//	printf("\n");
//	for (int i = 0; i < length; ++i) printf("%d ", s[i]);
//	printf("\n");
//	printf("%d", loc_xb);
//	printf("\n");
//	int count = 0;
//	int ans_[100] = {0};
	for (int i = 0; i < loc_xb - 1; ++i){
//		printf("\n");
//		printf("%d   *   %d", ans[loc[i] + 1], ans[loc[i + 1] - 1]);
//		printf("\n");
		for (int j = ans[loc[i] + 1]; j <= ans[loc[i + 1] - 1]; ++j){
//			printf("\n");
//			printf("\n");
//			int flag_ = (s[j] - '0' == 0 && j == ans[loc[i] + 1]);
			if ((s[j] - '0' == 0 && j == ans[loc[i] + 1]) || (s[j - 1] - '0' == 0 && s[j] - '0' == 0)) continue;
			else{
//				count++;
				f = 1;
//				if (count <= 2)
					printf("%d", s[j] - '0');
			}
		}
	}
	if (!f) printf("not find");
	return 0;
} 

#include<stdio.h>
#include<ctype.h>

int main(){
	char s[1000] = "\0";
	gets(s);
	int length = 0;
	for (int i = 0; i < 1000; ++i)
		if (s[i] != '\0') length++;
	int l = length, r = 0;
	for(int i = length; i >= 1; --i){
		if(s[i] == ')')
			if(!r) r = i;
		if(s[i] == '(')
			if(r && l == length) l = i;
	}
	
	for (int i = l + 1; i < r; ++i)
		if (s[i] == ')') r = i;
		
//	string S = "";
	int ans[1000] = {0};
	int xb = 0;
	int flag;
	int rb = 0;
	for(int i = l + 1; i < r; ++i){
		if(isdigit(s[i])){
			flag = (rb - i) == -1 ? 1 : 0;
			rb = i;
			if((s[i] == '0' && xb == 0) || (s[i] == '0' && !flag)) continue;
			else ans[xb] = s[i], xb++;
		}
	}
	
	if(!xb) puts("not find");
	else for (int i = 0; i < xb; ++i) printf("%d", ans[i]);
    return 0;
}


