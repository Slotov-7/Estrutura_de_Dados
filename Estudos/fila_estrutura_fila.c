// Created by Guilherme Araújo on 06/02/2025.
//
// FIFO, First in, First out
#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    int valor;
    struct no *prox;
}No;
typedef struct {
    No *inicio;
    No *final;
    int tam;
}Fila;
void criar_fila(Fila *fila) {
    fila->final = NULL;
    fila->inicio = NULL;
    fila->tam = 0;
}

void inserir(Fila *fila, int num) {
    No *novo = malloc(sizeof(No));

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        // Atribui o valor 'num' ao novo nó
        novo->valor = num;
        // Define o próximo do novo nó como NULL (pois ele será o último)
        novo->prox = NULL;
        // Verifica se a lista está vazia
        if (fila->inicio == NULL) {
            // Se estiver vazia, o novo nó é o primeiro (e único) elemento
            fila->inicio = novo;
            fila->final = novo;
        } else {
            fila->final->prox = novo;
            fila->final =novo;
        }
        fila->tam++;
    } else {
        printf("Erro de alocação de memória\n");
    }
}
No* remover(Fila *fila) {
    No *remover = NULL;
    if (fila->inicio) {
        remover = fila->inicio; // Armazena o nó a ser removido.
        fila->inicio = remover->prox; // Atualiza o início da fila para o próximo nó.
        fila->tam--;
    }else {
        printf("A fila esta vazia");
    }
    return remover;
}
void imprimir (Fila *fila) {
    No *aux = fila->inicio;
    printf("FILA: ");
    while (aux) {
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
}

int main() {
    Fila fila;
    int opcao, valor;
    No *removido;
    criar_fila(&fila);

    do {
        printf("\n--------------------------------------\n");;
        printf("[1] Inserir\n");
        printf("[2] Remover\n");
        printf("[3] Imprimir fila\n");
        printf("[4] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            inserir(&fila, valor);
            break;
            case 2:
                removido = remover(&fila);
            if (removido) {
                printf("Elemento removido: %d\n", removido->valor);
                free(removido);
            }
            break;
            case 3:
                imprimir(&fila);
            break;
            case 4:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    // Liberar memória restante na fila
    while (&fila) {
        removido = remover(&fila);
        free(removido);
    }

    return 0;
}