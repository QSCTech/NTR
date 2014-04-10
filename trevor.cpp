#include "trevor.h"
#include <ctime>
#include <climits>

Trevor::Trevor(map<int, int> card_define) {
	cardDefine = card_define;
}

string Trevor::yourName() {
	return "Trevor";
}

void Trevor::init(vector<string> player_name, vector<int> my_card, vector<int> left_card) {
	playerName = player_name;
	myCard = my_card;
	leftCard = left_card;
	for (int i = 0; i < leftCard.size(); ++i) {
		cardFlag[leftCard[i]] = 0;
	}
}

int Trevor::run(vector<vector<int> > heap, map<string, vector<int> > score) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < heap[i].size(); ++j) {
			cardFlag[heap[i][j]] = 0;
		}
	}
	for (int i = 0; i < playerName.size(); ++i) {
		for (int j = 0; j < score[playerName[i]].size(); ++j) {
			cardFlag[score[playerName[i]][j]] = 0;
		}
	}
	int index = getTactics(heap);
	int ret = myCard[index];
	myCard.erase(myCard.begin() + index);
	return ret;
}

int Trevor::getHeap(vector<vector<int> > heap, map<string, int> play) {
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

void Trevor::notifyGetScore(vector<int> score) {

}

int Trevor::getTactics(vector<vector<int> > heap){
	int index = rand() % myCard.size();
	int distence, minDistence = -1;
	vector<int> distenceVec;
	vector<int> blackList;
	map<int, int> cardDistence;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < myCard.size(); ++j) {
			distence = getDistence(heap[i], myCard[j]);
			if (distence <= 10 && distence > 0) {
				if (heap[i].size() < 4) {
					index = j;
					return index;
				} else {
					blackList.push_back(j);
				}
			}
			cardDistence[distence] = j;
			distenceVec.push_back(distence);
		}
	}
	// quickSort(distenceVec, 0, distenceVec.size());
	int minScore = getMinScore(heap);
	if (minDistence < 0) {
		if (minScore < 5) return myCard[0];
		else return myCard[myCard.size() - 1];
	}
	while(blackList.size() < myCard.size() && getIndex(blackList, index)) {
		index = rand() % myCard.size();
	}
	return index % myCard.size();
}

int Trevor::getIndex(vector<int> a, int value){
	for (int i = 0; i < a.size(); ++i)
		if (a[i] == value) return i;
	return -1;
}
int Trevor::getMinScore(vector<vector<int> > heap) {
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

	return minimum;
}
int Trevor::getDistence(vector<int> heap, int cardNum) {
	int distence = heap.size();
	for (int i = heap[heap.size() - 1]; i < cardNum; ++i) {
		if (cardFlag[i]) distence++;
	};
	return distence;
}

int Trevor::partition(vector<int> &vi, int low, int up) {
	int pivot = vi[up];
	int i = low-1;
	for (int j = low; j < up; j++) {
		if(vi[j] <= pivot) {
			i++;
			swap(vi[i], vi[j]);
		}
	}
	swap(vi[i+1], vi[up]);
	return i+1;
}
void Trevor::quickSort(vector<int> &vi, int low, int up) {
	if(low < up) {
		int mid = partition(vi, low, up);
		quickSort(vi, low, mid-1);
		quickSort(vi, mid+1, up); 
	}
}