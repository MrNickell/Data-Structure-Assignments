#include <iostream>
#include <vector>
using namespace std;

struct Position{
    int x;
    int y;
};


char maze[100][100] = {
        "#######",
        "#0#000#",
        "#0#0###",
        "#000#0#",
        "#0#000#",
        "#0#0#0#",
        "#######",
};


Position direction[4] ={{0,1},{0,-1},{-1,0},{1,0}};

Position exitPos = {5,5};
vector<Position> route;
int tag = 0;
void dfs(int x,int y){
    if(x ==  exitPos.x && y == exitPos.y){
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
void printMap(){
    cout << "迷宫地图:" << endl;
    cout << "\t";
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





int main() {
    printMap();
    dfs(1,1);
    cout <<"\n迷宫路径:" << endl;
    for(auto iter = route.begin(); iter != route.end() - 1;iter++)
        cout << "<" << iter->x << "," << iter->y << "> "<< "---> ";
    cout << "<" << (route.end() - 1)->x << "," << (route.end() - 1)->y << ">"<<endl;
    return 0;
}