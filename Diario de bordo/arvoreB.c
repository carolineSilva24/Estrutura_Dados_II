#include <stdio.h>
#include <stdlib.h>

typedef struct NoArvoreB {
    int *chaves;
    int numChaves;
    struct NoArvoreB **filhos;
    int ordem;
    int ehFolha;
} NoArvoreB;

// Função para inicializar um novo nó da árvore B
NoArvoreB* inicializarArvoreB(int ordem) {
    NoArvoreB *no = (NoArvoreB*)malloc(sizeof(NoArvoreB));
    no->ordem = ordem;
    no->numChaves = 0;
    no->ehFolha = 1; // Inicialmente, é uma folha
    no->chaves = (int*)malloc((2 * ordem - 1) * sizeof(int));
    no->filhos = (NoArvoreB**)malloc(2 * ordem * sizeof(NoArvoreB*));
    return no;
}

// Função para percorrer a árvore B em ordem
void percorrer(NoArvoreB *no) {
    int i;
    for (i = 0; i < no->numChaves; i++) {
        if (!no->ehFolha) {
            percorrer(no->filhos[i]);
        }
        printf("%d ", no->chaves[i]);
    }
    if (!no->ehFolha) {
        percorrer(no->filhos[i]);
    }
}

// Função para dividir um nó
void dividirNo(NoArvoreB *no, int idx, NoArvoreB *filho) {
    NoArvoreB *filhoNovo = inicializarArvoreB(filho->ordem);
    filhoNovo->ehFolha = filho->ehFolha;
    filhoNovo->numChaves = no->ordem - 1;

    for (int i = 0; i < no->ordem - 1; i++) {
        filhoNovo->chaves[i] = filho->chaves[i + no->ordem];
    }

    if (!filho->ehFolha) {
        for (int i = 0; i < no->ordem; i++) {
            filhoNovo->filhos[i] = filho->filhos[i + no->ordem];
        }
    }

    filho->numChaves = no->ordem - 1;

    for (int i = no->numChaves; i >= idx + 1; i--) {
        no->filhos[i + 1] = no->filhos[i];
    }

    no->filhos[idx + 1] = filhoNovo;

    for (int i = no->numChaves - 1; i >= idx; i--) {
        no->chaves[i + 1] = no->chaves[i];
    }

    no->chaves[idx] = filho->chaves[no->ordem - 1];
    no->numChaves++;
}

// Função para inserir uma chave na árvore B
void inserir(NoArvoreB **raiz, int chave) {
    NoArvoreB *no = *raiz;

    if (no->numChaves == (2 * no->ordem - 1)) {
        NoArvoreB *noNovo = inicializarArvoreB(no->ordem);
        *raiz = noNovo;
        noNovo->ehFolha = 0;
        noNovo->filhos[0] = no;
        dividirNo(noNovo, 0, no);
        inserir(&noNovo, chave);
    } else {
        int idx = no->numChaves - 1;

        if (no->ehFolha) {
            while (idx >= 0 && no->chaves[idx] > chave) {
                no->chaves[idx + 1] = no->chaves[idx];
                idx--;
            }
            no->chaves[idx + 1] = chave;
            no->numChaves++;
        } else {
            while (idx >= 0 && no->chaves[idx] > chave) {
                idx--;
            }
            idx++;
            if (no->filhos[idx]->numChaves == (2 * no->ordem - 1)) {
                dividirNo(no, idx, no->filhos[idx]);
                if (no->chaves[idx] < chave) {
                    idx++;
                }
            }
            inserir(&no->filhos[idx], chave);
        }
    }
}

// Função auxiliar para encontrar o predecessor
int encontrarPredecessor(NoArvoreB *no) {
    while (!no->ehFolha) {
        no = no->filhos[no->numChaves];
    }
    return no->chaves[no->numChaves - 1];
}

