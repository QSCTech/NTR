//#include "main.h"
#include "platform.h"
#include <ctime>
#include <random>
#include <chrono>
#include <iostream>
using namespace std;

int main() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	srand(seed);
	Platform p;
	int count = p.getRoundTime();
	for (int i = 0; i != count; ++i) {
		cout << "Round " << i << " Start\n";
		p.singleRound();
	}
	p.notifyFinish();
	return 0;
}