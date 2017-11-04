//
//  main.cpp
//  N皇后问题
//
//  Created by MrNickel on 2017/10/24.
//  Copyright © 2017年 MrNickel. All rights reserved.
//

#include <iostream>
using namespace std;
int N(0);

class Queens{
private:
    char** _chessboard;
    char* _queensPosition;
    int _N;
    int _count;
public:
    //初始化棋盘  包括初始化皇后的位置数组
    void initChess(int N)
    {
        _N = N;
        _count = 0;
        _queensPosition = new char[N];
        _chessboard = new char*[N];
        
        for(int i = 0; i < N; i++)
            _chessboard[i] = new char[N];
        
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                _chessboard[i][j] = '0';
            }
        }
    }
    
    //返回N皇后的解法
    int getCount()
    {
        return _count;
    }
    
    //判断如果把皇后放在这个位置是不是可以接受的
    bool isPutable(int i,int j)
    {
        for(int k = 0; k < i; k++)
        {
            if(j == _queensPosition[k] || abs(i - k) == abs( j - _queensPosition[k]))
            {
                return false;
            }
        }
        
        return true;
    }

    //主递归程序，寻找N皇后的解法
    void findQueens(int i)
    {
        if(i == _N)
        {
            print();
            _count++;
            cout << endl << endl;
            return ;
        }
        else
        {
            for(int k = 0; k < N; k++)
            {
                _chessboard[i][k] = 'X';
                _queensPosition[i] = k;
                if(isPutable(i, k))
                    findQueens(i + 1);
                _chessboard[i][k] = '0';
            }
        }
    }
    
    //打印棋盘
    void print()
    {
        for(int i = 0; i < _N; i++)
        {
            for (int j = 0; j < _N; j++)
            {
                cout << _chessboard[i][j] << "   ";
            }
            cout << endl;
        }
    }
};






int main(int argc, const char * argv[]) {
    cout << "现有N * N的棋盘，放入N个皇后，要求所有的皇后不在同一行、列和同一斜线上!" << endl;

    cout << "请输入皇后的个数：" << endl;
    cin >> N;
    Queens chess;
    chess.initChess(N);
    cout << "皇后摆法：" << endl;
    chess.findQueens(0);
    cout << "共有" <<chess.getCount() << "种解法!" << endl;
    return 0;
}
