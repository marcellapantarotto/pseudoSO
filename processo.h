#include <iostream>
#include <vector>

typedef std::vector<Processo> fila_t;

class Processo
{
  public:
    int id;           //identificador do processo
    double duracao;   //tempo de duração do processo
    int prioridade;   //prioridade do processo para escalonamento //são 4 níveis
}

// class Node
// {
//   public:
//     int num;      //conteudo do nó
//     Node *prox;   //potneiro para o próximo nó
// }

class Fila
{
  public:
    addProcesso();
    inicia();
    vazia();
    cheia();


  private:
    int tam;     //tamanho da fila
    Node *inicio; //ponteiro para o inicio da fila
    Node *final;  //ponteiro para o final da fila
}
