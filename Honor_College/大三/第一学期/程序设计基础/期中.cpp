////#include <stdio.h>
////void swap(int *x,int *y){
////    int t;
////	t=*x;
////    *x=*y;
////    *y=t;
////}
////void bubbleSort(int *a,int n,int flag){
////    int i,j,t;
////    for(i=1;i<n;i++){
////        for(j=0;j<n-i;j++){
////            if((a[j]-a[j+1])*flag<0){
////                swap(&a[j], &a[j + 1]);
////            }
////        }
////    }     
////}
////int main(){
////    int i,j,x,nod,nev,n;
////    int a[1000];
////    scanf("%d",&n);
////    nod=0;
////    nev=n-1;
////    for(i=0;i<n;i++){
////           scanf("%d",&x);
////        if(x%2==1)
////            a[nod++]=x;    
////        else
////            a[nev--]=x;
////    }
////    bubbleSort(a, nod, 1);
////    bubbleSort(a + nod, n - nod, -1);  
////    for(i=0;i<n;i++){
////        printf("%d ",a[i]);
////    }
////}
//
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
//#include <math.h>
//#include <string.h>
//#define N 10000 
// 
//int a[N], b[N];
//
//void merge(int l, int r){
//	if (l >= r) return;
//	int mid = (l + r) >> 1;
//	merge(l, mid);
//	merge(mid + 1, r);
//	int p = l;
//	int p1 = l, p2 = mid + 1;
//	while (p1 <= mid && p2 <= r){
//		if (a[p1] < a[p2]) b[p++] = a[p1++];
//		else b[p++] = a[p2++];
//	}
//	while (p1 <= mid) b[p++] = a[p1++];
//	while (p2 <= r) b[p++] = a[p2++];
//	int i;
//	for (i = l; i <= r; ++i) a[i] = b[i];
//} 
//
//void swap(int *x, int *y){
//	int temp = *x;
//	*x = *y;
//	*y = temp;
//}
//
//void bubble(int a[], int l, int r){
//	int i, j;
//	for (i = 0; i < r; ++i){
//		for (j = 0; j < r - 1 - i; ++j){
//			if (a[j] > a[j + 1]){
//				swap(&a[j], &a[j + 1]);
//			}
//		}
//	}
//}
//
//int getgcd(int x, int y){
//	if (x > y) swap(&x, &y);
//	int rb = x % y;
//	while (rb > 0){
//		x = y;
//		y = rb;
//		rb = x % y;
//	}
//	printf("%d %d\n", x, y);
//	return y;
//}
//
//int *get(int a[], int find, int r){
//	int ans = 0;
//	int i;
//	for (i = 0; i < r; ++i){
//		if (find == a[i]){
//			ans = i;
//			break;
//		}
//	}
//	return &a[ans];
//}
//
//int main(){
//    int a = 15, b = 10;
//    int res = getgcd(a, b);
//    printf("%d", res);
//    int a[] = {9,8,7,6,5,6,4,3,2,1};
////    merge(0, 8);
////	bubble(a, 0, 9);
//    int i;
////    for (i = 0; i < 9; ++i) printf("%d ", a[i]);
//    int *p = get(a, 6, 9);
//    printf("%d", *p);
//    return 0;
//}
//
//
////char ch = 'a';
////ch - 'a' + 2 + '0' :字母转数字 
////123
////int = ch - '0'  : 本质是偏移量 
//
////数字 + 偏差 = 字母 
//
#include <stdio.h>
int main(){
	char ch = 'a';
	printf("%c", ch - 'a' + 'A');
	return 0;
}

