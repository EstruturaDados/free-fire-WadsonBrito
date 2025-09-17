
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];   // ex: "chip central"
    char tipo[MAX_TIPO];   // ex: "controle", "suporte", "propulsao"
    int prioridade;        // 1 a 10
} Componente;

/* ---------- UTILITÁRIOS DE STRING ---------- */

// remove o \n deixado pelo fgets
void strip_newline(char *s) {
    size_t l = strlen(s);
    if (l == 0) return;
    if (s[l-1] == '\n') s[l-1] = '\0';
}

// compara duas strings ignorando maiúsculas/minúsculas
int strcmp_icase(const char *a, const char *b) {
    while (*a && *b) {
        char ca = tolower((unsigned char)*a);
        char cb = tolower((unsigned char)*b);
        if (ca != cb) return (ca < cb) ? -1 : 1;
        a++; b++;
    }
    if (*a) return 1;
    if (*b) return -1;
    return 0;
}

/* ---------- FUNÇÕES DE EXIBIÇÃO ---------- */

// mostra o vetor de componentes formatado
void mostrarComponentes(Componente comps[], int n) {
    printf("\nÍndice | %-29s | %-19s | Prioridade\n", "Nome", "Tipo");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%6d | %-29s | %-19s | %9d\n", i, comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
    printf("----------------------------------------------------------------------\n");
}

/* ---------- ALGORITMOS DE ORDENAÇÃO (cada um em sua função) ---------- */

