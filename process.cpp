#include "process.hpp"

ostream& operator<<(ostream& pl,const Process& punit) {
	pl << "\tPID: " << punit.pid << '\n';
	pl << "\tPriority: " << punit.priority << '\n';
	pl << "\tInitialization Time: " << punit.initTime << '\n';
	pl << "\tExecuting Time: " << punit.processTime << '\n';
	pl << "\tMemory Offset: " << punit.memoryOffset << '\n';
	pl << "\tBlocks Amount " << punit.amoutBlocks << '\n';
	pl << "\tPrinters: " << punit.usePrinter << '\n';
	pl << "\tScanners: " << punit.usescan << '\n';
	pl << "\tModems: " << punit.useModem << '\n';
	pl << "\tSATA: " << punit.useSATA;
	return pl;
}

// metodos get() e set() da classe Process
int Process::getPID() {
 	return this->pid;
}
void Process::setPID(const int pid) {
 	this->pid = pid;
}

int Process::getPriority() {
 	return this->priority;
}
void Process::setPriority(const int priority) {
 	this->priority = priority;
}

int Process::getMemoryOffset() {
 	return this->memoryOffset;
}
void Process::setMemoryOffset(const int off) {
	this->memoryOffset = off;
}

int Process::getAmoutBlocks() {
	return this->amoutBlocks;
}
void Process::setAmoutBlocks(const int hmblocks) {
	this->amoutBlocks = hmblocks;
}

int Process::getInitTime() {
	return this->initTime;
}
void Process::setInitTime(const int itime) {
	this->initTime = itime;
}

int Process::getExecutionTime() {
	return this->processTime;
}
void Process::setExecutionTime(const int etime) {
	this->processTime = etime;
}

bool Process::getScanner() {
	return this->usescan;
}
void Process::setScanner(const bool scan) {
	this->usescan = scan;
}

bool Process::getPrinter() {
	return this->usePrinter;
}
void Process::setPrinter(const bool print) {
	this->usePrinter = print;
}

bool Process::getModem() {
	return this->useModem;
}
void Process::setModem(const bool modem) {
	this->useModem = modem;
}

bool Process::getSata() {
	return this->useSATA;
}
void Process::setSata(const bool sata) {
	this->useSATA = sata;
}

int Process::getBlockedResource() {
	return this->blockedResource;
}

void Process::setBlockedResource(const int bres) {
	this->blockedResource = bres;
}

// função que bloqueia recurso
void Process::check() {
	int resource, hit;

	freeResource(resource);
	resource = usesResource();
	hit = blockResource(resource);
	if(hit) {
		blockedResource = resource;
	}
	processTime -= QUANTUM;
}

// 1 = bloqueado; 0 = livre
void Process::freeResources() {
	if(blockedResource != 0){
		freeResource(blockedResource);
		blockedResource = 0;
	}
}

// função que verifica se algum recurso está sento utilizado
int Process::existsResource() {
	int is = WITHOUT_RESOURCES;
	if(getScanner() || getPrinter() || getModem() || getSata()) {
		is = WITH_RESOURCES;
	}
	return is;
}

// função que checa se existem recursos e se eles são usados
// se nenhum recurso for usado, deve retornar 0
// mas, dependendo do recurso, o retorno pode ser 1, 2 ou 3
int Process::usesResource() {
	srand(time(NULL));		// cada vez cria uma sequência nova
	int use = existsResource();
	if(use) {
		use = 0;
		if(rand()%100 < PERCENTAGE) {
			int redo;
			while(redo) {
				redo = 0;
				use = rand()%4 + 1;
				if (use == 1)
						if(!getScanner()) redo = 1;
				else if(use == 2)
						if(!getPrinter()) redo = 1;
				else if(use == 3)
						if(!getModem()) redo = 1;
				else if(use == 4)
						if(!getSata()) redo = 1;
			};
		}
	}
	return use;
}

// função que verifica se processo está em memória
bool Process::inMemory() {
	bool inside = false;
	if(this->memoryOffset != -1) {
		inside = true;
	}
	return inside;
}

// função para verificar ordem de execução
bool firstToExecute(Process p1, Process p2) {
	return p1.getInitTime() < p2.getInitTime();
}
