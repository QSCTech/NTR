#include "naive.h"
#include <climits>
#include <iostream>

Naive::Naive(map<int, int> card_define) {
	round = 0;
	myScore = 0;
	cardDefine = card_define;
}

string Naive::yourName() {
	return myName;
}

void Naive::init(vector<string> player, vector<int> my_card, vector<int> unused_card) {
	cerr << "Hello, the Naive player now starts playing!" << endl;
	playerName = player;
	myCard = my_card;
	unusedCard = unused_card;
	for (size_t i = 0; i != player.size(); i++) {
		if (player[i] == myName) {
			myPosition = i;
			break;
		}
	}
}

int Naive::run(vector<vector<int> > heap, map<string, vector<int> > score) {
	round++;
	cerr << "Round " << round << " starts!" << endl;
	int index = rand();
	index = index % myCard.size();
	int ret = myCard[index];
	myCard.erase(myCard.begin() + index);
	return ret;
}

int Naive::getHeap(vector<vector<int> > heap, map<string, int> play) {
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
	cerr << "I decided to take Heap " << ret << "." << endl;
	return ret;
}

void Naive::notifyGetScore(vector<int> score) {
	cerr << "In Round " << round << " I got " << score[myPosition] << " penalty." << endl;
	myScore += score[myPosition];
}

