#include "scheduler.hpp"

//clock = seconds passed
void scheduler::startTime() {
	clock = 0;
}

void scheduler::addEndQueue(Process p) {
	switch(p.getPriority()) {
		case REAL_TIME:
			realTIME.push(p);
			break;
		case USER_P1:
			userP1.push(p);
			break;
		case USER_P2:
			userP2.push(p);
			break;
		case USER_P3:
			userP3.push(p);
			break;

	}
}

void scheduler::fillQueue() {
	int i = 0;
	Process p;

	while(i < (int)processes.size() && processes[i].getInitTime() < clock + 1) {
		p = processes[i];
		addEndQueue(p);
		i++;
	}

	processes.erase(processes.begin(),processes.begin()+i);
}

// ## Funcao de execucao de um processo ## //
void scheduler::executesProcess(Process& p) {
	switch(p.getPriority()){
		case REAL_TIME:
			clock += p.getExecutionTime();
			sleep(p.getExecutionTime()-QUANTUM);
			p.setExecutionTime(0);
			break;

		case USER_P1:
		case USER_P2:
		case USER_P3:
			p.check();
			clock += QUANTUM;
			break;

		// o default vai ate o fim do processo, nunca sera usado pois esta no case logo acima
		default: //USUARIO_P3
			int i = 0;
			while(!p.getBlockedResource()) {
				p.check();
				i++;
			}
			clock += QUANTUM*i;
			sleep((QUANTUM*i - 1));
			p.setExecutionTime(p.getExecutionTime() - QUANTUM*i);
			break;
	}
	return;
}

void scheduler::processOrder() {
	sort(processes.begin(), processes.end(), firstToExecute);
}

// ## verify se existe algum processo nas filas que ja pode ser executado ## //
bool scheduler::nextProcess(Process *p) {
	if(!realTIME.empty() && realTIME.front().getInitTime() <= clock) {
		*p = realTIME.front();
		realTIME.pop();
		return true;
	}
	if(!userP1.empty() && userP1.front().getInitTime() <= clock) {
		*p = userP1.front();
		userP1.pop();
		return true;
	}
	if(!userP2.empty() && userP2.front().getInitTime() <= clock) {
		*p = userP2.front();
		userP2.pop();
		return true;
	}
	if(!userP3.empty() && userP3.front().getInitTime() <= clock) {
		*p = userP3.front();
		userP3.pop();
		return true;
	}
	// ## Nao chegaram processes ainda ## //
	return false;
}

bool scheduler::stillExistsProcess() {
	return (
			!realTIME.empty() ||
			!userP1.empty() 	||
			!userP2.empty() 	||
			!userP3.empty() 	|| !processes.empty());
}

void scheduler::displayProcessQueue()
{
	Process x;
	//cout << "Todos os processes: " << endl;
	//for(Process p : processes)
	//dispatcher(p);

	cout << "\n All processes in real time:  " << endl;
	for(int i=0; i<(int)realTIME.size(); i++) {
		x = realTIME.front();
		cout << x << endl;
		realTIME.pop();
		realTIME.push(x);
	}

	cout << "\n All user processes with priority 1:  "<< endl;
	for(int i=0; i<(int)userP1.size(); i++) {
		x = userP1.front();
		cout << x << endl;
		userP1.pop();		// removes next element
		userP1.push(x);	// inserts a process in the end of queue
	}

	cout << "\n All user processes with priority 2:  "<< endl;
	for(int i=0; i<(int)userP2.size(); i++) {
		x = userP2.front();
		cout << x << endl;
		userP2.pop();
		userP2.push(x);
	}

	cout << "\n All user processes with priority 3:  "<< endl;
	for(int i=0; i<(int)userP3.size(); i++) {
		x = userP3.front();
		cout << x << endl;
		userP3.pop();
		userP3.push(x);
	}
}

void scheduler::dispatcher(Process& p) {
	cout << "\n Dispatcher =>" << '\n';
	cout << p << endl;
	executesProcess(p);
	displayExecution(p);
	sleep(QUANTUM);
	return;
}

void scheduler::displayExecution(Process p) {
	cout << "\n  Process " << p.getPID() << " => " << endl;
	cout << "\tPriority: " << p.getPriority() << endl;
	cout << "\tTime Since Arrival: " << clock - p.getInitTime() << endl;
	cout << "\tTime Left To Execute: " << p.getExecutionTime() << endl;
	cout << "\tHolds Any Resources: ";

	switch(p.getBlockedResource()) {
		case WITHOUT_RESOURCES:
			cout << "No";
			break;
		case PRINTER:
			cout << "Printer";
			break;
		case SCANNER:
			cout << "Scanner";
			break;
		case SATA:
			cout << "Sata";
			break;
		case MODEM:
			cout << "Modem";
			break;
	}
	cout << endl;
}

void scheduler::readFile(string filename) {
	fstream txt;	// to make I/O operations on files
	txt.open(filename.c_str());		// opening .txt file
	string data;
	vector<int> tmp;
	char *ptr;
	Process p;
	int id = 0;

	while(getline(txt, data)) 	{
		if(data!="") {
			ptr = strtok((char*)data.c_str(),"\t ,");	// split string into tokens
			while(ptr!=NULL) {
				tmp.push_back(atoi(ptr));
				ptr = strtok(NULL,"\t ,");
			}
		}
	}

	for(int i=0;i<(int)tmp.size();i+=8) {
		p.setPID(id);
		p.setMemoryOffset(-1);
		p.setInitTime(tmp[i]);
		p.setPriority(tmp[i+1]);
		p.setExecutionTime(tmp[i+2]);
		p.setAmoutBlocks(tmp[i+3]);
		p.setPrinter(tmp[i+4]);
		p.setScanner(tmp[i+5]);
		p.setModem(tmp[i+6]);
		p.setSata(tmp[i+7]);
		p.setBlockedResource(WITHOUT_RESOURCES);
		processes.push_back(p);
		id++;
	}
}

//	function that returns how much time has passed
int scheduler::getClock() {
	return clock;
}

void scheduler::simulation() {
	Process p;
	unsigned int offset;
	processOrder();
	startTime();

	while(stillExistsProcess()) {
		fillQueue();
		if(nextProcess(&p)){
			if(!p.inMemory()) {
				offset = m.allocation(p.getAmoutBlocks(),p.getPriority());
				if(offset==MAX_MEM)	{
					cout << "\a\tERROR : MEMORY NOT ALLOCATED TO PROCESS " << p.getPID() << endl;
					p.setPriority(p.getPriority()+1);
					if(p.getPriority() > 3) {
						p.setPriority(3);
					}
					addEndQueue(p);
					clock++;
					continue;
				}
				else if(offset > MAX_MEM){
					p.setExecutionTime(0);
					cout << "\a\tERROR : MEMORY IS BIGGER THEN THE TOTAL " << endl;
					clock++;
					continue;
				}
				else
					p.setMemoryOffset(offset);
			}

			dispatcher(p);
			if(p.getExecutionTime() > 0) {
				p.setPriority(p.getPriority()+1);
				if(p.getPriority() > 3)
					p.setPriority(3);
				addEndQueue(p);
			}
			else {
				cout << "\tProcess " << p.getPID() << " received SIGINT" << endl;
				m.deallocation(p.getMemoryOffset(),p.getAmoutBlocks());
				p.freeResources();
			}
		}
		else{
			clock++;
		}
	}
}
