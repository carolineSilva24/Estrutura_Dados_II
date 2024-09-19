// Árvore red black(rubro negra) - Caroline Andrade Silva - CC6M

#include <stdio.h>
#include <stdlib.h>

// Definição dos possíveis valores de cor
#define VERMELHO 1
#define PRETO 2

// Definição da estrutura de um nó da árvore Rubro-Negra
typedef struct NoArv {
  int numero;              // Valor armazenado no nó
  int cor;                 // Cor do nó (Vermelho ou Preto)
  struct NoArv *esq, *dir; // Ponteiros para os filhos esquerdo e direito
  struct NoArv *pai;       // Ponteiro para o nó pai
} NoArv;

// Função para criar um novo nó com valor fornecido
NoArv *criarNoArv(int numero) {
  NoArv *novoNo =
      (NoArv *)malloc(sizeof(NoArv)); // Aloca memória para um novo nó
  novoNo->numero = numero;            // Define o valor do nó
  novoNo->cor = VERMELHO;             // Todo novo nó começa como vermelho
  novoNo->esq = NULL;                 // Não tem filho esquerdo ainda
  novoNo->dir = NULL;                 // Não tem filho direito ainda
  novoNo->pai = NULL; // Não tem pai ainda (ainda será conectado)
  return novoNo;
}

// Função para fazer rotação à esquerda
void rotacaoEsquerda(NoArv **raiz, NoArv *x) {
  NoArv *y = x->dir;  // y é o filho direito de x
  x->dir = y->esq;    // O filho esquerdo de y se torna o filho direito de x
  if (y->esq != NULL) // Se o filho esquerdo de y existir, redefine o pai para x
    y->esq->pai = x;
  y->pai = x->pai;    // O pai de y se torna o pai de x
  if (x->pai == NULL) // Se x era a raiz, agora y se torna a raiz
    *raiz = y;
  else if (x == x->pai->esq) // Se x era o filho esquerdo
    x->pai->esq = y;
  else // Se x era o filho direito
    x->pai->dir = y;
  y->esq = x; // x se torna o filho esquerdo de y
  x->pai = y; // Atualiza o pai de x para y
}

// Função para fazer rotação à direita
void rotacaoDireita(NoArv **raiz, NoArv *x) {
  NoArv *y = x->esq;  // y é o filho esquerdo de x
  x->esq = y->dir;    // O filho direito de y se torna o filho esquerdo de x
  if (y->dir != NULL) // Se o filho direito de y existir, redefine o pai para x
    y->dir->pai = x;
  y->pai = x->pai;    // O pai de y se torna o pai de x
  if (x->pai == NULL) // Se x era a raiz, agora y se torna a raiz
    *raiz = y;
  else if (x == x->pai->dir) // Se x era o filho direito
    x->pai->dir = y;
  else // Se x era o filho esquerdo
    x->pai->esq = y;
  y->dir = x; // x se torna o filho direito de y
  x->pai = y; // Atualiza o pai de x para y
}

// Função para balancear a árvore após a inserção de um nó
void balancearArvore(NoArv **raiz, NoArv *z) {
  // Enquanto o pai de z for vermelho, precisamos corrigir a violação
  while (z != *raiz && z->pai->cor == VERMELHO) {
    // Se o pai de z for filho esquerdo do avô
    if (z->pai == z->pai->pai->esq) {
      NoArv *y = z->pai->pai->dir; // Tio de z
      // Caso 1: O tio de z também é vermelho
      if (y != NULL && y->cor == VERMELHO) {
        z->pai->cor = PRETO;         // Pai de z vira preto
        y->cor = PRETO;              // Tio de z vira preto
        z->pai->pai->cor = VERMELHO; // Avô vira vermelho
        z = z->pai->pai;             // Continua balanceando subindo na árvore
      } else {
        // Caso 2: z é o filho direito do pai
        if (z == z->pai->dir) {
          z = z->pai;
          rotacaoEsquerda(raiz, z); // Faz rotação à esquerda
        }
        // Caso 3: z é o filho esquerdo do pai
        z->pai->cor = PRETO;               // Pai vira preto
        z->pai->pai->cor = VERMELHO;       // Avô vira vermelho
        rotacaoDireita(raiz, z->pai->pai); // Faz rotação à direita
      }
    } else {
      // Se o pai de z for filho direito do avô (simétrico ao caso anterior)
      NoArv *y = z->pai->pai->esq;
      if (y != NULL && y->cor == VERMELHO) {
        z->pai->cor = PRETO;
        y->cor = PRETO;
        z->pai->pai->cor = VERMELHO;
        z = z->pai->pai;
      } else {
        if (z == z->pai->esq) {
          z = z->pai;
          rotacaoDireita(raiz, z); // Faz rotação à direita
        }
        z->pai->cor = PRETO;
        z->pai->pai->cor = VERMELHO;
        rotacaoEsquerda(raiz, z->pai->pai); // Faz rotação à esquerda
      }
    }
  }
  (*raiz)->cor = PRETO; // Garante que a raiz sempre será preta
}

