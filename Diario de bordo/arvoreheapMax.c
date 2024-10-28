#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dados; // Array para armazenar os elementos do heap
    int tamanho; // Tamanho atual do heap
    int capacidade; // Capacidade máxima do heap
} Heap;

// Função para criar um heap
Heap* criarHeap(int capacidade) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->dados = (int*)malloc(capacidade * sizeof(int));
    return heap;
}

// Função para trocar dois elementos no heap
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para "subir" o nó (heapify up) após a inserção
void subir(Heap* heap, int indice) {
    while (indice > 0 && heap->dados[indice] > heap->dados[(indice - 1) / 2]) {
        trocar(&heap->dados[indice], &heap->dados[(indice - 1) / 2]);
        indice = (indice - 1) / 2;
    }
}

// Função para inserir um elemento no heap
void inserir(Heap* heap, int valor) {
    if (heap->tamanho == heap->capacidade) {
        printf("Heap cheio! Não é possível inserir %d\n", valor);
        return;
    }
    heap->dados[heap->tamanho] = valor;
    heap->tamanho++;
    subir(heap, heap->tamanho - 1);
}

// Função para "descer" o nó (heapify down) após a remoção
void descer(Heap* heap, int indice) {
    int maior = indice;
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;

    if (esquerda < heap->tamanho && heap->dados[esquerda] > heap->dados[maior]) {
        maior = esquerda;
    }

    if (direita < heap->tamanho && heap->dados[direita] > heap->dados[maior]) {
        maior = direita;
    }

    if (maior != indice) {
        trocar(&heap->dados[indice], &heap->dados[maior]);
        descer(heap, maior);
    }
}

// Função para remover o elemento máximo (raiz) do heap
int remover(Heap* heap) {
    if (heap->tamanho == 0) {
        printf("Heap vazio! Não é possível remover\n");
        return -1; // Retorna -1 se o heap estiver vazio
    }
    int raiz = heap->dados[0];
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;
    descer(heap, 0);
    return raiz;
}

// Função para exibir os elementos do heap
void exibirHeap(Heap* heap) {
    for (int i = 0; i < heap->tamanho; i++) {
        printf("%d ", heap->dados[i]);
    }
    printf("\n");
}

// Função principal
int main() {
    int capacidade;
    printf("Digite a capacidade do heap: ");
    scanf("%d", &capacidade);

    Heap* heap = criarHeap(capacidade);
    int opcao;

    do {
        printf("Escolha uma opção:\n");
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Exibir heap\n");
        printf("4. Sair\n");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int valor;
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            inserir(heap, valor);
        } else if (opcao == 2) {
            int valorRemovido = remover(heap);
            if (valorRemovido != -1) {
                printf("Valor removido: %d\n", valorRemovido);
            }
        } else if (opcao == 3) {
            printf("Elementos do heap: ");
            exibirHeap(heap);
        } else if (opcao != 4) {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);

    // Libera a memória do heap
    free(heap->dados);
    free(heap);
    printf("Saindo...\n");
    return 0;
}
