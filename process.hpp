
#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "resource.hpp"
#define PERCENTAGE 101
#define QUANTUM 1

using namespace std;

enum prioritys{
	REAL_TIME = 0,
	USER_P1,
	USER_P2,
	USER_P3
};

class Process
{
	public:
		Process(){}
		Process(const int pid, const int priority, const int off, const int hmblocks, const int itime,
			const int etime, const bool scan, const bool print, const bool modem, const bool sata, int bres):
			// Construtor:
			pid(pid), priority(priority), memoryOffset(off), amoutBlocks(hmblocks), initTime(itime), processTime(etime),
			usescan(scan), usePrinter(print), useModem(modem), useSATA(sata), blockedResource(bres) { }

		friend ostream& operator<<(ostream& os,const Process& it);

		int getPID();
		void setPID(const int pid);
		int getPriority();
		void setPriority(const int priority);
		int getMemoryOffset();
		void setMemoryOffset(const int off);
		int getAmoutBlocks();
		void setAmoutBlocks(const int hmblocks);

		int getInitTime();
		void setInitTime(const int itime);
		int getExecutionTime();
		void setExecutionTime(const int etime);

		bool getScanner();
		void setScanner(const bool scan);
		bool getPrinter();
		void setPrinter(const bool print);
		bool getModem();
		void setModem(const bool modem);
		bool getSata();
		void setSata(const bool sata);

		int getBlockedResource();
		void setBlockedResource(const int bres);
		bool inMemory();
		void freeResources();
		void check();
		int display();

	private:
		int pid;
		int priority;
		int initTime;
		int memoryOffset;
		int amoutBlocks;
		int processTime;
		bool usePrinter;
		bool usescan;
		bool useModem;
		bool useSATA;
		int blockedResource;
		int existsResource();
		int usesResource();
};

bool firstToExecute(Process p1, Process p2);

#endif // PROCESS_HPP
