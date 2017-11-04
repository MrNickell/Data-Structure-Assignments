//
//  Dataset.h
//  单词检索统计系统
//
//  Created by MrNickel on 2017/10/25.
//  Copyright © 2017年 MrNickel. All rights reserved.
//
#ifndef Dataset_h
#define Dataset_h

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

class Dataset{
private:
    int               _command;
    int               _currentLine;
    int               _wordCount;
    int               _nonWordCount;

    string            _currentWords;
    map<string,int>   _wordMap;
public:
    Dataset():_command(0){
    }
    void createFile(){
        string fileName,line;
        cout << "输入要建立的文件名" << endl;
        cin >> fileName;
        ofstream file;
        file.open(fileName);

        char command = 'n';
        while (command == 'n') {
            cout << "请输入一行文本:";
            getline(cin,line);
            getline(cin,line);
            file << line << endl;
            cout << " 输入结束吗？y or n :";
            cin >>command;
        }
        cout << "建立文件结束！" << endl;
        file.close();

    }
    void printMenu(){
        cout << "**********************************" << endl;
        cout << "*******文本文件单词的检索与计数******" << endl;
        cout << "---------------------------------" << endl;
        cout << "|\t\t" << "【1】建立文本文档" <<"\t\t\t|"<<endl;
        cout << "|\t\t" << "【2】文本单词汇总" <<"\t\t\t|"<<endl;
        cout << "|\t\t" << "【3】单词定位" <<"\t\t\t\t|"<<endl;
        cout << "|\t\t" << "【4】退出" <<"\t\t\t\t\t|"<<endl;
        cout << "---------------------------------" << endl;

    }
    void wordCount(string fileName)
    {
        ifstream file;
        file.open(fileName);
        while (getline(file, _currentWords))
        {
            _currentLine++;
            stringstream ss(_currentWords);          //建立一个stringstream的对象 并将刚才读取的line（字符串）的内容放在ss里面
            string word;
            while (ss >> word) {

                if (word[0] >= 'A' && word[0] <= 'Z' || word[0] >= 'a' && word[0] <= 'z')
                    _wordCount++;
                else
                    _nonWordCount++;

                if (_wordMap[word] == 0)
                    _wordMap[word] = 1;
                else
                    _wordMap[word]++;
            }
        }
        file.close();
    }

    void textCount(){
        _currentLine = 0;
        _wordCount = 0;
        _nonWordCount = 0;
        cout << "请输入文件名:";
        string fileName;
        cin >> fileName;

        _wordMap.clear();
        wordCount(fileName);

        cout << ">>>>>>>>>>>>单词<<<>>>>个数<<<<<<<" << endl;
        for (auto iter = _wordMap.begin(); iter != _wordMap.end(); iter++)
        {
            cout.fill(' ');
            cout << setw(15) << iter->first  << setw(10) << iter->second << endl;

        }
        cout<< endl << ">>>>>>>>>>>>>>>>" << fileName << "的单词总数为" << _wordCount << "个" << endl << endl;
        cout << ">>>>>>>>>>>>>>>>" << fileName << "的非单词总数为" << _nonWordCount << "个" << endl << endl;
    }
    void wordPosition(string fileName){
        string word;
        cout << "要检索的单词:";
        cin >> word;
        _currentLine = 0;
        int position = 0;
        ifstream file;
        file.open(fileName);

        vector<int> _wordPosition;
        while (getline(file, _currentWords))
        {
            position = 1;
            _wordPosition.clear();
            _currentLine++;
            _wordCount = 0;
            stringstream ss(_currentWords);//建立一个stringstream的对象 并将刚才读取的line（字符串）的内容放在ss里面
            string tempWord;
            while (ss >> tempWord)
            {
                if(word == tempWord)
                {
                    _wordCount++;
                    _wordPosition.push_back(position);
                }
                position += tempWord.size() + 1;
            }
            if(_wordCount != 0)
            {
                cout << "行号:" << _currentLine <<",出现次数为"<< _wordCount <<", 起始位置分别为: 第";
                for(auto iter = _wordPosition.begin(); iter != _wordPosition.end(); iter++ )
                    cout << "  " << *iter;
                cout << "个字符" << endl;
            }
        }
        file.close();
    }
    void wordLocate(){
        cout << "======================================" << endl;
        cout << "||      文本文件字串的定位统计及定位    ||" << endl;
        cout << "||==================================||" << endl;
        cout << "||\t\t" << "a.   单词出现的次数  " <<" \t\t||"<<endl;
        cout << "||\t\t\t\t\t\t\t\t\t||"<<endl;
        cout << "||\t\t\t\t\t\t\t\t\t||"<<endl;
        cout << "||\t\t" << "b.   单词出现的位置" <<" \t\t\t||"<<endl;
        cout << "||\t\t\t\t\t\t\t\t\t||"<<endl;
        cout << "======================================" << endl;

        string command;
        cout << "请输入a或b:";
        cin >> command;
        string word;
        if( command == "a")
        {
            string fileName;
            cout << "请输入文本文件名:";
            cin >> fileName;

            cout << "请输入要统计计数的单词:" ;
            cin >> word;
            _wordMap.clear();
            wordCount(fileName);
            cout << "单词" << word << "文本文件" << fileName << "中共出现" << _wordMap[word] << "次" << endl;
        }
        else if(command == "b")
        {
            string fileName;
            cout << "请输入文本文件名:";
            cin >> fileName;
            wordPosition(fileName);


        } else {
            cout << "输入错误，已退出！" << endl;
        }
    }
    void executeCommand(){
        while(_command != 4){
            printMenu();
            cout << "请选择<1 ~ 4>:";
            cin >> _command;
            switch (_command) {
                case 1:
                    createFile();
                    break;
                case 2 :
                    textCount();
                    break;
                case 3:
                    wordLocate();
                    break;
                default:
                    break;
            }

        }
    }

};
#endif /* Dataset_h */