// Função auxiliar para encontrar o sucessor
int encontrarSucessor(NoArvoreB *no) {
    while (!no->ehFolha) {
        no = no->filhos[0];
    }
    return no->chaves[0];
}

// Função auxiliar para garantir que um nó tenha o número mínimo de chaves
void garantirMinimo(NoArvoreB *no, int idx) {
    if (idx != 0 && no->filhos[idx - 1]->numChaves >= no->ordem) {
        // Pegar da esquerda
        NoArvoreB *filho = no->filhos[idx];
        NoArvoreB *filhoEsquerdo = no->filhos[idx - 1];

        for (int i = filho->numChaves - 1; i >= 0; i--) {
            filho->chaves[i + 1] = filho->chaves[i];
        }

        if (!filho->ehFolha) {
            for (int i = filho->numChaves; i >= 0; i--) {
                filho->filhos[i + 1] = filho->filhos[i];
            }
            filho->filhos[0] = filhoEsquerdo->filhos[filhoEsquerdo->numChaves];
        }

        filho->chaves[0] = no->chaves[idx - 1];
        no->chaves[idx - 1] = filhoEsquerdo->chaves[filhoEsquerdo->numChaves - 1];
        filho->numChaves++;
        filhoEsquerdo->numChaves--;
    } else if (idx != no->numChaves && no->filhos[idx + 1]->numChaves >= no->ordem) {
        // Pegar da direita
        NoArvoreB *filho = no->filhos[idx];
        NoArvoreB *filhoDireito = no->filhos[idx + 1];

        filho->chaves[filho->numChaves] = no->chaves[idx];
        if (!filho->ehFolha) {
            filho->filhos[filho->numChaves + 1] = filhoDireito->filhos[0];
        }

        no->chaves[idx] = filhoDireito->chaves[0];
        for (int i = 1; i < filhoDireito->numChaves; i++) {
            filhoDireito->chaves[i - 1] = filhoDireito->chaves[i];
        }

        if (!filhoDireito->ehFolha) {
            for (int i = 1; i <= filhoDireito->numChaves; i++) {
                filhoDireito->filhos[i - 1] = filhoDireito->filhos[i];
            }
        }

        filho->numChaves++;
        filhoDireito->numChaves--;
    } else {
        // Mescla
        if (idx != no->numChaves) {
            NoArvoreB *filho = no->filhos[idx];
            NoArvoreB *filhoDireito = no->filhos[idx + 1];

            filho->chaves[filho->numChaves] = no->chaves[idx];
            for (int i = 0; i < filhoDireito->numChaves; i++) {
                filho->chaves[i + filho->numChaves + 1] = filhoDireito->chaves[i];
            }
            if (!filho->ehFolha) {
                for (int i = 0; i <= filhoDireito->numChaves; i++) {
                    filho->filhos[i + filho->numChaves + 1] = filhoDireito->filhos[i];
                }
            }

            filho->numChaves += filhoDireito->numChaves + 1;

            for (int i = idx + 1; i < no->numChaves; i++) {
                no->chaves[i - 1] = no->chaves[i];
            }

            for (int i = idx + 2; i <= no->numChaves; i++) {
                no->filhos[i - 1] = no->filhos[i];
            }

            no->numChaves--;
            free(filhoDireito->chaves);
            free(filhoDireito->filhos);
            free(filhoDireito);
        } else {
            NoArvoreB *filho = no->filhos[idx - 1];
            NoArvoreB *filhoDireito = no->filhos[idx];

            filho->chaves[filho->numChaves] = no->chaves[idx - 1];
            for (int i = 0; i < filhoDireito->numChaves; i++) {
                filho->chaves[i + filho->numChaves + 1] = filhoDireito->chaves[i];
            }
            if (!filho->ehFolha) {
                for (int i = 0; i <= filhoDireito->numChaves; i++) {
                    filho->filhos[i + filho->numChaves + 1] = filhoDireito->filhos[i];
                }
            }

            no->numChaves--;

            for (int i = idx - 1; i < no->numChaves; i++) {
                no->chaves[i] = no->chaves[i + 1];
            }

            for (int i = idx; i <= no->numChaves; i++) {
                no->filhos[i] = no->filhos[i + 1];
            }

            filho->numChaves += filhoDireito->numChaves + 1;
            free(filhoDireito->chaves);
            free(filhoDireito->filhos);
            free(filhoDireito);
        }
    }
}

