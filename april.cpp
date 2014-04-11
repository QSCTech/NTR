#include "april.h"
#include <climits>

April::April(map<int, int> card_define)
{
	cardDefine = card_define;
}

string April::yourName()
{
	return "Clever April";
}

void April::init(vector<string> player_name, vector<int> my_card, vector<int> left_card) 
{
	playerName = player_name;
	myCard = my_card;
	leftCard = left_card;
}

int April::run(vector<vector<int> > heap, map<string, vector<int> > score)
{
	//allfive判断是不是所有的heap都满了
	bool allfive = true;
	//minheap记录当前最小数量最少的牌堆
	auto minheap = heap.begin();

	//查看当前牌堆状态
	for (auto iter = heap.begin(); iter != heap.end(); ++iter)
	{
		if (iter->size() < 5)
		{
			allfive = false;
			if (iter->size() < minheap->size())
			{
				minheap = iter;
			}
		}
	}

	//如果所有堆都满了，就输出当前最大，好像有些不太对劲，以后再来改改
	if (allfive)
	{
		int answer = myCard.back();
		myCard.pop_back();
		return answer;
	}
	
	
	//如果所有堆都满了，就输出当前最大，好像有些不太对劲，以后再来改改
	// if (allfive)
	// {
	// 	int answer = myCard.back();
	// 	myCard.pop_back();
	// 	return answer;
	// }


	//否则输出离minheap.last()最近的数，好像也不是最厉害的方法，以后再来改改
	else
	{
		for (auto iter = myCard.begin(); iter != myCard.end(); ++iter)
		{
			if (*iter >= minheap->back())
			{
				int answer = *iter;
				myCard.erase(iter);
				return answer;
			}
		}
		// 如果不满足 暂时决策最小者，以后再改
		int answer = myCard.front();
		myCard.erase(myCard.begin());
		return answer;
	}
}

int April::getHeap(vector<vector<int>> heap, map<string, int> friendCard)
{
	int minpenaly=INT_MAX;
	int minheap;

	vector<int> penalty;
	for (auto iter = heap.begin(); iter != heap.end(); ++iter)
	{
		int sum = 0;
		for(auto card = iter->begin(); card != iter->end(); ++card)
		{
			sum += cardDefine[*card];
		}
		penalty.push_back(sum);
	}

	for (auto iter = penalty.begin(); iter != penalty.end(); ++iter)
	{
		if (*iter<minpenaly)
		{
			minpenaly = *iter;
			minheap = iter - penalty.begin();
		}
	}

	return minheap;
}

void April::notifyGetScore(vector<int> mypenaly){
	//暂时觉得用不上什么
}