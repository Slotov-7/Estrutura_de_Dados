//
// Created by Guilherme Araújo on 06/02/2025.
//
// FIFO, First in, First out (Primeiro a entrar, primeiro a sair)
#include <stdlib.h>
#include <stdio.h>

// Define uma estrutura para um nó na fila
typedef struct no {
    int valor; // Valor armazenado no nó
    struct no *prox; // Ponteiro para o próximo nó
} No;

// Função para inserir um novo nó na fila
void inserir(No **fila, int num) {
    No *aux, *novo = malloc(sizeof(No)); // Aloca memória para um novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor 'num' ao novo nó
        novo->prox = NULL; // Define o próximo do novo nó como NULL (pois ele será o último)

        // Verifica se a lista está vazia
        if (*fila == NULL) {
            *fila = novo; // Se estiver vazia, o novo nó é o primeiro (e único) elemento
        } else {
            aux = *fila; // Usa 'aux' para percorrer a lista sem perder a referência
            while (aux->prox != NULL) {
                aux = aux->prox; // Percorre a lista até encontrar o último nó (cujo 'prox' é NULL)
            }
            aux->prox = novo; // Conecta o último nó da fila ao novo nó
        }
    } else {
        printf("Erro de alocação de memória\n"); // Imprime uma mensagem de erro se a alocação falhar
    }
}

// Função para inserir um novo nó na fila com prioridade
void inserir_prioridade(No **fila, int num) {
    No *aux, *novo = malloc(sizeof(No)); // Aloca memória para um novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor 'num' ao novo nó
        novo->prox = NULL; // Define o próximo do novo nó como NULL (pois ele será o último)

        // Verifica se a lista está vazia
        if (*fila == NULL) {
            *fila = novo; // Se estiver vazia, o novo nó é o primeiro (e único) elemento
        } else {
            // Verifica se o valor é de prioridade
            if (num > 59) {
                // Se o primeiro nó não for de prioridade, insere o novo nó no início
                if ((*fila)->valor < 60) {
                    novo->prox = *fila;
                    *fila = novo;
                } else {
                    aux = *fila; // Usa 'aux' para percorrer a lista sem perder a referência
                    while (aux->prox && aux->prox->valor > 59) {
                        aux = aux->prox; // Percorre a lista até encontrar o último nó de prioridade
                    }
                    novo->prox = aux->prox; // Conecta o novo nó na posição correta
                    aux->prox = novo;
                }
            } else {
                aux = *fila; // Usa 'aux' para percorrer a lista sem perder a referência
                while (aux->prox) {
                    aux = aux->prox; // Percorre a lista até encontrar o último nó
                }
                aux->prox = novo; // Conecta o último nó da fila ao novo nó
            }
        }
    } else {
        printf("Erro de alocação de memória\n"); // Imprime uma mensagem de erro se a alocação falhar
    }
}

// Função para remover um nó da fila
No* remover(No **fila) {
    No *remover = NULL; // Inicializa um ponteiro para armazenar o nó a ser removido

    // Verifica se a fila não está vazia
    if (*fila) {
        remover = *fila; // Armazena o nó a ser removido
        *fila = remover->prox; // Atualiza o início da fila para o próximo nó
    } else {
        printf("A fila está vazia\n"); // Imprime uma mensagem de erro se a fila estiver vazia
    }
    return remover; // Retorna o nó removido (ou NULL se a fila estiver vazia)
}

// Função para imprimir os elementos da fila
void imprimir(No *fila) {
    printf("FILA: "); // Imprime o rótulo da fila

    // Percorre a fila e imprime cada elemento
    while (fila) {
        printf("%d ", fila->valor); // Imprime o valor do nó atual
        fila = fila->prox; // Move para o próximo nó
    }
}

// Função principal
int main() {
    No *fila = NULL; // Declara uma fila inicializada como vazia
    int opcao, valor; // Declara variáveis para entrada do usuário
    No *removido; // Declara um ponteiro para armazenar o nó removido

    // Loop para exibir o menu e realizar operações com base na entrada do usuário
    do {
        printf("\n--------------------------------------\n");
        printf("[1] Inserir\n");
        printf("[2] Remover\n");
        printf("[3] Imprimir fila\n");
        printf("[4] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Lê a escolha do usuário

        // Realiza a operação correspondente com base na escolha do usuário
        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir(&fila, valor); // Insere o valor na fila
                break;
            case 2:
                removido = remover(&fila); // Remove um nó da fila
                if (removido) {
                    printf("Elemento removido: %d\n", removido->valor); // Imprime o valor removido
                    free(removido); // Libera a memória do nó removido
                }
                break;
            case 3:
                imprimir(fila); // Imprime os elementos da fila
                break;
            case 4:
                printf("Saindo...\n"); // Imprime uma mensagem indicando a saída
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n"); // Imprime uma mensagem de erro para escolha inválida
        }
    } while (opcao != 4); // Continua o loop até o usuário escolher sair

    // Libera os nós restantes na fila
    while (fila) {
        removido = remover(&fila); // Remove um nó da fila
        free(removido); // Libera a memória do nó removido
    }

    return 0; // Retorna 0 para indicar execução bem-sucedida
}