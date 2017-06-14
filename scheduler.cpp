#include "scheduler.hpp"

// função que inicia o tempo do escalonador
//clock = aquantidade de segundo de execução
void Scheduler::startTime() {
	clock = 0;
}

// função para adicionar processos a fila de processos
void Scheduler::addEndQueue(Process p) {
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

// função para preencher a fila FIFO de processos de acordo com a prioridade
void Scheduler::fillQueue() {
	int i = 0;
	Process p;

	while(i < (int)processes.size() && processes[i].getInitTime() < clock + 1) {
		p = processes[i];
		addEndQueue(p);
		i++;
	}

	processes.erase(processes.begin(),processes.begin()+i);
}

// função para executar um processo
void Scheduler::executesProcess(Process& p) {
	switch(p.getPriority()){
		case REAL_TIME:
			clock += p.getExecutionTime();
			sleep(p.getExecutionTime()-QUANTUM);
			p.setExecutionTime(0);
			break;

		case USER_P1:
		case USER_P2:
		case USER_P3:
			p.gives();
			clock += QUANTUM;
			break;

		default:			// percorre até o final do processo
			int i = 0;
			while(!p.getBlockedResource()) {
				p.gives();
				i++;
			}
			clock += QUANTUM*i;
			sleep((QUANTUM*i - 1));
			p.setExecutionTime(p.getExecutionTime() - QUANTUM*i);
			break;
	}
	return;
}

// função determina ordem dos processos basseado na tempo de chegada
void Scheduler::processOrder() {
	sort(processes.begin(), processes.end(), firstToExecute);
}

// função que sempre checa se algum processo está pronto para ser executado
// true = sim ; false = não
bool Scheduler::nextProcess(Process *p) {
	if(!realTIME.empty() && realTIME.front().getInitTime() <= clock) {
		*p = realTIME.front();
		realTIME.pop();	// remove o próximo elemento
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

	return false;
}

// função que verifica se ainda existe algum processo a ser executado
// true = sim ; false = não
bool Scheduler::stillExistsProcess() {
	return (!realTIME.empty() || !userP1.empty() || !userP2.empty() || !userP3.empty() 	|| !processes.empty());
}

// função que apresenta fila de processos
void Scheduler::displayProcessQueue()
{
	Process x;

	cout << "\n All processes in real time:  " << endl;
	for(int i=0; i<(int)realTIME.size(); i++) {
		x = realTIME.front();
		cout << x << endl;
		realTIME.pop();		// remove o próximo elemento
		realTIME.push(x);	// insere um processo no final da fila
	}

	cout << "\n All user processes with priority 1:  "<< endl;
	for(int i=0; i<(int)userP1.size(); i++) {
		x = userP1.front();
		cout << x << endl;
		userP1.pop();
		userP1.push(x);
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

// função que exbice informações sobre o processo e o executa
void Scheduler::dispatcher(Process& p) {
	cout << "\n Dispatcher =>" << '\n';
	cout << p << endl;
	executesProcess(p);
	displayExecution(p);
	sleep(QUANTUM);
	return;
}

// função que apresenta dados do processo em execução
void Scheduler::displayExecution(Process p) {
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

// função que lê arquivo de entrada e atribui os valores ao processo
void Scheduler::readFile(string filename) {
	fstream txt;	// realiza operações de E/S em algum arquivo
	txt.open(filename.c_str());		// abrindo arquivo .txt
	string data;
	vector<int> tmp;
	char *ptr;
	Process p;
	int id = 1;

	while(getline(txt, data)) 	{
		if(data != "") {
			ptr = strtok((char*)data.c_str(),"\t ,");	// divide string em tokens
			while(ptr != NULL) {
				tmp.push_back(atoi(ptr));
				ptr = strtok(NULL,"\t ,");
			}
		}
	}

	// atibuição dos valores do processo a instancia
	for(int i = 0; i < (int)tmp.size(); i += 8) {
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

//	função que retorna o tempo de execução
int Scheduler::getClock() {
	return clock;
}

// função que executa processos
void Scheduler::simulation() {
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
