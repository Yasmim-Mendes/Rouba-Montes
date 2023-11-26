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
  if (lista == NULL || lista->inicio == NULL) {
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
  if (lista == NULL || lista->inicio == NULL) {
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

int listaVazia(Lista *lista) {
  if (lista == NULL || lista->inicio == NULL){
    return 1;
  }
  else {
    return 0;
  }
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

int main() {
    Lista *minhaLista = criarLista();


    Carta carta1;
    carta1.numero = 1;
    carta1.naipe = 'A';

    Carta carta2;
    carta2.numero = 2;
    carta2.naipe = 'B';

  Carta carta3;
  carta3.numero = 3;
  carta3.naipe = 'C';
  
    inserirItem(minhaLista, carta1);
    inserirItem(minhaLista, carta2);
    inserirItem(minhaLista, carta3);

    imprimirLista(minhaLista);

    ElementoLista *elementoEncontrado = removerItem(minhaLista, buscarItem(minhaLista, 2));

    if (elementoEncontrado != NULL) {
        printf("Elemento encontrado: %d\n", elementoEncontrado->carta.numero);
      imprimeNaipe(&elementoEncontrado->carta);
    } else {
        printf("Elemento não encontrado.\n");
    }

    limparLista(minhaLista);

    return 0;
}