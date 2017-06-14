#include "resource.hpp"

// semáforos do tipo sem_t
sem_t scanner;
sem_t printer;
sem_t modem;
sem_t sata;

// função que inicializa os semáforos
void InitializeSemaphores()
{
	// sem_init() inicializa o semáforo
	// primeiro argumento determina se o semáforo é compartilhado ou não:
	// 			0 = compartilhado entre threas de um processo; !0 = compartilhado entre pocessos
	// segundo argumento indica o valor do semáforo
	sem_init(&scanner, 0, 1);
	sem_init(&printer, 0, 2);
	sem_init(&modem, 0, 1);
	sem_init(&sata, 0, 2);
	return;
}

// função para bloquear recursos
int blockResource(int resource)
{
	int blo = 0;
	switch(resource)
	{
		// sem_trywait() bloqueia um semáforo se ele já não estiver bloqueado
		// tem que ser positivo
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

// função para liberar recursos
void freeResource(int resource)
{
	switch(resource)
	{
		//sem_post() libera o semáforo
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
