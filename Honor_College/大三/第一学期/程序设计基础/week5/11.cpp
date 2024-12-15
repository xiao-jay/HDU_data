#include<bits/stdc++.h>
using namespace std;

int main(){
	char s[1000];
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	int l = n, r = 0;
	for(int i = n; i >= 1; --i){
		if(s[i] == ')')
			if(!r) r = i;
		if(s[i] == '(')
			if(r && l == n) l = i;
	}
	for (int i = l + 1; i < r; ++i)
		if (s[i] == ')') r = i;
		
	string S = "";
	int flag;
	int rb = 0;
	for(int i = l + 1; i < r; ++i){
		if(isdigit(s[i])){
			flag = (rb - i) == -1 ? 1 : 0;
			rb = i;
			if((s[i] == '0' && !flag) || (s[i] == '0' && S == "")) continue;
			else S += s[i];
		}
	}
	
	if(!S.size()) puts("not find");
	else cout<<S<<endl;
    return 0;
}

