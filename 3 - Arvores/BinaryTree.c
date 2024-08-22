#include <stdio.h>
#include <stdlib.h>

struct NO {
  int info;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO *ArvBin;

ArvBin *cria_ArvBin() {
  ArvBin *raiz = (ArvBin *)malloc(sizeof(ArvBin));
  if (raiz != NULL) {
    *raiz = NULL;
  }
  return raiz;
}

int insert_ArvBin(ArvBin *raiz, int valor) {
  if (raiz == NULL) {
    return 0;
  }
  struct NO *novo;
  novo = (struct NO *)malloc(sizeof(struct NO));
  if (novo == NULL) {
    return 0;
  }
  novo->info = valor;
  novo->dir = NULL;
  novo->esq = NULL;

  if (*raiz == NULL) {
    *raiz = novo;
  } else {
    struct NO *atual = *raiz;
    struct NO *ant = NULL;
    while (atual != NULL) {
      ant = atual;
      if (valor == atual->info) {
        free(novo);
        return 0;
      }
      if (valor > atual->info) {
        atual = atual->dir;
      } else {
        atual = atual->esq;
      }
    }
    if (valor > ant->info) {
      ant->dir = novo;
    } else {
      ant->esq = novo;
    }
  }
  return 1;}

void preOrdem_arvBin(ArvBin *raiz){
  if(raiz==NULL){
      return;
  }
  if(*raiz!=NULL){
    printf("%d\t", (*raiz)->info);
    preOrdem_arvBin(&((*raiz)->esq));
    preOrdem_arvBin(&((*raiz)->dir));
  }
}

void emOrdem_arvBin(ArvBin *raiz){
  if(raiz==NULL){
      return;
  }
  if(*raiz!=NULL){
    emOrdem_arvBin(&((*raiz)->esq));
    printf("%d\t", (*raiz)->info);
    emOrdem_arvBin(&((*raiz)->dir));
  }
}

void posOrdem_arvBin(ArvBin *raiz){
  if(raiz==NULL){
      return;
  }
  if(*raiz!=NULL){
    posOrdem_arvBin(&((*raiz)->esq));
    posOrdem_arvBin(&((*raiz)->dir));
    printf("%d\t", (*raiz)->info);
  }
}

int procura_ArvBin(ArvBin *raiz, int valor){
  if(raiz==NULL){
      return 0;
  };
  struct NO *atual = *raiz;
  while(atual!=NULL){
    if(valor==atual->info){
      printf("Elemento encontrado!\n");
      return 1; 
    }
    if(valor>atual->info){
      atual=atual->dir;
    }
    if(valor<atual->info){
      atual=atual->esq;
    }
  }
  printf("Elemento não encontrado!\n");
  return 0; 
};

int remove_ArvBin(ArvBin *raiz, int valor){
  if(raiz==NULL){
      return 0;
  };
  struct NO *atual = *raiz;
  struct NO *ant=NULL;

  //busca do nó a ser removido
  while(atual!=NULL){
    if(valor==atual->info)
      break;
    ant=atual;
    if(valor>atual->info)
      atual=atual->dir;
    else
      atual=atual->esq;
  }
  // caso o valor não tenha sido encontrado na arvore
    if(atual==NULL)
      return 0;
  // caso o nó a ser removido seja uma folha
    if(atual->esq==NULL && atual->dir==NULL)
      if(ant==NULL)
        // como não tem filhos ele é a raiz ent é apagada
        *raiz=NULL;
      else
        // caso tenha filhos o ponteiro ant é desconectado como nó da arvore
        if(ant->esq==atual)
          ant->esq=NULL;
        else
          ant->dir=NULL;
  // caso tenha 2 filhos
    else
      if(atual->esq!=NULL && atual->dir!=NULL)
        if(ant==NULL)
  // a raiz é o nó a ser removido e será substituido pelo maior da esquerda
          *raiz=atual->esq;
  // O filho esquerdo de atual substitui atual na árvore.
        else
          if(ant->esq==atual)
            ant->esq=atual->esq;
          else
            ant->dir=atual->esq;
  // o nó tem apenas um filho
      else
  //se o anterior for nulo o nó a ser removido é a raiz, então a raiz é substituída pelo único filho de atual.
        if(ant==NULL)
          *raiz=atual->esq!=NULL?atual->esq:atual->dir;
  // O único filho de atual substitui atual na árvore.
        else
          if(ant->esq==atual)
            ant->esq=atual->esq!=NULL?atual->esq:atual->dir;
          else
            ant->dir=atual->esq!=NULL?atual->esq:atual->dir;
  // libera o nó atual
  free(atual);
  return 1;
}
int main(void) {
  ArvBin *raiz = cria_ArvBin();
  int N = 9, dados[9] = {50, 100, 30, 20, 40, 45, 35, 57, 52};
  for (int i = 0; i < N; i++) {
    insert_ArvBin(raiz, dados[i]);
    printf("Nó inserido: %d\n", dados[i]);
  }
  printf("\nPre-ordem: ");
  preOrdem_arvBin(raiz);
  printf("\nEmOrdem: ");
  emOrdem_arvBin(raiz);
  printf("\nPosOrdem: ");
  posOrdem_arvBin(raiz);

  printf("\nProcurando o elemento 20 na Arvore binaria: ");
  procura_ArvBin(raiz, 20);
  
  remove_ArvBin(raiz, 20);
  printf("\nPre-ordem após remoção do 20: ");
  preOrdem_arvBin(raiz);

  remove_ArvBin(raiz, 30);
  printf("\nPre-ordem após remoção do 30: ");
  preOrdem_arvBin(raiz);

  remove_ArvBin(raiz, 27);
  printf("\nPre-ordem após remoção do 27: ");
  preOrdem_arvBin(raiz);
  
  printf("\n\nProcurando o elemento 20 na Arvore binaria: ");
  procura_ArvBin(raiz, 20);
  return 0;
}
