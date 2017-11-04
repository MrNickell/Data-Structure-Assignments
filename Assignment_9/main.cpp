#include <iostream>
#include <sstream>
using namespace std;

struct AVLNode{
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

AVLNode* root = nullptr;

int max(int a, int b)
{
    return a > b ? a : b;
}

void menu()
{
    cout << "**\t\t\t  二叉排序树\t\t\t\t\t**\n";
    cout << "==========================================\n";
    cout << "**\t\t\t1 --- 建立二叉排序树\t\t\t**\n";
    cout << "**\t\t\t2 --- 插入元素\t\t\t\t**\n";
    cout << "**\t\t\t3 --- 查询元素\t\t\t\t**\n";
    cout << "**\t\t\t4 --- 退出程序\t\t\t\t**\n";
    cout << "==========================================\n";
}

int getHeight(AVLNode* node)
{
    if(node == nullptr)
        return -1;
    else
        return node -> height;

}

// 左单旋
AVLNode* singleLeftRotate(AVLNode* T)
{
    auto B = T->left;
    T->left = B->right;
    B-> right = T;
    T->height = max(getHeight(T->left),getHeight(T->right)) + 1;
    B->height = max(getHeight(B -> left),getHeight(T->right)) + 1;

    return B;
}
// 右单旋
AVLNode* singleRightRotate(AVLNode* T)
{
    auto B = T->right;
    T->right = B -> left;
    B->left = T;
    T->height = max(getHeight(T->left),getHeight(T->right)) + 1;
    B->height = max(getHeight(B -> left),getHeight(T->right)) + 1;

    return B;
}

//左右双旋
AVLNode* doubleLeftRightRotate(AVLNode* T)
{
    T->left = singleRightRotate(T->left);

    return singleLeftRotate(T);
}

//右左双旋
AVLNode* doubleRightLeftRotate(AVLNode* T)
{
    T->right = singleLeftRotate(T->right);

    return singleRightRotate(T);
}





AVLNode* insert(int key,AVLNode* T)
{
    if( !T )
    {
        T = new AVLNode;
        T -> data = key;
        T -> height = 0;
        T -> left = nullptr;
        T -> right = nullptr;
    }
    else if(key < T -> data)
    {
        T -> left = insert(key, T -> left);
        if(getHeight(T->left) - getHeight(T->right) == 2)
        {
            //左单旋
            if(key < T->left->data)
                T = singleLeftRotate(T);
            else //左右旋转
                T = doubleLeftRightRotate(T);
        }
    }
    else if(key > T -> data)
    {
        T -> right = insert(key, T -> right);
        if(getHeight(T->left) - getHeight(T->right) == -2)
        {
            if(key > T->right->data)
                T = singleRightRotate(T);
            else
                T = doubleRightLeftRotate(T);
        }
    }
    T->height = max(getHeight(T -> left),getHeight(T->right)) + 1;

    return T;
}
void inorder(AVLNode* T){
    if(T == nullptr)
        return;
    inorder(T->left);
    cout << T->data << "->";
    inorder(T->right);
}
bool find(AVLNode* T,int key){

    if(T == nullptr)
        return false;

    if(key == T -> data)
        return true;

    if(key < T->data)
        return find(T->left,key);
    else
        return find(T->right,key);
}
void createTree()
{
    if(root != nullptr)
    {
        cout << "you have created a tree!" << endl;
        return;
    }

    cout << "Please input keys to create Bsort_Tree:" << endl;
    int key = 0;
    char c;
    string keys;
    getline(cin,keys);
    getline(cin,keys);
    stringstream ss(keys);          //建立一个stringstream的对象 并将刚才读取的line（字符串）的内容放在ss里面
    string word;
    while (ss >> key)
    {
        if(key == 10)
            break;
        if(!find(root,key))
            root = insert(key,root);
        else
            cout << "The input key<" << key << "> iS have in!" << endl;
    }

    cout << "Bsort_Tree is :" << endl;
    inorder(root);
    cout << endl;
}
void insertSingleKey()
{
    int key;
    cout << "Please input key which inserted:";
    cin >> key;
    if(!find(root,key))
        root = insert(key,root);
    else
        cout << "The input key<" << key << "> iS have in!" << endl;
    cout << "Bsort_Tree is :" << endl;
    inorder(root);
    cout << endl;
}

void search()
{
    int key;
    cout << "Please input key which inserted:";
    cin >> key;
    if(find(root,key))
        cout << "search success!" << endl;
    else
        cout << key << " not exist!" << endl;
}

void run()
{
    int command = 1;

    while(command != 4)
    {
        cout << "Please select:  ";
        cin >> command;
        switch(command)
        {
            case 1:
                createTree();
                break;
            case 2:
                insertSingleKey();
                break;
            case 3:
                search();
                break;
            case 4:
                cout << "Exit successfully!" << endl;
                break;
            default:
                cout << "Error, Please input again!" << endl;
                break;
        }
        cout << endl;
    }
}

int main()
{
    menu();
    run();
}