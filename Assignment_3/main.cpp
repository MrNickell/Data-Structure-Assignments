#include <iostream>
#include <vector>
using namespace std;

//坐标
struct Position{
    int x;
    int y;
};

//迷宫
char maze[100][100] = {
        "#######",
        "#0#000#",
        "#0#0###",
        "#00000#",
        "#0###0#",
        "#0#0#0#",
        "#######",
};


Position direction[4] ={{0,1},{0,-1},{-1,0},{1,0}};

//出口的位置
Position exitPos = {5,5};

//用来存储每一个经过的坐标
vector<Position> route;

int tag = 0;

//递归深度搜索
void dfs(int x,int y)
{
    //发现出口即可退出
    if(x ==  exitPos.x && y == exitPos.y)
    {
        tag = 1;
        route.push_back(exitPos);
        return;
    }

    for(int i = 0; i < 4 ; i++)
    {
        if(maze[x + direction[i].x][y + direction[i].y] == '0'){
            maze[x][y] = 'F';
            Position cur = {x,y};
            route.push_back(cur);

            dfs(x + direction[i].x,y + direction[i].y);

            if(tag == 1)
                return ;

            route.erase(route.end() - 1);
            maze[x][y] = '0';
        }

    }
}

//打印地图
void printMap()
{
    cout << "迷宫地图:\n\t";

    for(int i = 0; i < 7; i++)
        cout << i << "列" <<"\t\t";

    cout << endl;
    for(int i = 0; i < 7; i++)
    {
        cout << i << "行" <<"\t";
        for(int j = 0 ;  j < 7; j++)
        {
            cout << maze[i][j]  <<"\t\t";
        }
        cout << endl << endl;
    }
}

//打印路线
void printRoute()
{
    cout <<"\n迷宫路径:" << endl;
    for(auto iter = route.begin(); iter != route.end() - 1;iter++)
        cout << "<" << iter->x << "," << iter->y << "> "<< "---> ";
    cout << "<" << (route.end() - 1)->x << "," << (route.end() - 1)->y << ">"<<endl;
}



int main() {
    printMap();
    dfs(1,1);

    printRoute();


    return 0;
}