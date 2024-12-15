 //==============================================
 // 马踏棋盘（优化版） 
 //----------------------------------------------
 // 作者：王立波   
 // 修订：2017年2月
 //==============================================

#include <iostream>
#include <iomanip>
#include "Hchess2.h"
using namespace std;

//输出结果 
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
    cout << "请输入棋盘行数：";
    cin >> m;
    cout << "请输入棋盘列数：";
    cin >> n;
    Hchess ch;
    Initchess( ch, m, n );
    cout << "请输入马的起始坐标：";
    cin >> begin.x >> begin.y;
    cout << endl;
    if ( ChessPath( ch, begin, m, n, backnum, compare ) )
    {
	    Print( ch );
	    cout << endl;
	    cout << "此次运行探测次数为：" << compare << endl;
        cout << "此次运行回溯次数为：" << backnum << endl;		
    }
    else 
    {
        cout << "没有通路" << endl;
        cout << "此次运行探测次数为：" << compare << endl;
        cout << "此次运行回溯次数为：" << backnum << endl;
    }
     
    Destroychess( ch ); 
    cout << endl;
    system( "pause" );
    return 0;
}
