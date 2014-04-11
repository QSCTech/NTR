#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

// 所有纯虚函数必须在子类中实现！
class Player {
public:
	// 构造函数
	// 参数：
	// 	* 牌点数（1~104）--牛头数的映射关系，请自行保存（之后所有卡牌都以点数指定）
	// TODO 请实现一个这样的构造函数（无需关心父类，将会被自动构造）
	// YourClass(map<int, int>); 

	// 返回你的玩家名称（仅会在游戏开始前被调用一次）
	virtual string yourName() = 0;

	// 游戏初始化
	// 参数：
	// 	* 所有玩家姓名
	// 	* 你所获得的手牌
	// 	* 本场游戏未被使用的牌 == (104 - 4) % NumberOfPlayers
	virtual void init(vector<string>, vector<int>, vector<int>) = 0;

	// 一轮游戏开始，询问出牌
	// 参数：
	// 	* 当前4个牌堆中的所有牌（每堆中按从小到大排列）
	// 	* 每个玩家已获得的记分牌
	virtual int run(vector<vector<int>>, map<string, vector<int>>) = 0;

	// 翻牌之后，出现需选走一堆牌的情况，询问选择（返回牌堆号，从0开始）
	// 参数：
	// 	* 其它每个用户出了什么
	// （你会在这次调用后被调用 notifyGetScore 通知你获得了这些牌，
	// 因此你无需在这个函数调用中记录分数）
	virtual int getHeap(vector<vector<int>>, map<string, int>) = 0;

	// 一轮结束，通知获得的卡牌
	// 参数：
	// 	* 获得的卡牌
	// （如果你没有拿到牌，则不会被调用）
	virtual void notifyGetScore(vector<int>) = 0;

	// 一轮结束，通知上一轮各玩家的出牌（每个玩家获得的罚分可在下一轮的 run 中获得）
	// 参数：
	// 	* 每个玩家在上一轮所出的牌
	// （不强制实现，保证在所有的询问函数之后调用）
	virtual void notifyPostRun(map<string, int>) {};
};

#endif
