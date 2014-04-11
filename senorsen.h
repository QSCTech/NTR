#ifndef _SENORSEN_H
#define _SENORSEN_H

#include "player.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class Senorsen: public Player {
	public:
		Senorsen(map<int, int>);
		Senorsen(map<int, int>, string);
		string yourName();
		void init(vector<string>, vector<int>, vector<int>);
		int run(vector<vector<int> >, map<string, vector<int> >);
		int getHeap(vector<vector<int> >, map<string, int>);
		void notifyGetScore(vector<int>);
	private:
		int round;			// current round
		int myScore;			// my current score
		int myPosition;			// my position(index) in the player vector
		vector<string> playerName;	// the names of all players (useless?)
		vector<int> myCard;		// cards currently in my hand
		vector<int> unusedCard;		// unsed cards in this game
		map<int, int> cardDefine;	// card number -- NTR
		string myName;
};

#endif

