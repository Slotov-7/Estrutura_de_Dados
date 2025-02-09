//
// Created by Guilherme Araújo on 06/02/2025.
//
#include <stdlib.h>
#include <stdio.h>

// Define uma estrutura para um nó na pilha
typedef struct no {
    int valor; // Valor armazenado no nó
    struct no *prox; // Ponteiro para o próximo nó
} No;

// Função para inserir um novo nó na pilha
void inserir(No **pilha, int num) {
    No *novo = malloc(sizeof(No)); // Aloca memória para um novo nó

    // Verifica se a alocação de memória foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor ao novo nó
        novo->prox = *pilha; // Define o próximo do novo nó como o topo atual da pilha
        *pilha = novo; // Atualiza o topo da pilha para o novo nó
    } else {
        printf("Erro ao alocar memoria"); // Imprime uma mensagem de erro se a alocação falhar
    }
}

// Função para remover um nó da pilha
No* remover(No **pilha) {
    No *remover = NULL; // Inicializa um ponteiro para armazenar o nó a ser removido

    // Verifica se a pilha não está vazia
    if (*pilha) {
        remover = *pilha; // Armazena o nó a ser removido
        *pilha = remover->prox; // Atualiza o topo da pilha para o próximo nó
    } else {
        printf("A pilha está vazia\n"); // Imprime uma mensagem de erro se a pilha estiver vazia
    }
    return remover; // Retorna o nó removido (ou NULL se a pilha estiver vazia)
}

// Função para imprimir os elementos da pilha
void imprimir(No *pilha) {
    printf("PILHA: \n"); // Imprime o rótulo da pilha

    // Percorre a pilha e imprime cada elemento
    while (pilha) {
        printf("%d ", pilha->valor); // Imprime o valor do nó atual
        pilha = pilha->prox; // Move para o próximo nó
    }
}

// Função principal
int main() {
    No *pilha = NULL; // Declara uma pilha inicializada como vazia
    int opcao, valor; // Declara variáveis para entrada do usuário
    No *removido; // Declara um ponteiro para armazenar o nó removido

    // Loop para exibir o menu e realizar operações com base na entrada do usuário
    do {
        printf("\n--------------------------------------\n");
        printf("[1] Inserir\n");
        printf("[2] Remover\n");
        printf("[3] Imprimir pilha\n");
        printf("[4] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Lê a escolha do usuário

        // Realiza a operação correspondente com base na escolha do usuário
        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir(&pilha, valor); // Insere o valor na pilha
                break;
            case 2:
                removido = remover(&pilha); // Remove um nó da pilha
                if (removido) {
                    printf("Elemento removido: %d\n", removido->valor); // Imprime o valor removido
                    free(removido); // Libera a memória do nó removido
                }
                break;
            case 3:
                imprimir(pilha); // Imprime os elementos da pilha
                break;
            case 4:
                printf("Saindo...\n"); // Imprime uma mensagem indicando a saída
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n"); // Imprime uma mensagem de erro para escolha inválida
        }
    } while (opcao != 4); // Continua o loop até o usuário escolher sair

    // Libera os nós restantes na pilha
    while (pilha) {
        removido = remover(&pilha); // Remove um nó da pilha
        free(removido); // Libera a memória do nó removido
    }

    return 0; // Retorna 0 para indicar execução bem-sucedida
}