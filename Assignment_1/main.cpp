//
//  main.cpp
//  考试报名系统
//
//  Created by MrNickel on 2017/9/27.
//  Copyright © 2017年 MrNickel. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//链表节点
struct student{
    int id;
    string name;
    string gender;
    int age;
    string career;
    student* next;
};


class StudentData
{
private:
    student* _head; //表头
    student* _tail; //表尾
    
public:
    StudentData();
    void print() const;
    void insertData();
    void deleteData();
    void find();
    void modify();
    void run();
    
};
//初始化数据库
StudentData::StudentData()
{
    _head = nullptr;
    cout << "首先建立考生信息系统" << endl << "请输入考生人数:";
    int studentNum;
    cin >> studentNum;
    cout <<"请依次输入考生考号，姓名，性别，年龄及报考类别!" << endl;
    _head = new student;
    cin >> _head->id >> _head->name >> _head->gender >>_head->age >> _head->career;
    this->_tail = _head;
    for(int i = 1; i < studentNum; i++)
    {
        _tail->next = new student;
        _tail = _tail->next;
        cin >> _tail->id >> _tail->name >> _tail->gender >>_tail->age >> _tail->career;
    }
    _tail->next = nullptr;
    print();
}

//打印学生信息
void StudentData::print() const
{
    cout <<"考号\t姓名\t性别\t年龄\t报考类别" << endl;
    auto p = this->_head;
    while(p != nullptr)
    {
        cout << p->id <<"\t" << p->name <<"\t"
        << p->gender << "\t" <<p->age << "\t"
        << p->career << endl;
        p = p->next;
    }
}

//插入数据
void StudentData::insertData()
{
    cout << "请输入您想要插入的考生的位置:" << endl;
    int position;
    cin >> position;
    cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考的类别" << endl;
    auto newNode = new student;
    cin >> newNode->id >> newNode->name >> newNode->gender
    >> newNode->age >> newNode->career;
    auto p = _head;
    for(int i = 0; i < position - 1; i++)
    {
        if(p->next != nullptr)
            p = p->next;
    }
    
    if( p -> next == nullptr)
    {
        p->next = newNode;
        this->_tail = newNode;
    }
    else
    {
        newNode->next = p->next;
        p->next = newNode;
    }
}

//删除数据
void StudentData::deleteData()
{
    cout << "请输入要删除的考生的考号:" << endl;
    int id;
    cin >> id;
    if(this->_head->id == id)
    {
        auto temp = _head;
        _head = _head->next;
        delete temp;
        return;
    }
    auto p = _head;
    while(p->next != nullptr)
    {
        
        if(p->next->id == id)
        {
            auto q = p->next;
            p->next = p->next->next;
            delete q;
            return;
        }
        p = p->next;
    }
    if(p->next == nullptr)
    {
        cout << "找不到学生的信息" << endl;
    }
    
}

//查找个人信息
void StudentData::find()
{
    cout << "请输入要查找的考号:" << endl;
    int id;
    cin >> id;
    auto p = _head;
    
    while(p != nullptr)
    {
        if(p->id == id)
        {
            cout <<"考号\t姓名\t性别\t年龄\t报考类别" << endl;
            cout << p->id <<"\t" << p->name <<"\t"
            << p->gender << "\t" <<p->age << "\t"
            << p->career << endl;
            break;
        }
        p = p-> next;
    }
    if( p == nullptr)
    {
        cout << "找不到学生信息，请重新输入" << endl;
    }
}

//修改信息
void StudentData::modify()
{
    cout << "请输入要修改信息的考生的考号:" << endl;
    int id;
    cin >> id;
    auto p = _head;
    while(p != nullptr)
    {
        if(p->id == id)
        {
            cout << "请依次输入要修改的考生的考号，姓名，性别，年龄及报考的类别" << endl;
            cin >> p->id >> p->name >> p->gender
            >> p->age >> p->career;
            cout << "修改成功！" << endl;
            cout <<"考号\t姓名\t性别\t年龄\t报考类别" << endl;
            cout << p->id <<"\t" << p->name <<"\t"
            << p->gender << "\t" <<p->age << "\t"
            << p->career << endl;
            break;
        }
        p = p-> next;
    }
    if( p == nullptr)
    {
        cout << "找不到学生信息，请重新输入，或退出。" << endl;
    }
}

//选择的主程序
void StudentData::run()
{
    while(1)
    {
        int command;
        cout <<"请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
        cin >> command;
        switch (command)
        {
            case 1:
                insertData();
                print();
                break;
            case 2:
                deleteData();
                print();
                break;
            case 3:
                find();
                break;
            case 4:
                modify();
                break;
            case 5:
                print();
                break;
            case 0:
                cout << "\n程序已经成功退出!\n "<< endl;
                return ;
        }
    }
}

int main(int argc, const char * argv[])
{
    StudentData data;
    data.run();
    
    return 0;
        
}
