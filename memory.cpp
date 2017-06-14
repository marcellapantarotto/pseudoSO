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
unsigned int Memory::allocation(unsigned int malloc, int type){
	unsigned int offset = MAX_MEM;
	switch(type){
		case REAL_TIME:
			if(malloc > MAX_REAL){
				offset = 1026; //Verificar
				return offset;
			}
			offset = verification(malloc,START,MAX_REAL); //Verifica quantidade de memoria ram e se ela está entre o inicio e o final.
		  break;
		default:
			if(malloc > USER_MAX){
				offset = 1026;
				return offset;
			}
			offset = verification(malloc,MAX_REAL,MAX_MEM);
			break;
	}

	if(offset!=MAX_MEM)
		for(int i=offset;i<malloc + offset;i++){
			mem[i] = 1;
		}
	return offset;
}

void Memory::deallocation(unsigned int offset,unsigned int malloc){
	int i=offset;
	do {
		mem[i] = 0;
		i++;
	} while(i<malloc+offset);
}

void Memory::display(){
	for(int i = 0; i < MAX_MEM; i++){
		cout << mem[i];
	}
	cout << endl;
}
unsigned int Memory::verification(unsigned int malloc, unsigned int start, unsigned int end){
	unsigned int offset = MAX_MEM;
	int j;

	for(int i=start; i<end; i++)	{
		j = i;

		while (mem[j] == 0 && j < malloc + i) j++;

		if (j == malloc + i){
			offset = i;
			break;
		}
		else i = j;
	}

	return offset;
}
