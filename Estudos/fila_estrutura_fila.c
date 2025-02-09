// Criado por Guilherme Araújo em 06/02/2025.
//
// FIFO, First in, First out (Primeiro a entrar, primeiro a sair)
#include <stdlib.h>
#include <stdio.h>

// Define uma estrutura para um nó na fila
typedef struct no {
    int valor; // Valor armazenado no nó
    struct no *prox; // Ponteiro para o próximo nó
} No;

// Define uma estrutura para a fila
typedef struct {
    No *inicio; // Ponteiro para o primeiro nó da fila
    No *final; // Ponteiro para o último nó da fila
    int tam; // Tamanho da fila
} Fila;

// Função para inicializar a fila
void criar_fila(Fila *fila) {
    fila->final = NULL; // Define o ponteiro final como NULL
    fila->inicio = NULL; // Define o ponteiro início como NULL
    fila->tam = 0; // Define o tamanho da fila como 0
}

// Função para inserir um novo nó na fila
void inserir(Fila *fila, int num) {
    No *novo = malloc(sizeof(No)); // Aloca memória para um novo nó

    // Verifica se a alocação de memória foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor ao novo nó
        novo->prox = NULL; // Define o próximo do novo nó como NULL

        // Verifica se a fila está vazia
        if (fila->inicio == NULL) {
            fila->inicio = novo; // Define o novo nó como o primeiro nó
            fila->final = novo; // Define o novo nó como o último nó
        } else {
            fila->final->prox = novo; // Conecta o último nó ao novo nó
            fila->final = novo; // Atualiza o último nó para o novo nó
        }
        fila->tam++; // Incrementa o tamanho da fila
    } else {
        printf("Erro de alocação de memória\n"); // Imprime uma mensagem de erro se a alocação falhar
    }
}

// Função para remover um nó da fila
No* remover(Fila *fila) {
    No *remover = NULL; // Inicializa um ponteiro para armazenar o nó a ser removido

    // Verifica se a fila não está vazia
    if (fila->inicio) {
        remover = fila->inicio; // Armazena o primeiro nó a ser removido
        fila->inicio = remover->prox; // Atualiza o primeiro nó para o próximo nó
        fila->tam--; // Decrementa o tamanho da fila
    } else {
        printf("A fila está vazia\n"); // Imprime uma mensagem de erro se a fila estiver vazia
    }
    return remover; // Retorna o nó removido
}

// Função para imprimir os elementos da fila
void imprimir(Fila *fila) {
    No *aux = fila->inicio; // Inicializa um ponteiro para percorrer a fila
    printf("FILA: "); // Imprime o rótulo da fila

    // Percorre a fila e imprime cada elemento
    while (aux) {
        printf("%d ", aux->valor); // Imprime o valor do nó atual
        aux = aux->prox; // Move para o próximo nó
    }
}

// Função principal
int main() {
    Fila fila; // Declara uma fila
    int opcao, valor; // Declara variáveis para entrada do usuário
    No *removido; // Declara um ponteiro para armazenar o nó removido
    criar_fila(&fila); // Inicializa a fila

    // Loop para exibir o menu e realizar operações com base na entrada do usuário
    do {
        printf("\n--------------------------------------\n");
        printf("[1] Inserir\n");
        printf("[2] Remover\n");
        printf("[3] Imprimir fila\n");
        printf("[4] Sair\n");
        printf("Escolha uma opção: ");
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
                imprimir(&fila); // Imprime os elementos da fila
                break;
            case 4:
                printf("Saindo...\n"); // Imprime uma mensagem indicando a saída
                break;
            default:
                printf("Opção inválida! Tente novamente.\n"); // Imprime uma mensagem de erro para escolha inválida
        }
    } while (opcao != 4); // Continua o loop até o usuário escolher sair

    // Libera os nós restantes na fila
    while (fila.inicio) {
        removido = remover(&fila); // Remove um nó da fila
        free(removido); // Libera a memória do nó removido
    }

    return 0; // Retorna 0 para indicar execução bem-sucedida
}