#ifndef APRIL_H_
#define APRIL_H_

#include "player.h"
#include <string>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class April: public Player
{
public:

	April(map<int, int>);

	string yourName();

	void init(vector<string>, vector<int>, vector<int>);

	int run(vector<vector<int>>, map<string, vector<int>>);
	
	int getHeap(vector<vector<int>>, map<string, int>);
	
	void notifyGetScore(vector<int>);

private:
	//mycard用于记录我当前的所有牌
	vector<int> myCard;

	//friends用于记录所有玩家的姓名
	vector<string> playerName;

	//cardDefine用于储存牌点数与牛头数
	map<int, int> cardDefine;

	//leftCard用于记录剩余牌数
	vector<int> leftCard;
};

#endif
