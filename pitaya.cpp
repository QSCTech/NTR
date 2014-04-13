#include "pitaya.h"
#include <ctime>
#include <iostream>

Pitaya::Pitaya(map<int, int> card_define) {
    cardDefine = card_define;
    srand(time(0));
    cardRem.clear();
    for (int i = 0; i < 105; ++i)
    {
        cardRem.push_back(0);
    }
    myCards.clear();
}

string Pitaya::yourName() {
    return myName;
}

void Pitaya::init(vector<string> players, vector<int> card_input, vector<int> remain_card)
{
    playerList = players;
    playerCount = playerList.size();
    myCards = card_input;
    sort(myCards.begin(), myCards.end());
    for (size_t i = 0; i < remain_card.size(); ++i)
    {
        cardRem[remain_card[i]] = -1;
    }
}

int Pitaya::run(vector<vector<int>> stack, map<string, vector<int>> score_card)
{
    int finalEvaluation, returnCard, maxStack, maxStackTop, remainCount, stackHeight, smaller, minStackCost;
    double tmpEvaluation, maxEvaluation;
    vector<int> stackCost;
    currentStack = stack;
    
    maxEvaluation = -99;

    //calculate current score of each player
    for (int i = 0; i < playerCount; ++i)
    {
        playerScore[playerList[i]] = 0;
        for (size_t j = 0; j < score_card[playerList[i]].size(); ++j)
        {
            playerScore[playerList[i]] += cardDefine[score_card[playerList[i]][j]];
        }
    }

    //calculate how much is each stack
    minStackCost = 99;
    for (size_t i = 0; i < currentStack.size(); ++i)
    {
        stackCost.push_back(evaluateStackCost(currentStack[i]));
        minStackCost = min(minStackCost, stackCost.back());
    }


    //for each card in hand
    for (size_t i = 0; i < myCards.size(); ++i)
    {
        //calculate which stack does it belong to
        maxStackTop = 0;
        for (size_t j = 0; j < currentStack.size(); ++j)
        {
            if (currentStack[j].back() < myCards[i] &&
                currentStack[j].back() > maxStackTop)
            {
                maxStackTop = currentStack[j].back();
                maxStack = j;
            }
        }

        if (maxStackTop == 0)
        {
            stackHeight = 0;
            remainCount = 0;
        }
        else
        {
            //the height of the stack
            stackHeight = currentStack[maxStack].size();

            //count remaining card between the card in hand
            //and the top card of the stack
            remainCount = 0;
            for (int j = maxStackTop+1; j < myCards[i]; ++j)
            {
                if (cardRem[j] != -1)
                {
                    remainCount++;
                }
            }            
        }

        //evaluate how small the card is
        smaller = 0;
        for (int j = 1; j < myCards[i]; ++j)
        {
            if (cardRem[j] != -1)
            {
                smaller++;
            }
        }
        
        //comprehensional evaluation
        if (remainCount + stackHeight >= 5)
        {
            tmpEvaluation = - 5.0 * exp(- pow(remainCount + stackHeight - 6, 2));
        }
        else
        {
            tmpEvaluation = 1.0 * (remainCount + stackHeight);
        }

        tmpEvaluation += 3.0 * exp(- 1.0 * smaller - 0.5 * minStackCost);

        if (tmpEvaluation > maxEvaluation)
        {
            maxEvaluation = tmpEvaluation;
            finalEvaluation = i;
        }

        //TODO: player specific optimization

        // cout << "card" << i << ": " << myCards[i] << " Evaluation: " << tmpEvaluation <<endl;
    }
    returnCard = myCards[finalEvaluation];
    myCards.erase(myCards.begin() + finalEvaluation);

    return returnCard;
}

bool cmp(pair<string, int> a, pair<string, int> b)
{
    if (a.second<b.second)
        return true;
    else
        return false;
}

int Pitaya::getHeap(vector<vector<int>> stack, map<string, int> player_card)
{
    int myChoice, maxStack, finalStack, minScore, totalScoreAdd;
    double tmpEvaluation, maxEvaluation;
    vector<int> stackCost;
    vector<vector<int>> tmpStack;
    map<string, int> tmpList, tmpScore;

    maxEvaluation = -99;
    for (size_t i = 0; i < stack.size(); ++i)
    {
        stackCost.push_back(evaluateStackCost(stack[i]));
    }

    for (size_t i = 0; i < stack.size(); ++i)
    {
        tmpStack = stack;
        tmpStack[i].clear();
        tmpStack[i].push_back(myChoice);
        tmpList = player_card;
        tmpScore = playerScore;
        totalScoreAdd = 0;

        //simulate the next round and count how many NTs each player get
        for (int j = 0; j < playerCount; ++j)
        {
            auto currentPlayer = min_element(tmpList.begin(), tmpList.end(), cmp);
            if (currentPlayer->first == myName)
            {
                tmpList.erase(currentPlayer);
                continue;
            }
            maxStack = 0;
            for (size_t k = 0; k < tmpStack.size(); ++k)
            {
                if (tmpStack[k].back() < currentPlayer->second && 
                    tmpStack[k].back() > tmpStack[maxStack].back())
                {
                    maxStack = k;
                }
            }
            if (tmpStack[maxStack].size() == 5)
            {
                for (int k = 0; k < 5; ++k)
                {
                    totalScoreAdd += cardDefine[tmpStack[maxStack][k]];
                }
                tmpScore[currentPlayer->first] += stackCost[maxStack];
                tmpStack[maxStack].clear();
            }
            tmpStack[maxStack].push_back(currentPlayer->second);
            tmpList.erase(currentPlayer);
        }

        minScore = 0;
        for (int j = 0; j < playerCount; ++j)
        {
            if (playerList[j] != myName)
            {
                if (tmpScore[playerList[j]] < minScore)
                {
                    minScore = tmpScore[playerList[j]];
                }   
            }
        }

        tmpEvaluation = -stackCost[i] + 0.5 * minScore + 0.5 * totalScoreAdd / playerCount;
        if (tmpEvaluation > maxEvaluation)
        {
            maxEvaluation = tmpEvaluation;
            finalStack = i;
        }
    }

    return finalStack;
}

void Pitaya::notifyGetScore(vector<int> new_card)
{

}

void Pitaya::notifyPostRun(map<string, int> runState)
{
    for (int i = 0; i < playerCount; ++i)
    {
        cardRem[runState[playerList[i]]] = -1;
    }
}

int Pitaya::evaluateStackCost(vector<int> stack)
{
    int sum = 0;
    for (size_t i = 0; i < stack.size(); ++i)
    {
        sum += cardDefine[stack[i]];        
    }
    return sum;
}
