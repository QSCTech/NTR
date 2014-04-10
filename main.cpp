//#include "main.h"
#include "platform.h"
#include <ctime>
#include <iostream>
using namespace std;

int main() {
	srand(time(NULL));
	Platform p;
	int count = p.getRoundTime();
	while (--count) {
		p.singleRound();
	}
	p.notifyFinish();
	return 0;
}