#include "memory.hpp"
#include <iostream>

Memory::Memory(){
		//Zera memoria
	int i=0;
	do {
		mem[i] = 0;
		i++;
	}while(i<MAX_MEM);

}
unsigned int Memory::allocation(unsigned int qtd, int tipo_p){
	unsigned int offset = MAX_MEM;
	switch(tipo_p){
		case REAL_TIME:
			if(qtd > MAX_REAL){
				offset = 1026; //Verificar
				return offset;
			}
			offset = verify(qtd,START,MAX_REAL); //Verifica quantidade de memoria ram e se ela está entre o inicio e o final.
		  break;
		default:
			if(qtd > USER_MAX){
				offset = 1026;
				return offset;
			}
			offset = verify(qtd,MAX_REAL,MAX_MEM);
			break;
	}

	if(offset!=MAX_MEM)
		for(int i=offset;i<qtd + offset;i++){
			mem[i] = 1;
		}
	return offset;
}

void Memory::deallocation(unsigned int offset,unsigned int qtd){
	int i=offset;
	do {
		mem[i] = 0;
		i++;
	} while(i<qtd+offset);
}

void Memory::display(){
	for(int i = 0; i < MAX_MEM; i++){
		cout << mem[i];
	}
	cout << endl;
}
unsigned int Memory::verify(unsigned int qtd, unsigned int start, unsigned int end){
	unsigned int offset = MAX_MEM;
	int j;

	for(int i=start; i<end; i++)	{
		j = i;

		while (mem[j] == 0 && j < qtd + i) j++;

		if (j == qtd + i){
			offset = i;
			break;
		}
		else i = j;
	}

	return offset;
}
