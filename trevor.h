#ifndef _TREVOR_H
#define _TREVOR_H

#include "player.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Trevor: public Player {
	public:
		Trevor(map<int, int>);
		string yourName();
		void init(vector<string>, vector<int>, vector<int>);
		int run(vector<vector<int> >, map<string, vector<int> >);
		int getHeap(vector<vector<int> >, map<string, int>);
		void notifyGetScore(vector<int>);
	private:
		vector<string> playerName;
		vector<int> myCard, leftCard;
		map<int, int> cardDefine;
		int cardFlag[105];
		int getTactics(vector<vector<int>>);
		int getIndex(vector<int> a, int value);
		int getMinScore(vector<vector<int> > heap);
		int getDistence(vector<int> heap, int cardNum);
};

#endif
