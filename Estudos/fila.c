//
// Created by Guilherme Araújo on 06/02/2025.
//
// FIFO, First in, First out
#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    int valor;
    struct no *prox;
}No;

void inserir(No **fila, int num) {
    No *aux, *novo = malloc(sizeof(No));

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        // Atribui o valor 'num' ao novo nó
        novo->valor = num;
        // Define o próximo do novo nó como NULL (pois ele será o último)
        novo->prox = NULL;
        // Verifica se a lista está vazia
        if (*fila == NULL) {
            // Se estiver vazia, o novo nó é o primeiro (e único) elemento
            *fila = novo;
        } else {
            // Se não estiver vazia, usa 'aux' para percorrer a lista sem perder a referência
            aux = *fila;
            // Percorre a lista até encontrar o último nó (cujo 'prox' é NULL)
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            // Conecta o último nó da fila ao novo nó
            aux->prox = novo;
        }
    } else {
        printf("Erro de alocação de memória\n");
    }
}
No* remover(No **fila) {
    No *remover = NULL;
    if (*fila) {
            remover = *fila; // Armazena o nó a ser removido.
            *fila = remover->prox; // Atualiza o início da fila para o próximo nó.
    }else {
        printf("A fila esta vazia");
    }
    return remover;
}
void imprimir (No *fila) {
    printf("FILA: ");
    while (fila) {
        printf("%d ", fila->valor);
        fila = fila->prox;
    }
}

int main() {
    No *fila = NULL;
    int opcao, valor;
    No *removido;

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
                imprimir(fila);
            break;
            case 4:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    // Liberar memória restante na fila
    while (fila) {
        removido = remover(&fila);
        free(removido);
    }

    return 0;
}