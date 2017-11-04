//
//  main.cpp
//  约瑟夫生者死者游戏
//
//  Created by MrNickel on 2017/10/11.
//  Copyright © 2017年 MrNickel. All rights reserved.
//

#include <iostream>
using namespace std;

class Passenger{
public:
    int _position;
    Passenger* _next;
public:
    Passenger(int position): _position(position){}
};

class DeadGame{
private:
    int _deadCountM;
    int _stillAlive;
    Passenger* _intialPosition;
    Passenger* _currentPosition;
public:
    DeadGame(int N, int beginPosition,int M):_deadCountM(M),_stillAlive(N) {
        _intialPosition = new Passenger(1);
        auto begin = _intialPosition;
        _currentPosition = _intialPosition;
        for(int i = 2; i <= N; i++)
        {
            auto temp = new Passenger(i);
            if(i == beginPosition)
                _intialPosition = temp;
            
            _currentPosition->_next = temp;
            _currentPosition = temp;
            _currentPosition ->_next = nullptr;
        }
        _currentPosition->_next = begin;
        _currentPosition = _intialPosition;
    }
    Passenger* findHim(){
        Passenger* p;
        for(int i = 0; i < _deadCountM - 1; i++)
        {
            p = _currentPosition;
            _currentPosition = _currentPosition->_next;
        }
        return p;
    }
    void showAlive(){
        while(_currentPosition->_position < _currentPosition->_next->_position)
            _currentPosition = _currentPosition->_next;
        _currentPosition = _currentPosition->_next;
        for(int i = 0; i < this->_stillAlive; i++){
            cout << _currentPosition->_position << "\t";
            _currentPosition = _currentPosition->_next;
        }
        cout << endl;
    }
    void killHim(Passenger* prePosition){
        auto p = _currentPosition;
        prePosition->_next = _currentPosition->_next;
        _currentPosition = _currentPosition->_next;
        cout << p->_position << endl;
        _stillAlive--;
        delete p;
    }
    int getN(){
        return _stillAlive;
    }
    
    
    
};

int main(int argc, const char * argv[]) {
    cout <<"现有N个人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止"<<endl;
    cout << endl;
    
    
    int N,S,M,K;
    cout << "请输入生死游戏的总人数N: " ;
    cin >> N;
    cout << "请输入游戏开始的位置S: " ;
    cin >> S;
    cout << "请输入死亡数字M: " ;
    cin >> M;
    cout << "请输入剩余的生者人数K: " ;
    cin >> K;
    cout << endl << endl << endl;
    DeadGame game(N,S,M);
    int i = 1;
    while(game.getN() > K)
    {
        auto prePosition = game.findHim();
        cout << "第" << i << "个死者的位置是:\t";
        game.killHim(prePosition);
        i++;
    }
    cout << endl << endl << endl;
    cout << "最后剩下:\t\t" << game.getN() <<"人" << endl;
    cout << "剩余的生者位置是为:";
    game.showAlive();
    
    return 0;
}




















