#include<bits/stdc++.h>
#include "Tree_1.h"
using namespace std;

int main(){
	cout << "---�˳���Ŀ����ʵ���߼����ʽ��ֵ���ж�����---" << endl <<endl;
    cout << "�߼����ʽ�������Ϊ ~��^��&��|��(��)���߼�����Ϊ��д��ĸ��" << endl << endl; 
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
