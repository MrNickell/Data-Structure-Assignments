#include <iostream>
#include <vector>
using namespace std;

//边的结构，包括起点、终点、权值
struct Edge{
    int value;
    char begin;
    char end;
};

//电力网络的构建
class ElecNetwork{
private:
    Edge _network[1000];
    int _father[1000];  //利用并查集查找爸爸
    int _count;      //顶点的个数
public:
    void createFather();
    void createNetwork();
    void menu();  //打印主菜单
    void loop();   //主循环
    void quickSort(Edge network[],int left,int right);
    void generateMinTree();
    char findFather(char x);  //有关并查集的两个函数 查找与合并
    void Union(char a,char b);
    void display();

};
void ElecNetwork::display(){
    cout <<"最小生成树的顶点以及边是:\n\n";
    for(int i = 0; i < _count; i++)
    {
        if(_network[i].begin != '?')
            cout << _network[i].begin << "-<" << _network[i].value << "> ->" << _network[i].end <<"    ";
    }
}
//快速排序 用于找最小的生成边
void ElecNetwork::quickSort(Edge *a, int left, int right) {
    int i,j,mid;
    Edge temp;

    if(left >= right)
        return;

    i = left;
    j = right;
    mid = (i + j) >> 1;
    do{
        while(a[mid].value > a[i].value) i++;
        while(a[mid].value < a[j].value) j--;
        //如果找到两个数的话  进行交换
        if(i <= j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
            j--;
        }
    }while(i <= j);

    quickSort(a,left,j);
    quickSort(a,i,right);

}

//找到自己的爸爸
char ElecNetwork::findFather(char x){
    if(_father[x] < 0)
        return x;
    else
        return _father[x] = findFather(_father[x]);
}

void ElecNetwork::generateMinTree() {
    char begining;
    cout << "请选择起始顶点:";
    cin >> begining;
    cout << "最小生成树已经生成！" << endl;
    for(int i = 0; i < _count ; i++)
    {
        //如果没有连通的话
        if(findFather(_network[i].begin) != findFather(_network[i].end))
            Union(_network[i].begin,_network[i].end);
        else{
            _network[i].begin = '?';
        }
    }

}

//找到自己的祖宗(连通 or 不连通)
void ElecNetwork::Union(char a,char b){

    char father1,father2;
    father1 = findFather(a);
    father2 = findFather(b);
    _father[father2] = father1;


}

void ElecNetwork::menu() {

    cout << "**\t\t\t  电网造价模拟系统\t\t\t\t**\n";
    cout << "==========================================\n";
    cout << "**\t\t\tA --- 创建电网顶点\t\t\t**\n";
    cout << "**\t\t\tB --- 添加电网的边\t\t\t**\n";
    cout << "**\t\t\tC --- 构造最小生成树\t\t\t**\n";
    cout << "**\t\t\tD --- 显示最小生成树\t\t\t**\n";
    cout << "**\t\t\tE --- 退出程序\t\t\t\t**\n";
    cout << "==========================================\n";

}

void ElecNetwork::createFather()
{
    cout << "请输入顶点的个数:";
    cin >> _count;
    cout << "请依次输入各项点的名称:" << endl;
    char temVertex;
    for(int i = 0; i < _count; i++)
    {
        cin >> temVertex;
        _father[temVertex] = -1;
    }
}
void ElecNetwork::createNetwork(){
    Edge tempEdge;
    int i = 0;
    while(1){

        cout << "请输入两个顶点以及边:";
        cin >> tempEdge.begin;
        cin >> tempEdge.end;
        cin >> tempEdge.value;

        if(tempEdge.begin == '?')
            break;
        _network[i++] = tempEdge;
    }

    quickSort(_network,0,i - 1); //对权值进行排序

}
void ElecNetwork::loop(){

    char command = 'A';

    while(command != 'E')
    {
        cout << "\n请选择操作:";
        cin >> command;
        switch (command)
        {
            case 'A':
                createFather();
                break;
            case 'B':
                createNetwork();
                break;
            case 'C':
                generateMinTree();
                break;
            case 'D':
                display();
                break;
            case 'E':
                cout << "已经成功退出!" << endl;
                break;
            default:
                cout << "输入错误！请输入有效的操作数!" << endl;
                break;
        }
    }

}

int main(){
    ElecNetwork network;
    network.menu();
    network.loop();

}