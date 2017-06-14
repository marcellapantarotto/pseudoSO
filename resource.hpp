#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <semaphore.h>
#include <pthread.h>

enum Resources{
  WITHOUT_RESOURCES = 0,
  WITH_RESOURCES, SCANNER, PRINTER, MODEM, SATA= 1
};

// global semaphores type sem_t
// extern makes variables linkeble to other fles
extern sem_t scanner;
extern sem_t printer;
extern sem_t modem;
extern sem_t sata;

void InitializeSemaphores();
void freeResource(int resource);
int blockResource(int resource);

#endif //RESOURCE_HPP
