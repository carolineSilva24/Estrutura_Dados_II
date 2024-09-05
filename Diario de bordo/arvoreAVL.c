// Arvore AVL - Caroline Andrade Silva

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore AVL
struct NoArvoreAVL
{
    int dado;
    struct NoArvoreAVL *esq;
    struct NoArvoreAVL *dir;
    int altura;
};

// Função para criar um novo nó na árvore
// Recebe um valor inteiro como parâmetro e retorna um ponteiro para o novo nó
struct NoArvoreAVL *criarNo(int dado){
    // Aloca memória para um novo nó da árvore AVL
    struct NoArvoreAVL *novoNo = (struct NoArvoreAVL *)malloc(sizeof(struct NoArvoreAVL));
    // Verifica se a alocação de memória foi bem-sucedida
    if (novoNo == NULL){
        // Imprime uma mensagem de erro e encerra o programa caso a alocação falhe
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        exit(-1);
    }
    novoNo->dado = dado;     // Armazena o valor fornecido dentro do nó
    novoNo->esq = NULL;      // Inicializa o ponteiro para o filho esquerdo como nulo
    novoNo->dir = NULL;      // Inicializa o ponteiro para o filho direito como nulo
    novoNo->altura = 0;      // Inicializa a altura do nó como 0
    return novoNo;           // Retorna o ponteiro para o novo nó criado
}

// Função para calcular a altura de um nó
int alturaNo(struct NoArvoreAVL *no){
    // Verifica se o nó é nulo
    if (no == NULL)
        // Retorna -1 se o nó for nulo
        return -1;
    // Retorna a altura do nó
    return no->altura;
}

 // Função para calcular o fator de balanceamento de um nó
  int fatorBalanceamento(struct NoArvoreAVL *no){
 // Verifica se o nó é nulo
     if(no == NULL){
       return 0;
     }
    // Calcula a altura do filho esquerdo do nó
    int alturaEsq = alturaNo(no->esq);
    // Calcula a altura do filho direito do nó
    int alturaDir = alturaNo(no->dir);
    // Retorna a diferença entre as alturas dos filhos
    return alturaEsq - alturaDir;
  }

 struct NoArvoreAVL *rotacaoDireita(struct NoArvoreAVL *no){
    struct NoArvoreAVL *novaRaiz = no->esq;   // Define a nova raiz como o nó à esq
    struct NoArvoreAVL *subArvore = novaRaiz->dir; // Define a subárvore como a subárvore dir da nova raiz

   // ocorre a rotação
    novaRaiz->dir = no; // o no é o filho direito da nova raiz
    no->esq = subArvore; // a subárvore dir da nova raiz é o filho esquerdo do novo nó

   // atualiza as alturas dos nós
    if(alturaNo(no->esq) > alturaNo(no->dir)){ // verifica se a altura da subarvore esq é maior
        no->altura = alturaNo(no->esq) + 1;
    }else{
        no->altura = alturaNo(no->dir) + 1;
    }

   if(alturaNo(novaRaiz->esq) > alturaNo(novaRaiz->dir)){ // verifica se a altura da subarvore esq da nova raiz é maior
     novaRaiz->altura = alturaNo(novaRaiz->esq) + 1;
   }else{
     novaRaiz->altura = alturaNo(novaRaiz->dir) + 1;
   }
   return novaRaiz;
    
 }

struct NoArvoreAVL *rotacaoEsquerda(struct NoArvoreAVL *no){
    struct NoArvoreAVL *novaRaiz = no->dir;
    struct NoArvoreAVL *subArvore = novaRaiz->esq;

   //ocorre a rotação
    novaRaiz->esq = no; // o no é o filho esquerdo da nova raiz
    no->dir = subArvore; // a subárvore esq da nova raiz é o filho direito do nó

   //atualiza as alturas dos nós
    if(alturaNo(no->esq) > alturaNo(no->dir)){ // verifica se a altura da subarvore esq é maior
        no->altura = alturaNo(no->esq) + 1;
    }else{
        no->altura = alturaNo(no->dir) + 1;
    }

