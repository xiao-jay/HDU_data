//==============================================
// ��̤���̣�δ�Ż��棩 
//----------------------------------------------
// ���ߣ�������   
// �޶���2017��2��
//==============================================
#include <iostream>
#include <iomanip>
#include "Hchess1.h"
using namespace std;

//������� 
void Print( Hchess &ch )
{
    int i,j;
    for ( i = 0; i < ch.row; i++ )
    {
        for ( j = 0; j < ch.col; j++ )   
            cout << setw( 4 ) << ch.chess[ i ][ j ];
			//���������ʽ��ÿ������ռ�ĸ���λ����		    
        cout << endl;
    }
}

int main()
{
    PosType begin;
    int m, n, backnum = 0, compare = 0;
    cout << "���������̵�������";
    cin >> m;
    cout << "���������̵�������";
    cin >> n;
    Hchess ch;
    Initchess( ch, m, n );
    cout << "�����������ʼ���꣨�ÿո�ָ�����";
    cin >> begin.x >> begin.y;
    cout << endl; 
    if ( ChessPath( ch, begin, m, n, backnum, compare ) )
    {
	    Print( ch );
	    cout << endl << "�˴����е�̽�����Ϊ��" << compare << endl;
        cout << endl << "�˴����еĻ��ݴ���Ϊ��" << backnum << endl;	
    }
    else
    { 
        cout << endl << "�˴����е�̽�����Ϊ��" << compare << endl;
        cout << endl << "�˴����л��ݴ���Ϊ��" << backnum << endl;
        cout << "û��ͨ·" << endl; 
    }
    Destroychess( ch );
    
    cout << endl;
    system( "pause" );
    return 0;
}
