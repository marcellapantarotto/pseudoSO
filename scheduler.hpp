#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include "process.hpp"
#include "memory.hpp"

class Scheduler
{
	public:
		int clock;
		void readFile(string filename);
		int getClock();
		void simulation();
		
	private:
		//typedef std::vector<Process> process_t;
		vector<Process> processes;
		queue<Process> userP1;
		queue<Process> userP2;
		queue<Process> userP3;
		queue<Process> realTIME;

		Memory m;
		void startTime();
		void addEndQueue(Process p);
		void fillQueue();
		void executesProcess(Process& p);
		void processOrder();
		bool nextProcess(Process *p);
		bool stillExistsProcess();
		void displayProcessQueue();
		void dispatcher (Process& p);
		void displayExecution(Process p);
};

#endif //SCHEDULER_HPP
