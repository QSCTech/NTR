#include "platform.h"
#include <iostream>

#include "naive.h"
#include "april.h"
using namespace std;

Platform::Platform() {
	//TODO: 初始化各个玩家
	initLevels();

	vector<int> t;
	Player *p = new Naive(level);
	string name = p->yourName();
	players.insert(pair <string, Player*> (name, p));
	scoreCards.insert(pair <string, vector<int>> (name, t));

	p = new April(level);
	name = p->yourName();
	players.insert(pair <string, Player*> (name, p));
	scoreCards.insert(pair <string, vector<int>> (name, t));


	for (auto iter = players.begin(); iter != players.end(); ++iter) {
		names.push_back(iter->first);
	}

	initCards();
	init();
}

int Platform::getRoundTime() {
	return (MAX_CARD - extraCards.size() - 4) / players.size();
}

void Platform::initLevels() {
	
	// http://zh.wikipedia.org/wiki/%E8%B0%81%E6%98%AF%E7%89%9B%E5%A4%B4%E7%8E%8B
	for (int i = 1; i <= MAX_CARD; ++i) {
		if ( (i - 5) % 5 == 0) {
			level.insert(pair <int, int>(i, 2)); 
			continue;
		}
		if (i % 10 == 0) {
			level.insert(pair <int, int>(i, 3)); 
			continue;
		}
		if (i % 11 == 0) {
			level.insert(pair <int, int>(i, 5));
			continue;
		}
		if (i == 55) {
			level.insert(pair <int, int>(i, 7));
			continue;
		}
		level.insert(pair <int, int>(i, 1));
	}
	// for (auto iter = level.begin(); iter != level.end(); ++iter) {
	// 	cout << iter->first << ' ' << iter->second<<endl;
	// }
}

void Platform::initCards() {
	cout << "Initialing Cards\n";
	for (int i = 1; i <= MAX_CARD; ++i) 
		cards.push_back(i);
	random_shuffle(cards.begin(), cards.end());

	auto iter = cards.begin();

	int avaliableCount = MAX_CARD - 4;
	extraCards.resize(avaliableCount % player_count);
	copy(iter, iter + (avaliableCount % player_count), extraCards.begin());
	sort(extraCards.begin(), extraCards.end());
	iter += avaliableCount % player_count;

	for (int i = 0; i != player_count; ++i) {
		vector<int> tempCards(avaliableCount / player_count);
		copy(iter, iter + avaliableCount / player_count, tempCards.begin());
		sort(tempCards.begin(), tempCards.end());
		userCards.insert(pair <string, vector<int>> (names[i], tempCards));
		iter = iter + avaliableCount / player_count;
	}

	while (iter != cards.end()) {
		vector<int> heap;
		heap.push_back(*iter);
		heapCards.push_back(heap);
		++iter;
	}
	cout << "Initial Card complete\n";
	
}

void Platform::printVector(vector<int> vec) {
	for (auto ai = vec.begin(); ai != vec.end(); ++ai) 
		cout << *ai << ' ';
	cout << endl;
}

void Platform::singleRound() {
	map<int, string> operation;
	map<string, int> operationReversed;

	for (auto iter = players.begin(); iter != players.end(); ++iter) {
		cout << "\tUser " << iter->first << " Start." << endl;
		int retCard = iter->second->run(heapCards, scoreCards);



		vector<int> &tempUserCard = userCards[iter->first];
		// 判断是否存在这张牌
		if (find(tempUserCard.begin(), tempUserCard.end(), retCard) == tempUserCard.end()) {
			cerr << "User: " + iter->first + " returns error AT run:" << retCard << endl;
			cout << "Heap top dumped:" << endl;
			for (auto heapIter = heapCards.begin(); heapIter != heapCards.end(); ++heapIter) {
				printVector(*heapIter);
			}
			exit(1);
		}
		tempUserCard.erase(find(tempUserCard.begin(), tempUserCard.end(), retCard));


		operation.insert(pair <int, string> (retCard, iter->first));
		operationReversed.insert(pair <string, int> (iter->first, retCard));
		// 将出牌序列保存起来
	}


	for (auto iter = operation.begin(); iter != operation.end(); ++iter) {
		Player *player = players[iter->second];
		int opt = iter->first;

		// 找出一个最大的，符合要求的牌堆
		int cardMax = -1;
		auto maxIter = heapCards.begin();
		for (auto hiter = heapCards.begin(); hiter != heapCards.end(); ++hiter) {
			int tmpMax = *max_element(hiter->begin(), hiter->end());
			if (tmpMax > cardMax && tmpMax < opt) {
				cardMax = tmpMax;
				maxIter = hiter;
			}
		}

		if (cardMax == -1) {
			//没有找到，需要询问他删除那个牌堆了
			int heapToGet = player->getHeap(heapCards, operationReversed);
			if (heapToGet < 0 || heapToGet > 3) {
				cerr << "User: " + iter->first << " returns error AT getHeap: " << heapToGet <<endl;
				exit(1);
			}

			// 将即将积分的堆临时保存
			auto heapIter = &heapCards[heapToGet];
			sort(heapIter->begin(), heapIter->end());
			player->notifyGetScore(*heapIter);
			heapIter->clear();
			heapIter->push_back(iter->first);
			scoreCards[iter->second].insert(scoreCards[iter->second].end(), heapIter->begin(), heapIter->end());

		} else {
			// 找到了一个最大的，并且应该将它放上去
			maxIter->push_back(iter->first);
			sort(maxIter->begin(), maxIter->end());
			if (maxIter->size() > 5) {
				//超过5个，需要放进去了
				player->notifyGetScore(*maxIter);
				scoreCards[iter->second].insert(scoreCards[iter->second].end(), maxIter->begin(), maxIter->end());
				maxIter->clear();
				maxIter->push_back(iter->first);
			} else {
				// 没发生什么事情
			}
		}
	}

	for (auto iter = operation.begin(); iter != operation.end(); ++iter) {
		Player *player = players[iter->second];
		player->notifyPostRun(operationReversed);
	}
}

void Platform::init() {
	for (auto iter = names.begin(); iter != names.end(); ++iter) {
		players[*iter]->init(names, userCards[*iter], extraCards);
	}
}

void Platform::notifyFinish() {
	cout << endl << endl << "User Score List:" << endl;
	for (auto iter = scoreCards.begin(); iter != scoreCards.end(); ++iter) {
		int sum = 0;
		for (auto io = iter->second.begin(); io != iter->second.end(); ++io) {
			sum += level[*io];
		}
		cout << iter->first << '\t' << sum << endl;
	}
	cout << endl;
}