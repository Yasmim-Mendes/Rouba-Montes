#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura das cartas
typedef struct carta {
  int numero;
  char naipe;
} Carta;

// Estrutura de cada elemento das pilhas
typedef struct elementoPilha {
  Carta carta;
  struct elementoPilha *anterior;
} ElementoPilha;

// Estrutura da pilha
typedef struct pilha {
  ElementoPilha *topo;
} Pilha;

typedef struct {
  int id;
  char nome[50];
} Jogador;

// Estrutura de cada elemento da fila
typedef struct elementoFila {
  Jogador jogador;
  struct elementoFila *proximo;
} ElementoFila;

// Estrutura da fila
typedef struct fila {
  ElementoFila *inicio;
  ElementoFila *final;
} Fila;

//----------------------------------------------------

Fila* criaFila() {
  Fila* novaFila = (Fila*)malloc(sizeof(Fila));

  if (novaFila == NULL) {
    exit(EXIT_FAILURE);
  }

  novaFila->inicio = NULL;
  novaFila->final = NULL;

  return novaFila;
}

void liberaFila(Fila *fila) {
  if (fila == NULL) {
    return;
  }

  ElementoFila *atual = fila->inicio;
  ElementoFila *proximo;

  while (atual != NULL) {
    proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }

  free(fila);
}

int estaVazia(Fila *fila) {
  if (fila->inicio == NULL && fila->final == NULL) {
    return 1;
  }
  else {
    return 0;
  }
}

void enfileirar(Fila *fila, Jogador jogador) {
  ElementoFila* novoElemento = (ElementoFila*)malloc(sizeof(ElementoFila));

  if (novoElemento == NULL) {
    exit(EXIT_FAILURE);
  }

  novoElemento->jogador = jogador;
  novoElemento->proximo = NULL;

  if (estaVazia(fila)) {
    fila->inicio = novoElemento;
    fila->final = novoElemento;
  } 
  else {
    fila->final->proximo = novoElemento;
    fila->final = novoElemento;
  }
}

Jogador desenfileirar(Fila *fila) {
  Jogador jogadorDesenfileirado;

  if (estaVazia(fila) == 1) {
    exit(EXIT_FAILURE);
  }

  jogadorDesenfileirado = fila->inicio->jogador;

  ElementoFila *temporario = fila->inicio;
  fila->inicio = fila->inicio->proximo;

  free(temporario);

  if (fila->inicio == NULL) {
    fila->final = NULL;
  }

  return jogadorDesenfileirado;
}

Jogador avancarTurno(Fila *fila) {
  if (estaVazia(fila)) {
    Jogador jogadorVazio;
    jogadorVazio.id = -1;
    strcpy(jogadorVazio.nome, "Vazio");
    return jogadorVazio; 
  }

  Jogador jogadorAtual = desenfileirar(fila);
  enfileirar(fila, jogadorAtual);

  return jogadorAtual;
}

void imprimirFila(Fila *fila) {
  if (fila == NULL || estaVazia(fila)) {
    printf("A fila está vazia.\n");
    return;
  }

  ElementoFila *atual = fila->inicio;

  printf("Jogadores na fila:\n");

  while (atual != NULL) {
    printf("%s\n", atual->jogador.nome);
    atual = atual->proximo;
  }

  printf("\n");
}

int main() {
  Fila *minhaFila = criaFila();

  Jogador jogador1;
  strcpy(jogador1.nome, "yasmim");
  jogador1.id = 1;

  Jogador jogador2;
  strcpy(jogador2.nome, "davi");
  jogador2.id = 2;

  Jogador jogador3;
  strcpy(jogador3.nome, "rafa");
  jogador3.id = 3;

  Jogador jogador4;
  strcpy(jogador4.nome, "ana");
  jogador4.id = 4;

  enfileirar(minhaFila, jogador1);
  enfileirar(minhaFila, jogador2);
  enfileirar(minhaFila, jogador3);
  enfileirar(minhaFila, jogador4);

  imprimirFila(minhaFila);

  Jogador atual = avancarTurno(minhaFila);
  printf("Jogador atual: %s\n", atual.nome);
  atual = avancarTurno(minhaFila);
  printf("Jogador atual: %s\n", atual.nome);
  atual = avancarTurno(minhaFila);
  printf("Jogador atual: %s\n", atual.nome);
  atual = avancarTurno(minhaFila);
  printf("Jogador atual: %s\n", atual.nome);
  atual = avancarTurno(minhaFila);
  printf("Jogador atual: %s\n", atual.nome);
  atual = avancarTurno(minhaFila);
  printf("Jogador atual: %s\n", atual.nome);

  liberaFila(minhaFila);

  return 0;
}
