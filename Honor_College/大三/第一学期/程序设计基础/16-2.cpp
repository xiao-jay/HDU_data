//��ȡһ���ı���ʽ�������ļ��������ж��뷽ʽ��� 
#include<stdio.h>
 int main()
 {  
    FILE *fp;		 //����fpΪָ���ļ����͵�ָ�����
    int n,i=0;
    fp=fopen("prime.txt","r"); //��6��
		//��8��    
    while (fscanf(fp,"%d",&n)==1) //Ҳ���ã�while (fscanf(fp,"%d",&n)��=EOF)
	{		//��7��
	  printf("%5d",n);	//����Ļ����ʾ
	  i++;
	  if (i==10){printf("\n");i=0;}	//1����ʾ10������	  
	}
	fclose(fp); 								//�ر�fp��ָ����ļ�
	return 0;
}

