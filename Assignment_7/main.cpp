#include <iostream>
#include <queue>
#include <vector>

using namespace std;
int main() {
    int n;
    cin >> n;
    //定义一个优先队列 并且这个是从小到大的队列
    priority_queue<int,vector<int>,greater<int>> weights;

    int weight;
    //读取权重
    for(int i = 0; i < n; i++) {
        cin >> weight;
        weights.push(weight);
    }

    int cost = 0,currentWeight = 0;

    //Huffman算法的应用~
    while(weights.size() >1){
        currentWeight = weights.top();
        weights.pop();
        currentWeight += weights.top();
        weights.pop();
        weights.push(currentWeight);
        cost += currentWeight;

    }
    cout << cost << endl;
}