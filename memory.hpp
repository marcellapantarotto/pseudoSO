#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <bitset>
#include "process.hpp"

#define MAX_MEM 1024
#define MAX_REAL 64
#define USER_MAX MAX_MEM-MAX_REAL
#define START 0

using namespace std;

class Memory {
	public:
		Memory();
		void display();
		unsigned int allocation(unsigned int qtd,int tipo_p);
		void deallocation(unsigned int offset, unsigned int qtd);
		unsigned int verification(unsigned int qtd,unsigned int start, unsigned int end);

	private:
		bitset<MAX_MEM> memoir;	// armazena bits: 0 ou 1
};

#endif //MEMORY_HPP
