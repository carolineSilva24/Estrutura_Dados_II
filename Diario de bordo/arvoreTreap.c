// Caroline Andrade Silva - CC6M

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct treap {
    int chave, prioridade;
    struct treap *esq, *dir;
} NoTreap;

// Função para criar um novo nó da treap
NoTreap* novoNo(int chave) {
    NoTreap* temp = (NoTreap*)malloc(sizeof(NoTreap));
    temp->chave = chave;
    temp->prioridade = rand() % 100; // Gerando uma prioridade aleatória
    temp->esq = temp->dir = NULL;
    return temp;
}

// Rotação à direita
NoTreap* rotacaoDireita(NoTreap* noAtual) {
    NoTreap* novoNo = noAtual->esq;
    NoTreap* novaSubarvore = novoNo->dir;
    // Realiza a rotação
    novoNo->dir = noAtual;
    noAtual->esq = novaSubarvore;

    return novoNo;
}

// Rotação à esquerda
NoTreap* rotacaoEsquerda(NoTreap* novoNo) {
    NoTreap* noAtual = novoNo->dir;
    NoTreap* novaSubarvore = noAtual->esq;
    // Realiza a rotação
    noAtual->esq = novoNo;
    novoNo->dir= novaSubarvore;

    return noAtual;
}

// Função para inserir um novo nó com uma chave específica
NoTreap* inserir(NoTreap* raiz, int chave) {
    // Caso base
    if (!raiz)
       return novoNo(chave);
    // Se a chave for menor, insere na subárvore à esquerda
    if (chave < raiz->chave) {
       raiz->esq = inserir(raiz->esq, chave);
        // Faz a rotação se a prioridade do novo nó for maior que a raiz
        if (raiz->esq->prioridade > raiz->prioridade)
           raiz = rotacaoDireita(raiz);
    }
    // Se a chave for maior, insere na subárvore à direita
    else if (chave > raiz->chave) {
        raiz->dir = inserir(raiz->dir, chave);
        // Faz a rotação se a prioridade do novo nó for maior que a raiz
        if (raiz->dir->prioridade > raiz->prioridade)
            raiz = rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para remover um nó com uma chave específica
NoTreap* removerNo(NoTreap* raiz, int chave) {
    if (!raiz)
       return raiz;
    // Se a chave a ser removida for menor, está na subárvore à esquerda
    if (chave < raiz->chave)
       raiz->esq = removerNo(raiz->esq, chave);
    // Se a chave a ser removida for maior, está na subárvore à direita
    else if (chave > raiz->chave)
       raiz->dir = removerNo(raiz->dir, chave);
    // Se a chave for igual à da raiz, este é o nó a ser removido
    else {
       // Caso 1: Nó com um ou nenhum filho
       if (!raiz->esq) {
           NoTreap* temp = raiz->dir;
           free(raiz);
           raiz = temp;
       }
       else if (!raiz->dir) {
           NoTreap* temp = raiz->esq;
           free(raiz);
           raiz = temp;
       }
       // Caso 2: Nó com dois filhos
       else {
           // Rotaciona o nó com maior prioridade para manter a propriedade da treap
           if (raiz->esq->prioridade > raiz->dir->prioridade)
              raiz = rotacaoDireita(raiz);
           else
              raiz = rotacaoEsquerda(raiz);
            // Remove o nó agora na subárvore
            raiz = removerNo(raiz, chave);
       }
    }
    return raiz;
}

// Função auxiliar para armazenar nós em um array
void armazenarNos(NoTreap* raiz, NoTreap** nos, int* indice) {
    if (raiz) {
        nos[*indice] = raiz;
        (*indice)++;
        armazenarNos(raiz->esq, nos, indice);
        armazenarNos(raiz->dir, nos, indice);
    }
}

// Função de comparação para ordenar nós pela prioridade
int comparar(const void* a, const void* b) {
    NoTreap* noA = *(NoTreap**)a;
    NoTreap* noB = *(NoTreap**)b;
    return noB->prioridade - noA->prioridade; // Ordena em ordem decrescente de prioridade
}

// Função para imprimir os nós ordenados por prioridade
void imprimirNosPorPrioridade(NoTreap* raiz) {
    // Contando o número de nós
    int contagem = 0;
    NoTreap* nos[100]; // Considerando no máximo 100 nós
    armazenarNos(raiz, nos, &contagem);

    // Ordenando os nós pela prioridade
    qsort(nos, contagem, sizeof(NoTreap*), comparar);

    // Imprimindo nós ordenados
    printf("Nós ordenados por prioridade:\n");
    for (int i = 0; i < contagem; i++) {
        printf("chave: %d | prioridade: %d\n", nos[i]->chave, nos[i]->prioridade);
    }
}

// Função para fazer a ordenação em ordem da árvore
void emOrdem(NoTreap* raiz) {
    if (raiz) {
        emOrdem(raiz->esq);
        printf("chave: %d | prioridade: %d\n", raiz->chave, raiz->prioridade);
        emOrdem(raiz->dir);
    }
}

int main() {
    srand(time(0));
    // Valores da raiz para qual vai gerar prioridades aleatorias
    NoTreap* raiz = NULL;
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("\nNós de maior prioridade:\n");
    imprimirNosPorPrioridade(raiz);

    printf("\nOrdem vista da árvore da esquerda para a direita:\n");
    emOrdem(raiz);

    printf("\nRemovendo nós com chave 50 e 70:\n");
    raiz = removerNo(raiz, 50);
    raiz = removerNo(raiz, 70);

    printf("\nNós de maior prioridade após a remoção:\n");
    imprimirNosPorPrioridade(raiz);

    printf("\nOrdem vista da árvore da esquerda para a direita após a remoção:\n");
    emOrdem(raiz);

    return 0;
}