// Bubble sort por nome (string). Conta comparações em *comparacoes.
void bubbleSortNome(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int trocou = 0;
        for (int j = 0; j < n-1-i; j++) {
            (*comparacoes)++; // comparação de strings
            if (strcmp_icase(arr[j].nome, arr[j+1].nome) > 0) {
                Componente tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
}

// Insertion sort por tipo (string). Conta comparações em *comparacoes.
void insertionSortTipo(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = arr[i];
        int j = i - 1;
        // comparamos key.tipo com arr[j].tipo
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp_icase(arr[j].tipo, key.tipo) > 0) {
                arr[j+1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j+1] = key;
    }
}

// Selection sort por prioridade (int). Conta comparações em *comparacoes.
void selectionSortPrioridade(Componente arr[], int n, long *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            (*comparacoes)++; // comparação de inteiros
            if (arr[j].prioridade < arr[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Componente tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

/* ---------- BUSCA BINÁRIA (aplicável após ordenação por nome) ---------- */

// Busca binária por nome. Retorna índice ou -1. Conta comparações em *comparacoes.
int buscaBinariaPorNome(Componente arr[], int n, const char chave[], long *comparacoes) {
    int low = 0, high = n - 1;
    *comparacoes = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*comparacoes)++; // comparação de string com o meio
        int cmp = strcmp_icase(arr[mid].nome, chave);
        if (cmp == 0) return mid;
        else if (cmp < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

/* ---------- MEDIÇÃO DE TEMPO (medirTempo) ---------- */

// medirTempo recebe um ponteiro para função de ordenação com assinatura
// void func(Componente[], int, long*) e executa medições de tempo e devolve tempo em segundos.
// Faz a cópia do array para não alterar o original se necessário.

double medirTempo(void (*algoritmo)(Componente[], int, long*), Componente arr[], int n, long *comparacoes) {
    // Fazemos uma cópia para preservar arr original (útil se quisermos comparar depois)
    Componente copia[MAX_COMPONENTES];
    for (int i = 0; i < n; i++) copia[i] = arr[i];

    clock_t inicio = clock();
    algoritmo(copia, n, comparacoes);
    clock_t fim = clock();
    double elapsed = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return elapsed;
}

/* ---------- LEITURA E CADASTRO ---------- */

// cadastra componentes (até MAX_COMPONENTES)
int cadastrarComponentes(Componente comps[]) {
    int n = 0;
    char buffer[128];
    printf("Quantos componentes deseja cadastrar? (1 a %d): ", MAX_COMPONENTES);
    if (!fgets(buffer, sizeof(buffer), stdin)) return 0;
    int q = atoi(buffer);
    if (q < 1) q = 1;
    if (q > MAX_COMPONENTES) q = MAX_COMPONENTES;

    for (int i = 0; i < q; i++) {
        printf("\nComponente %d/%d\n", i+1, q);
        printf("Nome: ");
        if (!fgets(comps[i].nome, sizeof(comps[i].nome), stdin)) comps[i].nome[0] = '\0';
        strip_newline(comps[i].nome);
        if (strlen(comps[i].nome) == 0) sprintf(comps[i].nome, "Componente_%d", i+1);

        printf("Tipo: ");
        if (!fgets(comps[i].tipo, sizeof(comps[i].tipo), stdin)) comps[i].tipo[0] = '\0';
        strip_newline(comps[i].tipo);
        if (strlen(comps[i].tipo) == 0) sprintf(comps[i].tipo, "tipo_desconhecido");

        int pri = 0;
        while (1) {
            printf("Prioridade (1 a 10): ");
            if (!fgets(buffer, sizeof(buffer), stdin)) break;
            pri = atoi(buffer);
            if (pri >= 1 && pri <= 10) break;
            printf("Entrada inválida. Tente novamente.\n");
        }
        comps[i].prioridade = pri;
        n++;
    }
    return n;
}

/* ---------- FUNÇÃO AUXILIAR: COPIAR VETOR ---------- */
void copiaVetor(Componente dest[], Componente src[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

/* ---------- FUNÇÃO PRINCIPAL / MENU ---------- */
int main(void) {
    Componente comps[MAX_COMPONENTES];
    int n = 0;
    int ordenado_por_nome = 0;

    printf("=== Torre de Resgate: Módulo de Priorização e Montagem (Nível Mestre) ===\n");

    // cadastrar inicialmente
    n = cadastrarComponentes(comps);
    if (n == 0) {
        printf("Nenhum componente cadastrado. Encerrando.\n");
        return 0;
    }

    int opcao = 0;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1) Mostrar componentes atuais\n");
        printf("2) Ordenar por NOME (Bubble Sort)\n");
        printf("3) Ordenar por TIPO (Insertion Sort)\n");
        printf("4) Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5) Busca binária por NOME (apenas após ordenar por nome)\n");
        printf("6) Re-cadastrar componentes (sobrescrever)\n");
        printf("0) Sair\n");
        printf("Escolha uma opção: ");

        char buf[32];
        if (!fgets(buf, sizeof(buf), stdin)) break;
        opcao = atoi(buf);

        if (opcao == 0) {
            printf("Saindo... boa sorte na fuga!\n");
            break;
        }

        if (opcao == 1) {
            mostrarComponentes(comps, n);
        } else if (opcao == 2) {
            // Ordenar por nome com bubble sort
            long comparacoes = 0;
            double tempo = medirTempo(bubbleSortNome, comps, n, &comparacoes);
            // executar de fato para modificar o vetor atual
            bubbleSortNome(comps, n, &comparacoes);
            ordenado_por_nome = 1;
            printf("\nResultado da ordenação por NOME (Bubble Sort):\n");
            mostrarComponentes(comps, n);
            printf("Comparações: %ld | Tempo gasto: %.6f s\n", comparacoes, tempo);
        } else if (opcao == 3) {
            long comparacoes = 0;
            double tempo = medirTempo(insertionSortTipo, comps, n, &comparacoes);
            insertionSortTipo(comps, n, &comparacoes);
            ordenado_por_nome = 0;
            printf("\nResultado da ordenação por TIPO (Insertion Sort):\n");
            mostrarComponentes(comps, n);
            printf("Comparações: %ld | Tempo gasto: %.6f s\n", comparacoes, tempo);
        } else if (opcao == 4) {
            long comparacoes = 0;
            double tempo = medirTempo(selectionSortPrioridade, comps, n, &comparacoes);
            selectionSortPrioridade(comps, n, &comparacoes);
            ordenado_por_nome = 0;
            printf("\nResultado da ordenação por PRIORIDADE (Selection Sort):\n");
            mostrarComponentes(comps, n);
            printf("Comparações: %ld | Tempo gasto: %.6f s\n", comparacoes, tempo);
        } else if (opcao == 5) {
            if (!ordenado_por_nome) {
                printf("Atenção: a busca binária por NOME só funciona corretamente após ordenar o vetor por NOME (opção 2).\n");
                continue;
            }
            char chave[MAX_NOME];
            printf("Digite o nome do componente-chave a buscar: ");
            if (!fgets(chave, sizeof(chave), stdin)) chave[0] = '\0';
            strip_newline(chave);
            long comparacoes = 0;
            clock_t inicio = clock();
            int idx = buscaBinariaPorNome(comps, n, chave, &comparacoes);
            clock_t fim = clock();
            double tempo = (double)(fim - inicio)/CLOCKS_PER_SEC;
            if (idx >= 0) {
                printf("Componente encontrado no índice %d:\n", idx);
                printf("Nome: %s | Tipo: %s | Prioridade: %d\n", comps[idx].nome, comps[idx].tipo, comps[idx].prioridade);
            } else {
                printf("Componente '%s' NÃO encontrado.\n", chave);
            }
            printf("Comparações na busca binária: %ld | Tempo: %.6f s\n", comparacoes, tempo);
        } else if (opcao == 6) {
            printf("Reiniciando cadastro...\n");
            n = cadastrarComponentes(comps);
            ordenado_por_nome = 0;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
