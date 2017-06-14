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

// método que mostra mapa de bits
void Memory::display(){
	for(int i = 0; i < MAX_MEM; i++){
		cout << memoir[i];
	}
	cout << endl;
}

// método de alocação de memória
// retorna o offset da memória e determina qual tipo de processo está sendo usado
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

// método que usa o offset para desalocar a memória
void Memory::deallocation(unsigned int offset,unsigned int qtd){
	int i = offset;
	while(i<qtd+offset) {
		memoir[i] = 0;
		i++;
	};
}

// método que verifica se existe uma quantidade memória contígua disponível
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
