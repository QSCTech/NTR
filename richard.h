#ifndef RICHARD_H
#define RICHARD_H

#include "player.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Richard: public Player {
	public:
		Naive(map<int, int>);
		string yourName();
		void init(vector<string>, vector<int>, vector<int>);
		int run(vector<vector<int> >, map<string, vector<int> >);
		int getHeap(vector<vector<int> >, map<string, int>);
		void notifyGetScore(vector<int>);
		void notifyPostRun(map<string, int>);
	private:
		map<int, int> levelMap;

		vector<int> myCardVec; // 我手中的卡片
		vector<string> userVec; // 所有用户名字
		vector<int> extraCardVec; // 多余的卡片（无用的）


};

#endif