   if(alturaNo(novaRaiz->esq) > alturaNo(novaRaiz->dir)){ // verifica se a altura da subarvore esq da nova raiz é maior
     novaRaiz->altura = alturaNo(novaRaiz->esq) + 1;
   }else{
     novaRaiz->altura = alturaNo(novaRaiz->dir) + 1;
   }
   return novaRaiz;

 }

 struct NoArvoreAVL *balanceamento(struct NoArvoreAVL *raiz, int dado)
 {
     // Atualiza a altura do nó atual
   // Se a raiz for nula, retorna a raiz
     if(raiz == NULL){
         return raiz;
     }
     if(alturaNo(raiz->esq) > alturaNo(raiz->dir)) // Verifica a altura da subárvore esq
        raiz->altura = 1 + alturaNo(raiz->esq); 
     else
        raiz->altura = 1 + alturaNo(raiz->dir); 

     // Calcula o fator de balanceamento deste nó para verificar se ele se tornou desbalanceado
     int balanceamento = fatorBalanceamento(raiz); 
   
     // Caso de desbalanceamento à esq-esq(rotação simples a direita)
     if (balanceamento >= 2 && dado < raiz->esq->dado) // Se o fator de balanceamento for maior ou igual a 2 e o dado for menor que o dado da subárvore esquerda
       return rotacaoDireita(raiz);              // Realiza rotação à dir

     // Caso de desbalanceamento à dir-dir(rotação simples a esquerda)
     if (balanceamento <= -2 && dado > raiz->dir->dado) // Se o fator de balanceamento for menor ou igual a -2 e o dado for maior que o dado da subárvore dir
       return rotacaoEsquerda(raiz);           // Realiza rotação à esq

     // Caso de desbalanceamento à esq-dir(rotação dupla a direita)
     if (balanceamento >= 2 && dado > raiz->esq->dado){ // Se o fator de balanceamento for maior ou igual a 2 e o dado for maior que o dado da subárvore esquerda
       raiz->esq = rotacaoEsquerda(raiz->esq); // Realiza rotação à esq na subárvore esq da raiz
       return rotacaoDireita(raiz);            // Realiza rotação à dir na raiz
     }

     // Caso de desbalanceamento à dir-esq
   if (balanceamento <= -2 && dado < raiz->dir->dado){ // Se o fator de balanceamento for menor ou igual a -2 e o dado for menor que o dado da subárvore dir
       raiz->dir = rotacaoDireita(raiz->dir);  // Realiza rotação à dir na subárvore dir da raiz
       return rotacaoEsquerda(raiz);           // Realiza rotação à esq na raiz
    }
     // Retorna a raiz inalterada após o balanceamento
     return raiz; 
 }

// função para inserir um novo nó na árvore AVL
struct NoArvoreAVL *inserir(struct NoArvoreAVL *raiz, int dado){
    // Se a raiz for nula, cria um novo nó e retorna
    if (raiz == NULL)
      return criarNo(dado);
    // Se o dado for menor que o dado da raiz, insere na subárvore esquerda
    if (dado < raiz->dado)
      raiz->esq = inserir(raiz->esq, dado);
    // Se o dado for maior que o dado da raiz, insere na subárvore direita
    else if(dado > raiz->dado)
      raiz->dir = inserir(raiz->dir, dado);
    // Se o dado for igual ao dado da raiz, não faz nada
    else
      return raiz;
    // Faça o balanceamento da árvore após a inserção
    return balanceamento(raiz, dado);
}

struct NoArvoreAVL *encontrarMinimo(struct NoArvoreAVL *no){
  struct NoArvoreAVL *atual = no;

  // Enquanto o nó atual não for nulo, vá para o nó mais à esquerda
  while(atual && atual->esq != NULL)
    atual = atual->esq;
// Retorna o nó mais à esquerda
  return atual;
}

