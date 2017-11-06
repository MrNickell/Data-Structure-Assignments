//
// Created by MrNickel on 2017/10/27.
//

#ifndef PROJECT6_FAMILY_H
#define PROJECT6_FAMILY_H
#include <iostream>
#include <vector>
#include <string>
using  namespace std;

struct Member{
    string name;      //姓名

    Member* child;    //孩子
    Member* sibling;  //兄弟姐妹

};

class Family{

private:

    Member* _ancestor;

public:

    Family():_ancestor(new Member){}
    void init();
    void menu();
    void modify(Member* p);
    void display(Member* p);
    void dele(Member* p);
    void deleChild(Member* p);
    void insert(Member* p,string name);
    void changeName(Member* p, string name);
    Member* find(Member* p,string name);

};

//初始化树
void Family::init()
{

    cout << "**\t\t\t  家族管理系统\t\t\t\t**\n";
    cout << "==========================================\n";
    cout << "**\t\t\t请选择要执行的操作:\t\t\t**\n";
    cout << "**\t\t\tA --- 完善家谱\t\t\t\t**\n";
    cout << "**\t\t\tB --- 添加家族成员\t\t\t**\n";
    cout << "**\t\t\tC --- 解散局部家庭\t\t\t**\n";
    cout << "**\t\t\tD --- 更改家庭成员姓名\t\t\t**\n";
    cout << "**\t\t\tE --- 退出程序\t\t\t\t**\n";
    cout << "==========================================\n";


    cout <<"请先建立一个家谱!" << endl;
    cout <<"请输入祖先的姓名:";
    cin >> _ancestor->name;
    _ancestor->child = nullptr;
    _ancestor->sibling = nullptr;

    cout << "此家谱的祖先是" << _ancestor->name << endl << endl;
}

//菜单与选项
void Family::menu()
{

    char command = 'h';
    while(command != 'E')
    {
        cout << "请选择要执行的操作:" ;
        cin >>command;
        switch(command)
        {
            case 'A':
            {
                cout << "请输入要建立家庭的人的姓名:";
                string name;
                cin >> name;
                auto thisMan = find(_ancestor,name);
                if(!thisMan)
                    cout << "找不到这个人，请重新输入！" << endl;
                else if(thisMan->child != nullptr){
                    cout << "他已经有家庭了，请不要破坏！" << endl;
                }
                else
                    modify(thisMan);
            }
                break;
            case 'B':
            {
                cout << "请输入要添加儿子（或女儿）的人的姓名:";
                string name;
                cin >> name;
                auto thisMan = find(_ancestor,name);
                if(!thisMan)
                {
                    cout << "找不到这个人，请重新输入！" << endl;
                    break;
                }

                cout << "请输入"<< name <<"新的添加儿子（或女儿）的人的姓名:";
                cin >> name;
                insert(thisMan,name);
                display(thisMan);
            }
                break;
            case 'C':
            {
                cout << "请输入要解散家庭的人的姓名:";
                string name;
                cin >> name;
                auto thisMan = find(_ancestor,name);
                if(!thisMan)
                {
                    cout << "找不到这个人，请重新输入！" << endl;
                    break;
                }
                cout << "要解散家庭的是" << name << endl;
                display(thisMan);
                auto child = thisMan->child;
                thisMan->child = nullptr;
                deleChild(child);
            }
                break;
            case 'D':
            {
                cout << "请输入要更改姓名的人的目前姓名:";
                string name;
                cin >> name;
                auto thisMan = find(_ancestor,name);
                if(!thisMan)
                {
                    cout << "找不到这个人，请重新输入！" << endl;
                    break;
                }
                cout << "请输入更改后的姓名:";
                cin >> name;
                changeName(thisMan,name);
                cout << name << endl << endl;
            }
                break;
            case 'E':
                cout <<"\n\n程序已经成功退出！";
                break;
            default :
                cout << "输入错误，请重新输入！" << endl;
                break;
        }
    }


}

//按名字找人
Member* Family::find(Member* p,string name)
{

    if( p == nullptr )
        return nullptr;

    if(p->name == name)
        return p;

    auto sib = find(p->sibling,name);

    if(sib != nullptr)
        return sib;
    else
        return find(p->child,name);


}

//修改姓名
void Family::modify(Member* p)
{

    cout << "请输入"<< p->name << "的子女的人数:";
    int num;
    cin >> num;

    string childName;
    vector<string> childNames;
    cout << "请依次输入"<<p-> name << "的儿女的姓名:";
    for(int i = 0; i < num; i++)
    {
        cin >> childName;
        childNames.push_back(childName);
    }

    //初始化这些子女，添加到树中去
    for(int i = 0; i < num; i++)
    {
        insert(p,childNames[i]);
    }

    display(p);

}

//添加家庭成员
void Family::insert(Member* p,string name)
{

    if(!(p -> child))   //如果p没有孩子
    {
        p->child = new Member;
        p = p->child;
        p->name = name;
        p->sibling = nullptr;
        p->child = nullptr;

    }
    else           //如果p已经有孩子了，就找到最右边的那个孩子
    {
        p = p->child;
        while(p -> sibling != nullptr)
            p = p->sibling;
        //找到了右边的空位！
        p->sibling = new Member;
        p = p->sibling;
        p->name = name;
        p->sibling = nullptr;
        p->child = nullptr;
    }


}

//打印
void Family::display(Member *p)
{
    if(!(p -> child))   //如果p没有孩子
    {
        cout << "他(她)没有孩子" << endl;
    }
    else           //如果p已经有孩子了，就找到最右边的那个孩子
    {
        cout << p->name << "的第一代子孙是:";
        p = p->child;
        cout <<p->name<< "   ";
        while(p -> sibling != nullptr)
        {
            p = p->sibling;
            cout <<p->name<< "   ";
        }
        cout << endl << endl;
    }
}

void Family::changeName(Member *p,string name)
{
    cout << p->name << "已经更改成";
    p->name = name;
}

//接下来的两个函数用来杀死所有孩子
void Family::deleChild(Member* p)
{
    auto temp = p;
    while(p->child!= nullptr)
    {
        temp = p->child;
        dele(p);
        p = temp;
    }
    dele(temp);
}

void Family::dele(Member *p)
{

    if(p->sibling == nullptr)
    {
        delete p;
        return;
    }
    dele(p->sibling);
    delete p;

    return;
}



#endif //PROJECT6_FAMILY_H
