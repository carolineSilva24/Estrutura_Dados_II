#include <stdio.h>
#include <stdlib.h>
// Caroline Andrade Silva - CC6M 

// Struct para armazenar os dados do no
struct NO {
  int info;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO *ArvBin;
// cria a arvore binaria
ArvBin *cria_ArvBin() {
  ArvBin *raiz = (ArvBin *)malloc(sizeof(ArvBin));
  if (raiz != NULL) {
    *raiz = NULL;
  }
  return raiz;
}

int insert_ArvBin(ArvBin *raiz, int valor) {
  // verifica se a arvore esta vazia
  if (raiz == NULL) {
    return 0;
  }
  struct NO *novo;
  // cria um novo no e aloca a memoria com o tamanho do no
  novo = (struct NO *)malloc(sizeof(struct NO));
  if (novo == NULL) {
    return 0;
  }
  novo->info = valor;
  novo->dir = NULL;
  novo->esq = NULL;
// se não tiver um no raiz o novo valor vai ser o no raiz
  if (*raiz == NULL) {
    *raiz = novo;
  } else {
    struct NO *atual = *raiz;
    struct NO *ant = NULL;
    // enquanto o valor do atual for diferente de nulo o atual vai ser o anterior 
    while (atual != NULL) {
      ant = atual;
      // se o valor for igual ao atual o valor não vai ser inserido
      if (valor == atual->info) {
        free(novo);
        return 0;
      }
      // se o valor for maior que o atual, o atual vai ser o direito
      if (valor > atual->info) {
        atual = atual->dir;
        // se o valor for menor que o atual, o atual vai ser o esquerdo
      } else {
        atual = atual->esq;
      }
    }
    // se o valor for maior que o anterior, o novo vai ser o direito
    if (valor > ant->info) {
      ant->dir = novo;
    // se o valor for menor que o anterior, o novo vai ser o esquerdo
    } else {
      ant->esq = novo;
    }
  }
  return 1;}

void preOrdem_arvBin(ArvBin *raiz){
  // verifica se a árvore ta vazia
  if(raiz==NULL){
      return;
  }
  // ordena a arvore em pre ordem
  if(*raiz!=NULL){
    printf("%d\t", (*raiz)->info);
    preOrdem_arvBin(&((*raiz)->esq));
    preOrdem_arvBin(&((*raiz)->dir));
  }
}

int procura_ArvBin(ArvBin *raiz, int valor){
  // verifica se a arvore está vazia
  if(raiz==NULL){
      return 0;
  };
  struct NO *atual = *raiz;
  // percorre a arvore ate achar o valor procurado
  while(atual!=NULL){
    // verifica se o valor foi encontrado
    if(valor==atual->info){
      printf("Elemento encontrado!\n");
      return 1; 
    }
    // verifica se o valor é menor ou maior que o atual
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
  //verifica se a arvore está vazia
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
  // nos a serem inseridos na árvore binaria
  int N = 9, dados[9] = {50, 100, 30, 20, 40, 45, 35, 57, 52};
  // inserção dos elementos da arvore até o ultimo valor
  for (int i = 0; i < N; i++) {
    insert_ArvBin(raiz, dados[i]);
    printf("Nó inserido: %d\n", dados[i]);
  }
  printf("\nPre-ordem: ");
  preOrdem_arvBin(raiz);
  
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
