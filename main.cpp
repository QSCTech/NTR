//#include "main.h"
#include "platform.h"
#include <ctime>
using namespace std;

int main() {
	srand(time(NULL));
	Platform p;
	int count = p.getRoundTime();
	while (count--) {
		p.singleRound();
	}
	return 0;
}