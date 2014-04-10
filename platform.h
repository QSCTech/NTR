#ifndef PLATFORM_H_
#define PLATFORM_H_

// #include "player.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class Platform {
private:
	map<int, int> level;
	const int player_count = 1;
	// map<string, Player*> players;

public:
	Platform();
	// 初始化各个牌的分数
	void initLevels();





};

#endif