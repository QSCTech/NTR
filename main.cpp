//#include "main.h"
#include "platform.h"
#include <ctime>
#include <random>
#include <chrono>
#include <iostream>
using namespace std;

#define ROUND 10000

int main() {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	srand(seed);
	map <string, int> data;

	for (int i = 0; i != ROUND; ++i) {
		cout << "Round " << i << " Started" <<endl;
		Platform p;
		int count = p.getRoundTime();
		for (int i = 0; i != count; ++i) {
			cerr << "Round " << i << " Start\n";
			p.singleRound();
		}
		p.notifyFinish();
		map <string, int> temp = p.getScore();

		for (auto iter = temp.begin(); iter != temp.end(); ++iter) {
			try {
				data[iter->first] += iter->second;
			} catch(out_of_range ) {
				data.insert(*iter);
			}
		}
	}

	cout << "Final ranklist\n";
	for (auto iter = data.begin(); iter != data.end(); ++iter) {
		cout << iter->first << '\t' << iter->second << endl;
	}
	
	return 0;
}