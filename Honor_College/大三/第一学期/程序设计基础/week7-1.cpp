//abs(): 函数重载运算符
//a[i]: 数组定义语法的呢形式 

#include <stdio.h>
#include <string.h>

int main(){
	char filename[20];
	scanf("%s", filename);
    freopen(filename, "r", stdin);     
    freopen("result.txt", "w", stdout); 
    char ch;
    char word[1000][20]; //单词本 
	
    fclose(stdin);
    fclose(stdout);
    
    
	int i,j,k,n;
	char s[1000],str1[1000],str2[1000];
	gets(s);
	n=strlen(s);
	j=0;
	for(i=n-1;i>=0;i--)
	{
	str1[j]=s[i];
	j++;
	}
	j=0;
	for(i=0;i<n;i++)
	    {
        if((str1[i]>=65&&str1[i]<=90)||(str1[i]>=97&&str1[i]<=122))//判断是否为空格，若不是，将该处字符储存到字符串数组中
        {
            str2[j]=str1[i];
            j++; 
        }    
        if((str1[i]<65||(str1[i]>90&&str1[i]<97)||str1[i]>122)&&(str1[i-1]>=65&&str1[i-1]<=90||str1[i-1]>=97&&str1[i-1]<=122)||i==n-1)//当该单词结束时，将储存到字符串数组中的单词倒序输出
        {
            for(k=j-1;k>=0;k--)
            {
            printf("%c",str2[k]);
            }
            j=0;
        }    
        if(str1[i]==' '||str1[i]==','||str1[i]=='.')//当遇到空格时，照常输出
        printf(" ");
        if(i==n-1)printf("\n"); //句尾输出换行符
    }
    return 0;
}
