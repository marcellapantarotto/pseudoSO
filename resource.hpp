#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <semaphore.h>
#include <pthread.h>

// enumeração: constantes do tipo inteiro
enum Resources{
  WITHOUT_RESOURCES = 0,
  WITH_RESOURCES, SCANNER, PRINTER, MODEM, SATA= 1
};

// semáforos globais do tipo sem_t
// extern permite que variáveis sejam linkadas em outros arquivos
extern sem_t scanner;
extern sem_t printer;
extern sem_t modem;
extern sem_t sata;

void InitializeSemaphores();
void freeResource(int resource);
int blockResource(int resource);

#endif //RESOURCE_HPP