struct NoArvoreAVL* encontrarMaximo(struct NoArvoreAVL* no) {
    // Verifica se o nó fornecido é válido
    if (no == NULL)
        return NULL;
    // Enquanto o nó não for nulo, vá para o nó mais à direita da subarvore esquerda
    while (no->dir != NULL) {
        no = no->dir;
    }
    // Retorna o nó mais à direita da subárvore esquerda
    return no;
}

// Função para remover um nó da árvore AVL
struct NoArvoreAVL *removerNo(struct NoArvoreAVL *raiz, int valor) {
  if (raiz == NULL) // Verifica se o nó a ser excluído existe ou é nulo
    return raiz;
  
  if (valor < raiz->dado){ // Verifica se o dado está à esquerda
    raiz->esq = removerNo(raiz->esq, valor); // Chama a função recursivamente até encontrar o nó a ser excluído
  }
  else if (valor > raiz->dado) // Verifica se o dado está à direita
  {
    raiz->dir = removerNo(raiz->dir, valor); // Chama a função recursivamente até encontrar o nó a ser excluído
  }
  else{ // Se o nó atual for igual ao valor a ser excluído
     // Caso 1: Nó folha ou nó com apenas um filho
    if (raiz->esq == NULL){ // Se tiver apenas filhos à direita
      struct NoArvoreAVL *temp = raiz->dir; // O filho a direita vai substituir o nó
        free(raiz);                         // Libera o valor do nó da memória
        return temp;                        // Retorna o nó que irá substituir o nó pai
    }
    else if (raiz->dir == NULL){ // Se tiver apenas filhos à esquerda
      struct NoArvoreAVL *temp = raiz->esq; // O filho a esquerda vai substituir o nó
        free(raiz);                         // Libera o valor do nó da memória
        return temp;                        // Retorna o nó que irá substituir o nó pai
    }

    // Caso 2: Nó com dois filhos
    // Verifica o balanceamento antes de decidir entre o valor maior à direita da subárvore esquerda ou o menor valor à esquerda da subárvore direita
    if (alturaNo(raiz->esq) >= alturaNo(raiz->dir)) {
    // Se a altura da subárvore esquerda for maior, escolhe o maior valor à direita da subárvore esquerda
      struct NoArvoreAVL *temp = encontrarMaximo(raiz->esq); // Encontra o maior valor na subárvore esquerda
       raiz->dado = temp->dado;             // Copia o valor do sucessor in-order (maior valor na subárvore esquerda) para a raiz atual
       raiz->esq = removerNo(raiz->esq, temp->dado); // Remove o nó com o valor copiado da subárvore esquerda
    } else {
    // Caso contrário, escolhe o menor valor à esquerda da subárvore direita
      struct NoArvoreAVL *temp = encontrarMinimo(raiz->dir); // Encontra o menor valor na subárvore direita
        raiz->dado = temp->dado;            // Copia o valor do sucessor in-order (menor valor na subárvore direita) para a raiz atual
        raiz->dir = removerNo(raiz->dir, temp->dado);   // Remove o nó com o valor copiado da subárvore direita
      }
  }
  // Após a exclusão, chama a função de balanceamento para garantir que a árvore permaneça balanceada
  return balanceamento(raiz, valor);
}

// Função para imprimir a árvore AVL em ordem
void imprimirEmOrdem(struct NoArvoreAVL *raiz){
  if (raiz != NULL){
    imprimirEmOrdem(raiz->esq);
    printf(" %d ", raiz->dado);
    imprimirEmOrdem(raiz->dir);
  }
}

// Função para imprimir a árvore AVL em pré-ordem
void imprimirPreOrdem(struct NoArvoreAVL *raiz){
  if (raiz != NULL){
    printf(" %d ", raiz->dado);
    imprimirPreOrdem(raiz->esq);
    imprimirPreOrdem(raiz->dir);
  }
}

