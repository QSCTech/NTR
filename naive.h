#ifndef _NAIVE_H
#define _NAIVE_H

#include "player.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Naive: public Player {
	public:
		Naive(map<int, int>);
		string yourName();
		void init(vector<string>, vector<int>, vector<int>);
		int run(vector<vector<int> >, map<string, vector<int> >);
		int getHeap(vector<vector<int> >, map<string, int>);
		void notifyGetScore(vector<int>);
	private:
		vector<string> playerName;
		vector<int> myCard, leftCard;
		map<int, int> cardDefine;
};

#endif
