#include <iostream>
using namespace std;

//每一个乘客
class Passenger{
public:
    int _position;
    Passenger* _next;
public:
    Passenger(int position): _position(position){}
};


//游戏类，主要由循环链表存储实现
class DeadGame{
private:
    int           _deadCountM;   //死亡人数
    int           _stillAlive;   //还活着的人的人数
    Passenger*    _initPos;      //最初的位置
    Passenger*    _curPos;       //目前的位置
public:
    DeadGame(int N, int beginPosition,int M);   //初始化整个游戏
    
    Passenger* findHim();                       //找到要死的人
    
    void showAlive();                           //展示还活着的人的序号

    void killHim(Passenger* prePos);            //kill this man！

    int getN()
    {
        return _stillAlive;
    }
    
    
    
};
//初始化整个游戏
DeadGame::DeadGame(int N, int beginPosition,int M):_deadCountM(M),_stillAlive(N)
{
    _initPos = new Passenger(1);
    auto begin = _initPos;
    _curPos = _initPos;
    
    for(int i = 2; i <= N; i++)
    {
        auto temp = new Passenger(i);
        if(i == beginPosition)
            _initPos = temp;
        
        _curPos->_next = temp;
        _curPos = temp;
        _curPos ->_next = nullptr;
    }
    
    _curPos->_next = begin;
    _curPos = _initPos;
}

//找到要死的人
Passenger* DeadGame::findHim()
{
    Passenger* p;
    for(int i = 0; i < _deadCountM - 1; i++)
    {
        p = _curPos;
        _curPos = _curPos->_next;
    }
    return p;
}

//展示还活着的人的序号
void DeadGame::showAlive()
{
    while(_curPos->_position < _curPos->_next->_position)
        _curPos = _curPos->_next;
    
    _curPos = _curPos->_next;
    for(int i = 0; i < this->_stillAlive; i++)
    {
        cout << _curPos->_position << "\t";
        _curPos = _curPos->_next;
    }
    cout << endl;
}

//kill this man！
void DeadGame::killHim(Passenger *prePos)
{
    auto p = _curPos;
    
    prePos->_next = _curPos->_next;
    _curPos = _curPos->_next;
    cout << p->_position << endl;
    
    _stillAlive--;
    delete p;
}


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

