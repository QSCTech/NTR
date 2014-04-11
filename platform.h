#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "player.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_CARD 104

class Platform {
private:
	map<int, int> level;
	const int player_count = 2;
	map<string, Player*> players;
	vector<string> names;
	vector<int> cards; //所有的卡片
	map<string, vector<int>> userCards; //每个用户的所有卡片（根据出牌情况更新，会检查牌数、有没有等）
	vector<int> extraCards; //多余的牌
	vector<vector<int>> heapCards; //牌堆中的牌
	map<string, vector<int>> scoreCards; // 手中的记分牌

public:
	Platform();
	// 初始化各个牌的分数
	void initLevels();
	void initCards();
	void singleRound(); //进行一回合的游戏
	void printVector(vector<int>);
	void init();
	int getRoundTime(); // 获取即将进行几轮比赛
	void notifyFinish(); // 通知他游戏结束了
};

#endif