// Função para remover uma chave da árvore B
void remover(NoArvoreB *no, int chave) {
    int idx = 0;
    while (idx < no->numChaves && no->chaves[idx] < chave) {
        idx++;
    }

    if (idx < no->numChaves && no->chaves[idx] == chave) {
        if (no->ehFolha) {
            for (int i = idx + 1; i < no->numChaves; i++) {
                no->chaves[i - 1] = no->chaves[i];
            }
            no->numChaves--;
        } else {
            // Remover da árvore interna
            int chaveAtual = no->chaves[idx];

            if (no->filhos[idx]->numChaves >= no->ordem) {
                int predecessor = encontrarPredecessor(no->filhos[idx]);
                no->chaves[idx] = predecessor;
                remover(no->filhos[idx], predecessor);
            } else if (no->filhos[idx + 1]->numChaves >= no->ordem) {
                int sucessor = encontrarSucessor(no->filhos[idx + 1]);
                no->chaves[idx] = sucessor;
                remover(no->filhos[idx + 1], sucessor);
            } else {
                // Mescla
                NoArvoreB *filho = no->filhos[idx];
                NoArvoreB *filhoDireito = no->filhos[idx + 1];

                filho->chaves[filho->numChaves] = chaveAtual;
                for (int i = 0; i < filhoDireito->numChaves; i++) {
                    filho->chaves[i + filho->numChaves + 1] = filhoDireito->chaves[i];
                }
                if (!filho->ehFolha) {
                    for (int i = 0; i <= filhoDireito->numChaves; i++) {
                        filho->filhos[i + filho->numChaves + 1] = filhoDireito->filhos[i];
                    }
                }

                filho->numChaves += filhoDireito->numChaves + 1;
                for (int i = idx + 1; i < no->numChaves; i++) {
                    no->chaves[i - 1] = no->chaves[i];
                }
                for (int i = idx + 2; i <= no->numChaves; i++) {
                    no->filhos[i - 1] = no->filhos[i];
                }
                no->numChaves--;
                free(filhoDireito->chaves);
                free(filhoDireito->filhos);
                free(filhoDireito);
                remover(filho, chave);
            }
        }
    } else {
        // Se não for uma folha, continue a busca
        if (!no->ehFolha) {
            if (idx == no->numChaves) {
                idx--; // O último filho
            }

            garantirMinimo(no, idx);

            if (idx < no->numChaves) {
                remover(no->filhos[idx], chave);
            } else {
                remover(no->filhos[idx - 1], chave);
            }
        } else {
            printf("A chave %d não está presente na árvore.\n", chave);
            
        }
    }
}

// Função principal
int main() {
    int ordem, chave, op;
    NoArvoreB *raiz = NULL;

    printf("Digite a ordem da árvore B: ");
    scanf("%d", &ordem);
    raiz = inicializarArvoreB(ordem);

    do {
        printf("\nMenu:\n");
        printf("1. Inserir chave\n");
        printf("2. Remover chave\n");
        printf("3. Percorrer árvore (in-ordem)\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("Digite a chave para inserir: ");
                scanf("%d", &chave);
                inserir(&raiz, chave);
                break;
            case 2:
                printf("Digite a chave para remover: ");
                scanf("%d", &chave);
                remover(raiz, chave);
                break;
            case 3:
                printf("Árvore B em ordem: ");
                percorrer(raiz);
                printf("\n");
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (op != 4);

    return 0;
}
