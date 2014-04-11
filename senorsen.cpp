#include "senorsen.h"
#include <climits>
#include <iostream>

Senorsen::Senorsen(map<int, int> card_define) {
	round = 0;
	myScore = 0;
	cardDefine = card_define;
	myName = "Senorsen";
}

Senorsen::Senorsen(map<int, int> card_define, string name) {
	round = 0;
	myScore = 0;
	cardDefine = card_define;
	myName = name;
}

string Senorsen::yourName() {
	return myName;
}

void Senorsen::init(vector<string> player, vector<int> my_card, vector<int> unused_card) {
	cerr << "Here comes Senorsen! =v=" << endl;
	playerName = player;
	myCard = my_card;
	unusedCard = unused_card;
	cerr << "Unused cards in this game are: ";
	for (auto i = unusedCard.begin(); i != unusedCard.end(); i++) {
		cerr << *i << " ";
	}
	cerr << endl;
	cerr << "Players in this game are: ";
	for (auto i = playerName.begin(); i != playerName.end(); i++) {
		if (*i == myName) {
			myPosition = i - playerName.begin();
		}
		cerr << *i << " ";
	}
	cerr << endl << endl;
}

int Senorsen::run(vector<vector<int> > heap, map<string, vector<int> > score) {
	round++;
	int index = rand();
	index = index % myCard.size();
	int ret = myCard[index];
	myCard.erase(myCard.begin() + index);
	cerr << "[Round " << round << "] Senorsen gave out " << ret << "." << endl;
	return ret;
}

int Senorsen::getHeap(vector<vector<int> > heap, map<string, int> play) {
	int minimum = INT_MAX, ret;
	for (size_t i = 0; i != heap.size(); i++) {
		int total = 0;
		for (size_t j = 0; j != heap[i].size(); j++) {
			total += cardDefine[heap[i][j]];
		}
		if (total < minimum) {
			minimum = total;
			ret = i;
		}
	}
	cerr << "Senorsen decided to take Heap " << ret << "." << endl;
	return ret;
}

void Senorsen::notifyGetScore(vector<int> score) {
	cerr << "[Round " << round << "] Senorsen got " << score[myPosition] << " penalty." << endl;
	myScore += score[myPosition];
}

