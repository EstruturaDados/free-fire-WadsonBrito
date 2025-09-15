#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// Estrutura que representa cada item da mochila
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

int main() {
    Item mochila[MAX_ITENS]; // Vetor estático de itens
    int total = 0;           // Quantidade de itens cadastrados
    int opcao;

    do {
        printf("\n=== MOCHILA VIRTUAL - DESAFIO FREE FIRE ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o \n do buffer

        switch (opcao) {
            case 1:
                if (total < MAX_ITENS) {
                    printf("Digite o nome do item: ");
                    fgets(mochila[total].nome, MAX_NOME, stdin);
                    mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0'; // Remove \n

                    printf("Digite o tipo do item: ");
                    fgets(mochila[total].tipo, MAX_TIPO, stdin);
                    mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                    printf("Digite a quantidade: ");
                    scanf("%d", &mochila[total].quantidade);
                    getchar();

                    total++;
                    printf("✅ Item adicionado com sucesso!\n");
                } else {
                    printf("⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
                }
                break;

            case 2: {
                char nomeRemover[MAX_NOME];
                int encontrado = 0;

                if (total == 0) {
                    printf("⚠️ Mochila vazia. Nenhum item para remover.\n");
                    break;
                }

                printf("Digite o nome do item que deseja remover: ");
                fgets(nomeRemover, MAX_NOME, stdin);
                nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

                for (int i = 0; i < total; i++) {
                    if (strcmp(mochila[i].nome, nomeRemover) == 0) {
                        for (int j = i; j < total - 1; j++) {
                            mochila[j] = mochila[j + 1]; // Desloca os itens
                        }
                        total--;
                        encontrado = 1;
                        printf("🗑️ Item removido com sucesso!\n");
                        break;
                    }
                }

                if (!encontrado) {
                    printf("❌ Item nao encontrado.\n");
                }
                break;
            }

            case 3:
                if (total == 0) {
                    printf("⚠️ Mochila vazia. Nenhum item cadastrado.\n");
                } else {
                    printf("\n📋 Itens na mochila:\n");
                    printf("-----------------------------------------\n");
                    printf("%-20s %-15s %-5s\n", "Nome", "Tipo", "Qtd");
                    printf("-----------------------------------------\n");
                    for (int i = 0; i < total; i++) {
                        printf("%-20s %-15s %-5d\n",
                               mochila[i].nome,
                               mochila[i].tipo,
                               mochila[i].quantidade);
                    }
                    printf("-----------------------------------------\n");
                }
                break;

            case 0:
                printf("👋 Saindo do programa. Boa sorte na ilha!\n");
                break;

            default:
                printf("⚠️ Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
