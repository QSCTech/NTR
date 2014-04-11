#include "NTRAI_Leo.h"
#include <climits>
#include <iostream>

NTRAI_Leo::NTRAI_Leo(map<int, int> card_define) 
{
    round = 0;
    myScore = 0;
    cardDefine = card_define;
    for (int i = 0; i < 104; i++) {
        ifUsedCard.push_back(false);
    }
}

string NTRAI_Leo::yourName() {
    return myName;
}

void NTRAI_Leo::init(vector<string> player_name, vector<int> my_card, vector<int> unused_card)
{
    playerName = player_name;
    playerCount = playerName.size();
    myCard = my_card;
    cerr<<myCard.size()<<"this is my card size!!!\n";
    for (auto i = unused_card.begin(); i != unused_card.end(); i++) {
        ifUsedCard[*i - 1] = true;
    }
}

int NTRAI_Leo::run(vector<vector<int> > heaps, map<string, vector<int> > score)
{
    for (auto it = score.begin(); it != score.end(); it++) {
        auto vec = it->second;
        for (auto i = vec.begin(); i != vec.end(); i++)
            ifUsedCard[*i - 1] = true;
    }
    int minFee = INT_MAX;
    int index = -1;
    auto chosenCard = myCard.begin();
    for (auto card = myCard.begin(); card != myCard.end();card++) {
        int cardNum = *card; cerr<<cardNum<<"****"<<endl;
        int fee = (104 - cardNum) / 2;
        auto changedHeap = heaps.begin();
        int changedHeapLargestNumber = INT_MAX;
        for (auto heap = heaps.begin(); heap != heaps.end(); heap++) {
            int heapLargestNumber = *(heap->rbegin());
            if ((heapLargestNumber < cardNum) && (heapLargestNumber < changedHeapLargestNumber)) {
                changedHeapLargestNumber = heapLargestNumber;
                changedHeap = heap;
            }
        }
        if (changedHeapLargestNumber == INT_MAX) {
            fee += 10 * NTRAI_Leo::getMinimumHeap(heaps);
        } else {
            int heapSize = changedHeap->size();
            if (heapSize == 5) {
                fee += NTRAI_Leo::getHeapScore(*changedHeap);
            } else {
                int remainedCardSum = NTRAI_Leo::getUnusedCardSum(changedHeapLargestNumber, cardNum-1);
                if (remainedCardSum + heapSize >= 5 && playerCount + heapSize >= 5) {
                    fee += remainedCardSum / 5 * 10 * NTRAI_Leo::getHeapScore(*changedHeap) + cardDefine[cardNum] * 10;
                } else {
                    fee -= (104 - (cardNum - changedHeapLargestNumber));
                }
            }
        }
        if (fee < minFee) {
            cerr<<minFee<<endl;
            index = cardNum;
            minFee = fee;
            chosenCard = card;
        } 
    }
    myCard.erase(chosenCard);
    cerr<<"Leo give out "<<index<<endl;
    return index;
}

int NTRAI_Leo::getHeapScore(vector<int> heap)
{
    int score = 0;
    for (auto i = heap.begin(); i < heap.end();i++) {
        score += cardDefine[*i];
    }
    return score;
}

int NTRAI_Leo::getMinimumHeap(vector< vector <int> > heaps)
{
    int score = INT_MAX;
    int index = -1;
    for (int i = 0; i < (int) heaps.size(); i++) {
        int heapScore = NTRAI_Leo::getHeapScore(heaps[i]);
        if (heapScore < score) {
            score = heapScore;
            index = i;
        }
    }
    return index;
}

int NTRAI_Leo::getHeap(vector<vector<int> > heap, map<string, int> play)
{
    return NTRAI_Leo::getMinimumHeap(heap);
}

int NTRAI_Leo::getUnusedCardSum(int l, int r)
{
    int sum = 0;
    for (int i = l; i <= r; i++) {
        if ( !ifUsedCard[i] ) sum ++;
    }
    return sum;
}

void NTRAI_Leo::notifyGetScore(vector<int> heap)
{
    for (auto card = heap.begin(); card < heap.end(); card++) {
        myScore += cardDefine[*card]; 
    }
}

