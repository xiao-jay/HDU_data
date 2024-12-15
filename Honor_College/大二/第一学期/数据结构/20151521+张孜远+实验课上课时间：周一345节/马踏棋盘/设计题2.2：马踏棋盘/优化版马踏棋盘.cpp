 //==============================================
 // ��̤���̣��Ż��棩 
 //----------------------------------------------
 // ���ߣ�������   
 // �޶���2017��2��
 //==============================================

#include <iostream>
#include <iomanip>
#include "Hchess2.h"
using namespace std;

//������ 
void Print( Hchess &ch )
{
    int i,j;
    for ( i = 0; i < ch.row; i++ )
    {
        for ( j = 0; j < ch.col; j++ )   
            cout << setw( 4 ) << ch.chess[ i ][ j ];		    
        cout << endl;
    }
}

int main()
{
    PosType begin;
    int m, n, backnum = 0, compare = 0;
    cout << "����������������";
    cin >> m;
    cout << "����������������";
    cin >> n;
    Hchess ch;
    Initchess( ch, m, n );
    cout << "�����������ʼ���꣺";
    cin >> begin.x >> begin.y;
    cout << endl;
    if ( ChessPath( ch, begin, m, n, backnum, compare ) )
    {
	    Print( ch );
	    cout << endl;
	    cout << "�˴�����̽�����Ϊ��" << compare << endl;
        cout << "�˴����л��ݴ���Ϊ��" << backnum << endl;		
    }
    else 
    {
        cout << "û��ͨ·" << endl;
        cout << "�˴�����̽�����Ϊ��" << compare << endl;
        cout << "�˴����л��ݴ���Ϊ��" << backnum << endl;
    }
     
    Destroychess( ch ); 
    cout << endl;
    system( "pause" );
    return 0;
}
