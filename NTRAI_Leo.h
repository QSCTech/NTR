#ifndef _NTRAI_LEO_H
#define _NTRAI_LEO_H

#include "player.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class NTRAI_Leo: public Player {
	public:
		NTRAI_Leo(map<int, int>);
		string yourName();
		void init(vector<string>, vector<int>, vector<int>);
		int run(vector<vector<int> >, map<string, vector<int> >);
		int getHeap(vector<vector<int> >, map<string, int>);
		void notifyGetScore(vector<int>);
	private:
		int round;			// current round
		int myScore;			// my current score
        int playerCount;
		vector<string> playerName;	// the names of all players (useless?)
		vector<int> myCard;		// cards currently in my hand
		vector<bool> ifUsedCard;		// unsed cards in this game
		map<int, int> cardDefine;	// card number -- NTR
		const string myName = "leeleo3x";
        int getHeapScore(vector<int>);
        int getMinimumHeap(vector<vector<int> >);
        int getUnusedCardSum(int l, int r);
};

#endif
