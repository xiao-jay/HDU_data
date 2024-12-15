//==============================================
// 马踏棋盘（未优化版） 
//----------------------------------------------
// 作者：王立波   
// 修订：2017年2月
//==============================================
#include <iostream>
#include <iomanip>
#include "Hchess1.h"
using namespace std;

//输出棋盘 
void Print( Hchess &ch )
{
    int i,j;
    for ( i = 0; i < ch.row; i++ )
    {
        for ( j = 0; j < ch.col; j++ )   
            cout << setw( 4 ) << ch.chess[ i ][ j ];
			//设置输出格式：每个数字占四个单位长度		    
        cout << endl;
    }
}

int main()
{
    PosType begin;
    int m, n, backnum = 0, compare = 0;
    cout << "请输入棋盘的行数：";
    cin >> m;
    cout << "请输入棋盘的列数：";
    cin >> n;
    Hchess ch;
    Initchess( ch, m, n );
    cout << "请输入行棋初始坐标（用空格分隔）：";
    cin >> begin.x >> begin.y;
    cout << endl; 
    if ( ChessPath( ch, begin, m, n, backnum, compare ) )
    {
	    Print( ch );
	    cout << endl << "此次运行的探测次数为：" << compare << endl;
        cout << endl << "此次运行的回溯次数为：" << backnum << endl;	
    }
    else
    { 
        cout << endl << "此次运行的探测次数为：" << compare << endl;
        cout << endl << "此次运行回溯次数为：" << backnum << endl;
        cout << "没有通路" << endl; 
    }
    Destroychess( ch );
    
    cout << endl;
    system( "pause" );
    return 0;
}
