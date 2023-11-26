#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//estrutura das cartas
typedef struct carta {
  int numero;
  char naipe;
} Carta;

//estrutura de cada elemento das pilhas
typedef struct elemento {
  Carta carta;
  struct elemento *anterior;
} ElementoPilha;

//estrutura da pilha
typedef struct pilha {
  ElementoPilha *topo;
} Pilha;


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
int estaVazia(Pilha *pilha) {
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
  if (estaVazia(pilha) == 1) {
    exit(EXIT_FAILURE);
  }

  ElementoPilha *elementoRemovido = pilha->topo;
  pilha->topo = elementoRemovido->anterior;

  Carta cartaRemovida = elementoRemovido->carta;
  free(elementoRemovido);

  return cartaRemovida;
}

void imprimirPilha(Pilha *pilha) {
  if (pilha == NULL || estaVazia(pilha) == 1) {
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




int main() {
  Pilha *minhaPilha = criaPilha();

  srand(time(NULL));

  for (int i=0; i<3; i++){
    empilharRandom(minhaPilha);
  }

  imprimirPilha(minhaPilha);

  while (estaVazia(minhaPilha) != 1) {
    Carta valorRemovido = desempilhar(minhaPilha);
    printf("Valor desempilhado: %d de ", valorRemovido.numero);
    imprimeNaipe(&valorRemovido);
    printf("\n");
  }

  liberaPilha(minhaPilha);

  return 0;
}
