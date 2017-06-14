#include "memory.hpp"
#include <iostream>

// instância de Memory
Memory::Memory(){
	int i=0;
	while(i < MAX_MEM){
		memoir[i] = 0;		// zera memória
		i++;
	};
}

// método para mostra memória disponível
void Memory::display(){
	for(int i = 0; i < MAX_MEM; i++){
		cout << memoir[i];
	}
	cout << endl;
}

// método de alocação de memória, checando a quantidade e RAM disponível
unsigned int Memory::allocation(unsigned int qtd, int tipo_p){
	unsigned int offset = MAX_MEM;
	switch(tipo_p){
		case REAL_TIME:
			if(qtd > MAX_REAL){
				offset = 1025;
				return offset;
			}
			offset = verification(qtd,START,MAX_REAL);
		  break;
		default:
			if(qtd > USER_MAX){
				offset = 1025;
				return offset;
			}
			offset = verification(qtd,MAX_REAL,MAX_MEM);
			break;
	}

	if(offset!=MAX_MEM)
		for(int i=offset;i<qtd + offset;i++){
			memoir[i] = 1;
		}
	return offset;
}

// método de desatribui a memória a um processo
void Memory::deallocation(unsigned int offset,unsigned int qtd){
	int i = offset;
	while(i<qtd+offset) {
		memoir[i] = 0;
		i++;
	};
}

// método de verificação da posição de memória disponível para seu usada
unsigned int Memory::verification(unsigned int qtd, unsigned int start, unsigned int end){
	unsigned int offset = MAX_MEM;
	int j;

	for(int i = start; i < end; i++) {
		j = i;
		while (memoir[j] == 0 && j < qtd + i) j++;
		if (j == qtd + i){
			offset = i;
			break;
		}
		else i = j;
	}
	return offset;
}
