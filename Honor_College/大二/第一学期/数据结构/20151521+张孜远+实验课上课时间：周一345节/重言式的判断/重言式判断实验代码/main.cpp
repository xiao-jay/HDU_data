#include<bits/stdc++.h>
#include "Tree_1.h"
using namespace std;

int main(){
	cout << "---此程序目的是实现逻辑表达式求值并判断类型---" << endl <<endl;
    cout << "逻辑表达式中运算符为 ~、^、&、|、(、)，逻辑变量为大写字母。" << endl << endl; 
    char s[200];
    while (scanf("%s", s) != EOF){
    	TreeList T;
    	T.InitBTree(T.root);
		T.Build_Tree(s);
    	int n = T.num;
    	T.Calculation(T.root, n);
    	T.DestroyBTree(T.root);
	}
	return 0;
}