// Função para imprimir a árvore AVL em pós-ordem
void imprimirPosOrdem(struct NoArvoreAVL *raiz){
  if (raiz != NULL){
    imprimirPosOrdem(raiz->esq);
    imprimirPosOrdem(raiz->dir);
    printf(" %d ", raiz->dado);
  }
}

void imprimeNo(int c, int b)
{
    int i;
    for (i = 0; i < b; i++) // Loop para imprimir espaços proporcionais à profundidade
        printf("   ");
    printf("%i\n", c); // Imprime o valor do nó com a devida indentação
}

void mostraArvore(struct NoArvoreAVL *a, int b){
  if (a != NULL){ // Verifica se o nó atual não é nulo
        // Chama a função recursivamente para percorrer a subárvore direita
        mostraArvore(a->dir, b + 1);
        // Imprime o nó atual com um espaçamento proporcional à sua profundidade
        imprimeNo(a->dado, b);
        // Chama a função recursivamente para percorrer a subárvore esquerda
        mostraArvore(a->esq, b + 1);
  }
}

// Função para calcular a altura de uma árvore AVL
int alturaTree(struct NoArvoreAVL *no){
   if (no == NULL) // Se o nó for nulo, a altura é -1
        return -1;

   // Calcula a altura da subárvore esquerda e direita
   int altura_esquerda = alturaTree(no->esq) + 1;
   int altura_direita = alturaTree(no->dir) + 1;

   // Retorna a maior altura entre a subárvore esquerda e direita, somada à altura do nó atual
   if (1 + ((altura_esquerda > altura_direita)))
     return altura_esquerda;
   else
     return altura_direita;
}

// função para buscar um no na arvore
struct NoArvoreAVL *buscarNo(struct NoArvoreAVL *raiz, int valor)
{
    if (raiz == NULL || raiz->dado == valor)
        return raiz;

    if (valor < raiz->dado)
        return buscarNo(raiz->esq, valor);
    else
        return buscarNo(raiz->dir, valor);
}

int main(){
    struct NoArvoreAVL *raiz = NULL;

   //Inserindo elementos na árvore AVL
      raiz = inserir(raiz, 30);
      raiz = inserir(raiz, 24);
      raiz = inserir(raiz, 20);
      raiz = inserir(raiz, 35);
      raiz = inserir(raiz, 27);
      raiz = inserir(raiz, 33);
      raiz = inserir(raiz, 38);
      raiz = inserir(raiz, 25);
      raiz = inserir(raiz, 22);
      raiz = inserir(raiz, 34);
      raiz = inserir(raiz, 40);
      raiz = inserir(raiz, 29);
      mostraArvore(raiz, 1);

      printf("\nArvore em ordem: ");
      imprimirEmOrdem(raiz);

      printf("\nInsere 31\n");
      raiz = inserir(raiz, 31);
      mostraArvore(raiz, 3);

      printf("\nInsere 15\n");
      raiz = inserir(raiz, 15);
      mostraArvore(raiz, 3);

      printf("\nInsere 23 \n");
      raiz = inserir(raiz, 23);
      mostraArvore(raiz, 3);

      printf("\nExclui 24\n");
      raiz = removerNo(raiz, 24);
      mostraArvore(raiz, 3);

      printf("\nExclui 35\n");
      raiz = removerNo(raiz, 35);
      mostraArvore(raiz, 3);

      printf("\nInsere 9\n");
      raiz = inserir(raiz, 9);
      mostraArvore(raiz, 3);

      printf("\nInserir 24\n");
      raiz = inserir(raiz, 24);
      mostraArvore(raiz, 3);

      printf("\nExclui 27\n");
      raiz = removerNo(raiz, 27);
      mostraArvore(raiz, 3);

      printf("\nInserir 10\n");
      raiz = inserir(raiz, 10);
      mostraArvore(raiz, 3);

      printf("\nExclui 21\n");
      raiz = removerNo(raiz, 21);
      mostraArvore(raiz, 3);
  
      return 0;
  }
