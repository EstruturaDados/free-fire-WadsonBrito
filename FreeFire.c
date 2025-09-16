#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 30

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n=== MENU Free Fire ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch(opcao) {
            case 1:
                if (total < MAX_ITENS) {
                    printf("Nome: ");
                    fgets(mochila[total].nome, MAX_NOME, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                    printf("Tipo: ");
                    fgets(mochila[total].tipo, MAX_TIPO, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Quantidade: ");
                    scanf("%d", &mochila[total].quantidade);

                    total++;
                    printf("Item adicionado!\n");
                } else {
                    printf("Mochila cheia!\n");
                }
                break;

            case 2: {
                char nomeBusca[MAX_NOME];
                printf("Digite o nome do item para remover: ");
                fgets(nomeBusca, MAX_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                int i, j, encontrado = 0;
                for (i = 0; i < total; i++) {
                    if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                        for (j = i; j < total - 1; j++) {
                            mochila[j] = mochila[j+1];
                        }
                        total--;
                        encontrado = 1;
                        printf("Item removido!\n");
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Item não encontrado.\n");
                }
                break;
            }

            case 3:
                if (total == 0) {
                    printf("Mochila vazia.\n");
                } else {
                    printf("\n--- Itens da Mochila ---\n");
                    printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    }
                }
                break;

            case 4: {
                char nomeBusca[MAX_NOME];
                printf("Digite o nome do item para buscar: ");
                fgets(nomeBusca, MAX_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                int encontrado = 0;
                for (int i = 0; i < total; i++) {
                    if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                        printf("\nItem encontrado!\n");
                        printf("Nome: %s\n", mochila[i].nome);
                        printf("Tipo: %s\n", mochila[i].tipo);
                        printf("Quantidade: %d\n", mochila[i].quantidade);
                        encontrado = 1;
                        break;
                    }
                }
                if (!encontrado) {
                    printf("Item não encontrado na mochila.\n");
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}
