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

typedef struct elementoLista {
  Carta carta;
  struct elementoLista *proximo;
} ElementoLista;

typedef struct lista {
  ElementoLista *inicio;
} Lista;

//----------------------------------------------------

void imprimeNaipe (Carta *cartaDaVez){
  if (cartaDaVez->naipe == 'A'){
    printf ("paus\n");
  }
  else if (cartaDaVez->naipe == 'B'){
    printf ("copas\n");
  }
  else if (cartaDaVez->naipe == 'C'){
    printf ("espadas\n");
  }
  else if (cartaDaVez->naipe == 'D'){
    printf ("ouro\n");
  }
}

//----------------------------------------------------

//função que cria uma pilha
Pilha* criaPilha() {
  //aloca memória
  Pilha *novaPilha = (Pilha*)malloc(sizeof(Pilha));

  //inicializa o topo da pilha como NULL
  novaPilha->topo = NULL;

  return novaPilha;
}

//função que libera memória da pilha
void liberaPilha(Pilha *pilha) {
  //caso o ponteiro pilha não aponte para nenhum lugar na memória, encerra a função
  if (pilha == NULL) {
    return;
  }

  ElementoPilha *atual = pilha->topo;
  ElementoPilha *proximo;

  while (atual != NULL) {
    proximo = atual->anterior;
    free(atual);
    atual = proximo;
  }

  free(pilha);
}

//verifica se a pilha está vazia
int pilhaVazia(Pilha *pilha) {
  if (pilha->topo == NULL){
    return 1;
  }
  else {
    return 0;
  }
}

void empilhar(Pilha *pilha, Carta carta) {
  ElementoPilha *novoElemento = (ElementoPilha*)malloc(sizeof(ElementoPilha));

  novoElemento->carta = carta;
  novoElemento->anterior = pilha->topo;
  pilha->topo = novoElemento;
}

void empilharRandom (Pilha *pilha){
  ElementoPilha *novoElemento = (ElementoPilha *)malloc(sizeof(ElementoPilha));

  novoElemento->carta.numero = 1 + rand()%(13 - 1 + 1);
  novoElemento->carta.naipe = 'A' + rand() % 4;
  novoElemento->anterior = pilha->topo;
  pilha->topo = novoElemento;
}

Carta desempilhar(Pilha *pilha) {
  // Não há o que desempilhar
  if (pilhaVazia(pilha) == 1) {
    exit(EXIT_FAILURE);
  }

  ElementoPilha *elementoRemovido = pilha->topo;
  pilha->topo = elementoRemovido->anterior;

  Carta cartaRemovida = elementoRemovido->carta;
  free(elementoRemovido);

  return cartaRemovida;
}

void imprimirPilha(Pilha *pilha) {
  if (pilha == NULL || pilhaVazia(pilha) == 1) {
    return;
  }

  ElementoPilha *atual = pilha->topo;

  while (atual != NULL) {
    if (atual->carta.numero == 1) {
      printf("Ás de ");
      imprimeNaipe(&atual->carta);
    }
    else if (atual->carta.numero == 11){
      printf ("Valete de ");
      imprimeNaipe(&atual->carta);
    }
    else if (atual->carta.numero == 12){
      printf ("Dama de ");
      imprimeNaipe(&atual->carta);
    }
    else if (atual->carta.numero == 13){
      printf ("Rei de ");
      imprimeNaipe(&atual->carta);
    }
    else {
      printf("%d de ", atual->carta.numero);
      imprimeNaipe(&atual->carta);
    }

    atual = atual->anterior;
  }

  printf("\n");
}




//-----------------------------------------------------




Fila* criaFila() {
  Fila *novaFila = (Fila*)malloc(sizeof(Fila));

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

int filaVazia(Fila *fila) {
  if (fila->inicio == NULL && fila->final == NULL) {
    return 1;
  }
  else {
    return 0;
  }
}

void enfileirar(Fila *fila, Jogador jogador) {
  ElementoFila *novoElemento = (ElementoFila*)malloc(sizeof(ElementoFila));

  if (novoElemento == NULL) {
    exit(EXIT_FAILURE);
  }

  novoElemento->jogador = jogador;
  novoElemento->proximo = NULL;

  if (filaVazia(fila)) {
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

  if (filaVazia(fila) == 1) {
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
  if (filaVazia(fila)) {
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
  if (fila == NULL || filaVazia(fila)) {
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




//---------------------------------------------------




Lista* criarLista() {
  Lista *novaLista = (Lista*)malloc(sizeof(Lista));

  if (novaLista == NULL) {
    exit(EXIT_FAILURE); 
  }

  novaLista->inicio = NULL;
  return novaLista;
}

void limparLista(Lista *lista) {
  if (lista == NULL) {
    return;
  }

  ElementoLista *atual = lista->inicio;
  ElementoLista *proximo;

  while (atual != NULL) {
    proximo = atual->proximo;
    free(atual);
    atual = proximo;
  }

  lista->inicio = NULL;
}

int listaVazia(Lista *lista) {
  if (lista == NULL || lista->inicio == NULL){
    return 1;
  }
  else {
    return 0;
  }
}

void inserirItem(Lista *lista, Carta carta) {
    ElementoLista *novoElemento = (ElementoLista*)malloc(sizeof(ElementoLista));

  if (novoElemento == NULL) {
    exit(EXIT_FAILURE); 
  }

  novoElemento->carta = carta;
  novoElemento->proximo = NULL;

  if (lista->inicio == NULL) {
    lista->inicio = novoElemento;
  } 
  else {
    ElementoLista *atual = lista->inicio;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }
    atual->proximo = novoElemento;
  }
}

ElementoLista* removerItem(Lista *lista, int posicao) {
  if (listaVazia(lista) == 1) {
    return NULL;
  }

  ElementoLista *elementoRemovido;

  if (posicao == 0) {
    elementoRemovido = lista->inicio;
    lista->inicio = lista->inicio->proximo;
  } 
  else {
    ElementoLista *anterior = NULL;
    ElementoLista *atual = lista->inicio;
    int i = 0;

    while (i < posicao && atual != NULL) {
      anterior = atual;
      atual = atual->proximo;
      i++;
    }

    if (atual != NULL) {
      elementoRemovido = atual;
      anterior->proximo = atual->proximo;
    } 
    else {
      return NULL;
    }
  }

  elementoRemovido->proximo = NULL;

  return elementoRemovido;
}

int buscarItem(Lista *lista, int chave) {
  if (listaVazia(lista) == 1) {
    return -1;
  }

  ElementoLista *atual = lista->inicio;
  int posicao = 0;

  while (atual != NULL) {
    if (atual->carta.numero == chave) {
      return posicao;
    }
    atual = atual->proximo;
    posicao++;
  }

  return -1;
}

void imprimirLista(Lista *lista) {
  if (listaVazia(lista) == 1) {
    return;
  }

  ElementoLista *atual = lista->inicio;

  while (atual != NULL) {
    printf("%d ", atual->carta.numero);
    imprimeNaipe(&atual->carta);
    atual = atual->proximo;
  }
  printf("\n");
}




//------------------------------------------------------




