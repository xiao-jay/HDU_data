#include <iostream>
using namespace std;

int main(){
	long long int i, f = 1;
    for (i = 1; i <= 20; ++i){
    	printf("%d!=%d\n", i, f);
    	f = f * (i + 1);
	}
	
	int a, b;
	scanf("%d %d", &a, &b);
	printf("a = %d, b = %d\n", a ,b);
	
	int x=10,y=3,z;
	printf("%d\n",z=(x%y,x/y));
	
	
	x=(a=3,b=++a);
	cout<<x<<" "<<a<<" "<<b<<endl;
	
	int j = 5,s=0;
	do {
    	if (j%2) continue;
    	else cout<<j<<endl, s += j;
	}while(--j);
	cout<<s<<endl;
	
	i=5, s=0;
	while(--i!=0){
        if (i%2==1) continue;
        s+=i;  
	}
	cout<<s<<"*****"<<endl;
    return 0;
}

