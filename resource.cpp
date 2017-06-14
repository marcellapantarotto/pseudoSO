#include "resource.hpp"

// semaphores type sem_t
sem_t scanner;
sem_t printer;
sem_t modem;
sem_t sata;

// function to initialize semaphores
void InitializeSemaphores()
{
	// sem_init() initializes a semaphores
	// first argument indicates if the semaphore is shared:
	// 0 = shared between threads of a process; !0 = shared between processes
	// second argument indicates the value of the semaphore
	sem_init(&scanner, 0, 1);
	sem_init(&printer, 0, 2);
	sem_init(&modem, 0, 1);
	sem_init(&sata, 0, 2);
	return;
}

int blockResource(int resource)
{
	int blo = 0;
	switch(resource)
	{
		// sem_trywait() locks the semaphore if it is not already locked
		// sem must be positve
		case SCANNER:
			if(sem_trywait(&scanner) == 0)
				blo = 1;
			break;
		case PRINTER:
			if(sem_trywait(&printer) == 0)
				blo = 1;
			break;
		case MODEM:
			if(sem_trywait(&modem) == 0)
				blo = 1;
			break;
		case SATA:
			if(sem_trywait(&sata) == 0)
				blo = 1;
			break;
		default:
			break;
	}
	return blo;
}

void freeResource(int resource)
{
	switch(resource)
	{
		//sem_post() liberates the semaphore
		case PRINTER:
			sem_post(&printer);
			break;
		case SCANNER:
			sem_post(&scanner);
			break;
		case MODEM:
			sem_post(&modem);
			break;
		case SATA:
			sem_post(&sata);
			break;
		default:
			break;
	}
}
