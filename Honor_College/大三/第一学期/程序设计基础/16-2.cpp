//读取一个文本格式的数据文件，按行列对齐方式输出 
#include<stdio.h>
 int main()
 {  
    FILE *fp;		 //定义fp为指向文件类型的指针变量
    int n,i=0;
    fp=fopen("prime.txt","r"); //第6行
		//第8行    
    while (fscanf(fp,"%d",&n)==1) //也可用：while (fscanf(fp,"%d",&n)！=EOF)
	{		//第7行
	  printf("%5d",n);	//在屏幕上显示
	  i++;
	  if (i==10){printf("\n");i=0;}	//1行显示10个素数	  
	}
	fclose(fp); 								//关闭fp所指向的文件
	return 0;
}

