#ifndef MAIN_H_
#define MAIN_H_

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class Player{
public:
	//无参数构造函数
	Player();

	// 你的玩家名称
	virtual string yourName() = 0;

	// 初始化，传入所有玩家姓名，你的本局牌
	virtual void init(vector<string>, vector<int>) = 0;

	// 进行一轮游戏，传入当前下面4个牌堆的牌，每个用户手中的记分牌（用于算牌）
	virtual int run(vector<int>, map<string, vector<int>>) = 0;

	// 选择你要拿走的一堆牌，其它每个用户出了什么牌，返回index。（你会在这次调用后被调用 notifyGetScore 通知你获得了这些分数，因此你无需在这个函数调用中记录分数）
	virtual int getHeap(vector<int>, map<string, int>);

	// 告诉你这一局你得到了这些牌
	virtual void notifyGetScore(vector<int>) = 0;
};

#endif