#include<iostream>
#include "scheduler.hpp"

using namespace std;

int main(int argq, char* argv[]) {
	if(argq < 2) {
		cerr << "\a Not enough number of arguments!" << endl;
		cerr << "\a Command line: ./run <input.txt>" << endl;
		return -1;
	}

	char* input;
	input = argv[1];

	Scheduler sched;
	InitializeSemaphores();
	sched.readFile(input);
	sched.simulation();

	return 0;
}
