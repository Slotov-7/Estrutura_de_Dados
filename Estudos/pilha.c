//
// Created by Guilherme Araújo on 06/02/2025.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    int valor;
    struct no *prox;
}No;

void inserir (No **pilha, int num) {
    No *novo = malloc(sizeof(No));
    if (novo) {
        novo->valor = num;
        novo->prox = *pilha;
        *pilha = novo;
    }else {
        printf("Erro ao alocar memoria");
    }
}

No* remover(No **pilha) {
    No *remover = NULL;
    if (*pilha) {
        remover = *pilha; // Armazena o nó a ser removido
        *pilha = remover->prox; // Atualiza o topo da pilha
    } else {
        printf("A pilha está vazia\n"); // Mensagem de erro com quebra de linha
    }
    return remover; // Retorna o nó removido (ou NULL se a pilha estiver vazia)
}

void imprimir(No *pilha) {
    printf("PILHA: \n");
    while (pilha) {
        printf("%d ", pilha->valor);
        pilha = pilha->prox;
    }
}

int main() {
    No *pilha = NULL;
    int opcao, valor;
    No *removido;

    do {
        printf("\n--------------------------------------\n");;
        printf("[1] Inserir\n");
        printf("[2] Remover\n");
        printf("[3] Imprimir pilha\n");
        printf("[4] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            inserir(&pilha, valor);
            break;
            case 2:
                removido = remover(&pilha);
            if (removido) {
                printf("Elemento removido: %d\n", removido->valor);
                free(removido);
            }
            break;
            case 3:
                imprimir(pilha);
            break;
            case 4:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    while (pilha) {
        removido = remover(&pilha);
        free(removido);
    }
    return 0;
}