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

int Richard::run(vector<vector<int>> heapVec, map<string, vector<int> > scoreMap) {
	return 0;
}

int Richard::getHeap(vector<vector<int>> heapVec, map<string, int> userHand) {
	vector<int> heapSumVec;
	return 0;
};

void Richard::notifyGetScore(vector<int> getScoreVec) {

}

void Richard::notifyPostRun(map<string, int> userHand) {

}