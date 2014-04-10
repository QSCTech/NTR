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
	while (--count) {
		p.singleRound();
	}
	p.notifyFinish();
	return 0;
}