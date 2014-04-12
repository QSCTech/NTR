#include <iostream>
#include <algorithm>
#include "richard.h"

Richard::Richard(map<int, int> levelMap) {
	this->levelMap = levelMap;
}

string Richard::yourName() {
	return "Richard";
}

void Richard::init(vector<string> userName, vector<int> cards, vector<int> extras) {
	this->userVec = userName;
	this->myCardVec = cards;
	this->extraCardVec = extras;
}

int Richard::run(vector<vector<int>> heapVec, map<string, vector<int>> scoreMap) {
	int temp = myCardVec.back();
	myCardVec.erase(myCardVec.end() - 1);
	return temp;
}

int Richard::getHeap(vector<vector<int>> heapVec, map<string, int> userHand) {
	vector<int> heapSumVec;
	for (auto iter : heapVec) {
		int sum = 0;
		for_each(iter.begin(), iter.end(), [&sum](int temp) {
			sum += temp;
		});
		heapSumVec.push_back(sum);
	}

	auto minIter = min_element(heapSumVec.begin(), heapSumVec.end());
	return minIter - heapSumVec.begin();
};

void Richard::notifyGetScore(vector<int> getScoreVec) {

}

void Richard::notifyPostRun(map<string, int> userHand) {

}