// Função para inserir um novo nó na árvore Rubro-Negra
void inserirNo(NoArv **raiz, int numero) {
  NoArv *z = criarNoArv(numero); // Cria um novo nó com o valor
  NoArv *y = NULL;               // Ponteiro para armazenar o pai
  NoArv *x = *raiz;              // Começa na raiz da árvore

  // Busca o local correto para inserir o novo nó
  while (x != NULL) {
    y = x;
    if (z->numero < x->numero)
      x = x->esq; // Se o valor for menor, vai para a esquerda
    else
      x = x->dir; // Se for maior, vai para a direita
  }
  z->pai = y; // O pai do novo nó é y
  if (y == NULL)
    *raiz = z; // Se y for NULL, o novo nó se torna a raiz
  else if (z->numero < y->numero)
    y->esq = z; // Se o valor do nó for menor que o do pai, insere à esquerda
  else
    y->dir = z; // Se for maior, insere à direita

  balancearArvore(raiz, z); // Após a inserção, balanceia a árvore
}

// Função para imprimir a árvore Rubro-Negra em ordem
void emOrdem(NoArv *raiz) {
  if (raiz != NULL) {
    emOrdem(raiz->esq); // Percorre a subárvore esquerda
    if (raiz->cor == VERMELHO)
      printf("%d Vermelho", raiz->numero); // Imprime o valor e a cor do nó
    else
      printf("%d Preto", raiz->numero);
    emOrdem(raiz->dir); // Percorre a subárvore direita
  }
}

// Função para imprimir a árvore em formato visual, com níveis
void imprimeArvoreRN(NoArv *raiz, int b) {
  if (raiz != NULL) {
    // Chama a função recursivamente para a subárvore direita
    imprimeArvoreRN(raiz->dir, b + 1);

    // Imprime o nó com espaçamento proporcional ao nível
    for (int i = 0; i < b; i++)
      printf("     ");
    if (raiz->cor == VERMELHO)
      printf("\033[31m%d(V)\033[0m\n\n", raiz->numero); // Nó vermelho
    else
      printf("%d(B)\n\n", raiz->numero); // Nó preto

    // Chama a função recursivamente para a subárvore esquerda
    imprimeArvoreRN(raiz->esq, b + 1);
  }
}

int main() {
  struct NoArv *raiz = NULL; // Inicializa a raiz da árvore como NULL, pois a árvore está inicialmente vazia

  // Exemplo de inserção de números na árvore Rubro-Negra
  int vetor[] = {12, 31, 20, 14, 53, 17, 11, 8, 3, 24, 15, 33, 10, 1, 9};
  int i, tam = sizeof(vetor) / sizeof(vetor[0]); // Calcula o tamanho do vetor

  // Loop para inserir cada número do vetor na árvore Rubro-Negra
  for (i = 0; i < tam; i++)
    inserirNo(&raiz, vetor[i]); // Insere o número atual do vetor na árvore

  // Imprime a estrutura da árvore Rubro-Negra no formato visual
  printf("Árvore Rubro-Negra: \n");
  imprimeArvoreRN(raiz, 3); // Chama a função de impressão da árvore (começando com espaçamento base de 3)

  printf("\n");

  return 0;
}
