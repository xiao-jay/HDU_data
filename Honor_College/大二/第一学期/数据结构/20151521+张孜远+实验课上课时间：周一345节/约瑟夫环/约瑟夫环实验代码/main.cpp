#include "real_nec_ReList.h"

int main(){
	//��Ҹ���
	int players; 
	cout<<"��������Ҹ���: ";
	cin>>players;
	
	//���ÿ����ҵ�������������  
	int code_nums[players]; 
	
	cout<<"�밴������ÿλ��ҵ�������: ";
	for (int i = 0; i < players; i++){
		cin>>code_nums[i];
		//cout<<code_nums[i]<<"\n";
	}

	RecycList<int> *L=new RecycList<int> (code_nums, players);
	Node<int> *p=L->get_phead(), *pre, *next;
	
	int m;
	cout<<"��������Ϸ�г�ʼ�Ĳ�������: "; 
	cin>>m;
	
	cout<<"��Լɪ���е������̭˳��: "<<endl; 
	L->Node_move(players, m);

	return 0;
} 
