#include "processo.h"

Fila::Fila():
{ }

void Fila::inicia() {
  inicio = 0;
  fim = inicio;
}

bool Fila::vazia(){
  return(inicio == 0);
}

bool Fila::cheia(){

}
