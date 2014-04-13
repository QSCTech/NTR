#include "player.h"
class Pitaya: public Player{
public:
    // Pitaya(map<int, int> card_define) {
    //     cardDefine = card_define;
    // }

    //无参数构造函数
    Pitaya(map<int, int>);

    // 你的玩家名称
    string yourName();

    // 初始化，传入所有玩家姓名，你的本局牌，剩余的牌（即104 / 玩家数后多余的牌）
    void init(vector<string>, vector<int>, vector<int>);

    // 进行一轮游戏，传入当前下面4个牌堆的牌，每个用户手中的记分牌（用于算牌）
    int run(vector<vector<int>>, map<string, vector<int>>);

    // 选择你要拿走的一堆牌，其它每个用户出了什么牌，返回index。（你会在这次调用后被调用 notifyGetScore 通知你获得了这些分数，因此你无需在这个函数调用中记录分数）
    int getHeap(vector<vector<int>>, map<string, int>);

    // 告诉你这一局你得到了这些牌，如果你没有拿到牌，则不会被调用
    void notifyGetScore(vector<int>);

    // 一轮结束，通知上一轮各玩家的出牌（每个玩家获得的罚分可在下一轮的 run 中获得）
    // 参数：
    //  * 每个玩家在上一轮所出的牌
    // （不强制实现，保证在所有的询问函数之后调用）
    void notifyPostRun(map<string, int>);

private:
    const string myName = "Pitaya";

    //number of players
    int playerCount;

    //name of players
    vector<string> playerList;

    //cards in my hand, the card that haven't appeareder
    vector<int> myCards, cardRem;

    //numbers of NT that each card have
    map<int, int> cardDefine;
    
    //score of each player
    map<string, int> playerScore;

    vector<vector<int>> currentStack;

    //cost of a stack
    int evaluateStackCost(vector<int>);
};
