//abs(): �������������
//a[i]: ���鶨���﷨������ʽ 

#include <stdio.h>
#include <string.h>

int main(){
	char filename[20];
	scanf("%s", filename);
    freopen(filename, "r", stdin);     
    freopen("result.txt", "w", stdout); 
    char ch;
    char word[1000][20]; //���ʱ� 
	
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
        if((str1[i]>=65&&str1[i]<=90)||(str1[i]>=97&&str1[i]<=122))//�ж��Ƿ�Ϊ�ո������ǣ����ô��ַ����浽�ַ���������
        {
            str2[j]=str1[i];
            j++; 
        }    
        if((str1[i]<65||(str1[i]>90&&str1[i]<97)||str1[i]>122)&&(str1[i-1]>=65&&str1[i-1]<=90||str1[i-1]>=97&&str1[i-1]<=122)||i==n-1)//���õ��ʽ���ʱ�������浽�ַ��������еĵ��ʵ������
        {
            for(k=j-1;k>=0;k--)
            {
            printf("%c",str2[k]);
            }
            j=0;
        }    
        if(str1[i]==' '||str1[i]==','||str1[i]=='.')//�������ո�ʱ���ճ����
        printf(" ");
        if(i==n-1)printf("\n"); //��β������з�
    }
    return 0;
}
