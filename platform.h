#ifndef PLATFORM_H_
#define PLATFORM_H_

// #include "player.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define MAX_CARD = 104;

class Platform {
private:
	map<int, int> level;
	const int player_count = 1;
	// map<string, Player*> players;
	vector<int> cards; //所有的卡片

public:
	Platform();
	// 初始化各个牌的分数
	void initLevels();
	void initCards();

	void printVector();
	




};

#endif