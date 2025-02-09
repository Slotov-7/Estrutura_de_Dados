// Criado por Guilherme Araújo em 06/02/2025.
//
#include <stdlib.h>
#include <stdio.h>

// Define uma estrutura para um nó na pilha
typedef struct no {
    int valor; // Valor armazenado no nó
    struct no *prox; // Ponteiro para o próximo nó
} No;

// Define uma estrutura para a pilha
typedef struct {
    No *inicio; // Ponteiro para o primeiro nó da pilha
    int tam; // Tamanho da pilha
} Pilha;

// Função para inicializar a pilha
void criar_pilha(Pilha *pilha) {
    pilha->inicio = NULL; // Define o ponteiro início como NULL
    pilha->tam = 0; // Define o tamanho da pilha como 0
}

// Função para inserir um novo nó na pilha
void inserir(Pilha *pilha, int num) {
    No *novo = malloc(sizeof(No)); // Aloca memória para um novo nó

    // Verifica se a alocação de memória foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor ao novo nó
        novo->prox = pilha->inicio; // Define o próximo do novo nó como o início atual da pilha
        pilha->inicio = novo; // Atualiza o início da pilha para o novo nó
        pilha->tam++; // Incrementa o tamanho da pilha
    } else {
        printf("Erro ao alocar memoria"); // Imprime uma mensagem de erro se a alocação falhar
    }
}

// Função para remover um nó da pilha
No* remover(Pilha *pilha) {
    No *remover = NULL; // Inicializa um ponteiro para armazenar o nó a ser removido

    // Verifica se a pilha não está vazia
    if (pilha->inicio) {
        remover = pilha->inicio; // Armazena o nó a ser removido
        pilha->inicio = remover->prox; // Atualiza o início da pilha para o próximo nó
        pilha->tam--; // Decrementa o tamanho da pilha
    } else {
        printf("A pilha está vazia\n"); // Imprime uma mensagem de erro se a pilha estiver vazia
    }
    return remover; // Retorna o nó removido (ou NULL se a pilha estiver vazia)
}

// Função para imprimir os elementos da pilha
void imprimir(Pilha *pilha) {
    No *aux = pilha->inicio; // Inicializa um ponteiro para percorrer a pilha
    printf("PILHA: \n"); // Imprime o rótulo da pilha

    // Percorre a pilha e imprime cada elemento
    while (aux) {
        printf("%d ", aux->valor); // Imprime o valor do nó atual
        aux = aux->prox; // Move para o próximo nó
    }
}

// Função principal
int main() {
    Pilha pilha; // Declara uma pilha
    int opcao, valor; // Declara variáveis para entrada do usuário
    No *removido; // Declara um ponteiro para armazenar o nó removido
    criar_pilha(&pilha); // Inicializa a pilha

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
                imprimir(&pilha); // Imprime os elementos da pilha
                break;
            case 4:
                printf("Saindo...\n"); // Imprime uma mensagem indicando a saída
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n"); // Imprime uma mensagem de erro para escolha inválida
        }
    } while (opcao != 4); // Continua o loop até o usuário escolher sair

    // Libera os nós restantes na pilha
    while (pilha.inicio) {
        removido = remover(&pilha); // Remove um nó da pilha
        free(removido); // Libera a memória do nó removido
    }

    return 0; // Retorna 0 para indicar execução bem-sucedida
}