#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 30

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade;
} Item;

typedef enum { NOME = 1, TIPO, PRIORIDADE } Criterio;

void insertionSort(Item v[], int n, Criterio c, int *comparacoes) {
    for (int i = 1; i < n; i++) {
        Item chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            int cmp = 0;
            if (c == NOME) cmp = strcmp(chave.nome, v[j].nome);
            else if (c == TIPO) cmp = strcmp(chave.tipo, v[j].tipo);
            else if (c == PRIORIDADE) cmp = chave.prioridade - v[j].prioridade;

            if (cmp < 0) {
                v[j+1] = v[j];
                j--;
            } else break;
        }
        v[j+1] = chave;
    }
}

int buscaBinaria(Item v[], int n, char nome[]) {
    int ini = 0, fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nome, v[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else ini = meio + 1;
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("===================================\n");
        printf("=== FREE FIRE ===\n");
        printf("=== MOCHILA DO SOBREVIVENTE ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar mochila\n");
        printf("5. Buscar item (binária)\n");
        printf("0. Sair\n");
        printf("===================================\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            if (qtd < MAX_ITENS) {
                printf("Nome: ");
                fgets(mochila[qtd].nome, MAX_NOME, stdin);
                mochila[qtd].nome[strcspn(mochila[qtd].nome, "\n")] = 0;

                printf("Tipo: ");
                fgets(mochila[qtd].tipo, MAX_TIPO, stdin);
                mochila[qtd].tipo[strcspn(mochila[qtd].tipo, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &mochila[qtd].quantidade);
                getchar();

                printf("Prioridade (1 a 5): ");
                scanf("%d", &mochila[qtd].prioridade);
                getchar();

                qtd++;
                ordenadoPorNome = false;
                printf("Item adicionado!\n");
            } else {
                printf("Mochila cheia!\n");
            }
        } else if (opcao == 2) {
            char nome[MAX_NOME];
            printf("Nome do item a remover: ");
            fgets(nome, MAX_NOME, stdin);
            nome[strcspn(nome, "\n")] = 0;

            int encontrado = 0;
            for (int i = 0; i < qtd; i++) {
                if (strcmp(mochila[i].nome, nome) == 0) {
                    for (int j = i; j < qtd - 1; j++) {
                        mochila[j] = mochila[j + 1];
                    }
                    qtd--;
                    encontrado = 1;
                    ordenadoPorNome = false;
                    printf("Item removido!\n");
                    break;
                }
            }
            if (!encontrado) {
                printf("Item não encontrado!\n");
            }
        } else if (opcao == 3) {
            printf("\n--- ITENS DA MOCHILA ---\n");
            for (int i = 0; i < qtd; i++) {
                printf("%d. %s | %s | Qtd: %d | Prioridade: %d\n", 
                       i+1, mochila[i].nome, mochila[i].tipo, 
                       mochila[i].quantidade, mochila[i].prioridade);
            }
        } else if (opcao == 4) {
            printf("Ordenar por (1-Nome, 2-Tipo, 3-Prioridade): ");
            int criterio;
            scanf("%d", &criterio);
            getchar();

            int comparacoes = 0;
            insertionSort(mochila, qtd, criterio, &comparacoes);

            if (criterio == NOME) ordenadoPorNome = true;
            else ordenadoPorNome = false;

            printf("Itens ordenados! Comparações realizadas: %d\n", comparacoes);
        } else if (opcao == 5) {
            if (!ordenadoPorNome) {
                printf("A mochila deve estar ordenada por NOME antes da busca binária!\n");
            } else {
                char nome[MAX_NOME];
                printf("Nome do item a buscar: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = 0;

                int idx = buscaBinaria(mochila, qtd, nome);
                if (idx >= 0) {
                    printf("Item encontrado: %s | %s | Qtd: %d | Prioridade: %d\n",
                           mochila[idx].nome, mochila[idx].tipo, 
                           mochila[idx].quantidade, mochila[idx].prioridade);
                } else {
                    printf("Item não encontrado!\n");
                }
            }
        }

    } while (opcao != 0);

    return 0;
}
