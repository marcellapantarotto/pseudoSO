#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <bitset>
#include "process.hpp"

#define MAX_MEM 1024
#define MAX_REAL 64
#define USER_MAX MAX_MEM, MAX_REAL
#define START 0

using namespace std;

class Memory {
	private:
		bitset<MAX_MEM> mem;
	public:
		Memory();
		void display();
		unsigned int allocation(unsigned int malloc,int type);
		void deallocation(unsigned int offset, unsigned int malloc);
		unsigned int verification(unsigned int malloc,unsigned int start, unsigned int end);
};

#endif //MEMORY_HPP
