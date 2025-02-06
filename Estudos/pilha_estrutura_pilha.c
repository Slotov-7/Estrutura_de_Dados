//
// Created by Guilherme Araújo on 06/02/2025.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct no {
    int valor;
    struct no *prox;
}No;

typedef struct {
    No *inicio;
    int tam;
}Pilha;

void criar_pilha(Pilha *pilha) {
    pilha->inicio = NULL;
    pilha->tam = 0;
}


void inserir (Pilha *pilha, int num) {
    No *novo = malloc(sizeof(No));
    if (novo) {
        novo->valor = num;
        novo->prox = pilha->inicio;
        pilha->inicio = novo;
        pilha->tam++;
    }else {
        printf("Erro ao alocar memoria");
    }
}

No* remover(Pilha *pilha) {
    No *remover = NULL;
    if (pilha) {
        remover = pilha->inicio; // Armazena o nó a ser removido
        pilha->inicio = remover->prox; // Atualiza o topo da pilha
        pilha->tam--;
    } else {
        printf("A pilha está vazia\n"); // Mensagem de erro com quebra de linha
    }
    return remover; // Retorna o nó removido (ou NULL se a pilha estiver vazia)
}

void imprimir(Pilha *pilha) {
    No *aux = pilha->inicio;
    printf("PILHA: \n");
    while (aux) {
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
}

int main() {
    Pilha pilha;
    int opcao, valor;
    No *removido;
    criar_pilha(&pilha);

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
                imprimir(&pilha);
            break;
            case 4:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    while (&pilha) {
        removido = remover(&pilha);
        free(removido);
    }
    return 0;
}