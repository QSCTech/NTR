#include "naive.h"
#include <ctime>
#include <climits>

Naive::Naive(map<int, int> card_define) {
	cardDefine = card_define;
	srand(time(0));
}

string Naive::yourName() {
	return "Naive";
}

void Naive::init(vector<string> player_name, vector<int> my_card, vector<int> left_card) {
	playerName = player_name;
	myCard = my_card;
	leftCard = left_card;
}

int Naive::run(vector<vector<int> > heap, map<string, vector<int> > score) {
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
	return ret;
}

void Naive::notifyGetScore(vector<int> score) {

}
