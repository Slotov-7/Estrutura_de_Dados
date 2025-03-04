#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó
typedef struct no {
    int valor; // Valor armazenado no nó
    struct no *filhoEsq; // Ponteiro para o filho esquerdo
    struct no *filhoDir; // Ponteiro para o filho direito
} No;

// Função para inserir um nó na árvore
No* inserir_1(No *raiz, int valor) {
    if (raiz == NULL) { // Se a árvore está vazia
        No *novo = malloc(sizeof(No)); // Aloca memória para um novo nó
        if (novo == NULL) { // Verifica se a alocação foi bem-sucedida
            printf("Erro ao alocar memoria\n"); // Imprime mensagem de erro
            return NULL; // Retorna NULL se a alocação falhar
        }
        novo->valor = valor; // Atribui o valor ao novo nó
        novo->filhoEsq = NULL; // Inicializa o filho esquerdo como NULL
        novo->filhoDir = NULL; // Inicializa o filho direito como NULL
        return novo; // Retorna o novo nó
    }
    if (valor < raiz->valor) { // Se o valor é menor que o valor do nó atual
        raiz->filhoEsq = inserir_1(raiz->filhoEsq, valor); // Insere no filho esquerdo
    } else { // Se o valor é maior ou igual ao valor do nó atual
        raiz->filhoDir = inserir_1(raiz->filhoDir, valor); // Insere no filho direito
    }
    return raiz; // Retorna a raiz da árvore
}

// Função para inserir um nó na árvore sem retornar o nó
void inserir_2(No **raiz, int valor) {
    if (*raiz == NULL) { // Se a árvore está vazia
        *raiz = malloc(sizeof(No)); // Aloca memória para um novo nó
        if (*raiz == NULL) { // Verifica se a alocação foi bem-sucedida
            printf("Erro ao alocar memoria\n"); // Imprime mensagem de erro
            return; // Retorna se a alocação falhar
        }
        (*raiz)->valor = valor; // Atribui o valor ao novo nó
        (*raiz)->filhoEsq = NULL; // Inicializa o filho esquerdo como NULL
        (*raiz)->filhoDir = NULL; // Inicializa o filho direito como NULL
    } else {
        if (valor < (*raiz)->valor) { // Se o valor é menor que o valor do nó atual
            inserir_2(&((*raiz)->filhoEsq), valor); // Insere no filho esquerdo
        } else { // Se o valor é maior ou igual ao valor do nó atual
            inserir_2(&((*raiz)->filhoDir), valor); // Insere no filho direito
        }
    }
}

// Função para inserir um nó na árvore iterativamente
void inserir_3(No **raiz, int valor) {
    No *aux = *raiz; // Ponteiro auxiliar para percorrer a árvore
    while (aux) { // Enquanto não encontrar uma posição vazia
        if (valor < aux->valor) { // Se o valor é menor que o valor do nó atual
            raiz = &(aux->filhoEsq); // Move para o filho esquerdo
        } else { // Se o valor é maior ou igual ao valor do nó atual
            raiz = &(aux->filhoDir); // Move para o filho direito
        }
        aux = *raiz; // Atualiza o ponteiro auxiliar
    }
    aux = malloc(sizeof(No)); // Aloca memória para um novo nó
    if (aux) { // Se a alocação foi bem-sucedida
        aux->valor = valor; // Atribui o valor ao novo nó
        aux->filhoDir = NULL; // Inicializa o filho direito como NULL
        aux->filhoEsq = NULL; // Inicializa o filho esquerdo como NULL
        *raiz = aux; // Atualiza o ponteiro raiz
    } else { // Se a alocação falhar
        printf("Erro ao alocar memoria\n"); // Imprime mensagem de erro
    }
}

// Função para imprimir a árvore em pré-ordem
void imprimir_arvore_pre_ordem(No *raiz) {
    if (raiz) { // Se o nó não é NULL
        printf("%d ", raiz->valor); // Imprime o valor do nó
        imprimir_arvore_pre_ordem(raiz->filhoEsq); // Imprime o filho esquerdo em pré-ordem
        imprimir_arvore_pre_ordem(raiz->filhoDir); // Imprime o filho direito em pré-ordem
    }
}

// Função para imprimir a árvore em in-ordem/ordem simétrica
void imprimir_arvore_in_ordem(No *raiz) {
    if (raiz) { // Se o nó não é NULL
        imprimir_arvore_in_ordem(raiz->filhoEsq); // Imprime o filho esquerdo em in-ordem
        printf("%d ", raiz->valor); // Imprime o valor do nó
        imprimir_arvore_in_ordem(raiz->filhoDir); // Imprime o filho direito em in-ordem
    }
}

No* buscar_1(No *raiz, int valor) {
    if (raiz) {
        if (valor == raiz->valor) {
            return raiz;
        }
        if(valor < raiz->valor) {
            return buscar_1(raiz->filhoEsq, valor);
        }
            return buscar_1(raiz->filhoDir, valor);
    }
    return NULL;
}

// Função principal
int main() {
    No *busca, *raiz = NULL; // Inicializa a árvore como vazia
    int opcao, valor; // Variáveis para armazenar a opção do menu e o valor a ser inserido

    do {
        printf("\nMenu de Opcoes:\n");
        printf("1 - Inserir um valor na arvore\n");
        printf("2 - Inserir um valor (sem return) na arvore\n");
        printf("3 - Inserir um valor (imperativo) na arvore\n");
        printf("4 - Imprimir arvore em pre-ordem\n");
        printf("5 - Imprimir arvore em in-ordem\n");
        printf("6 - Buscar um valor na arvore\n");
        printf("7 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Lê a opção do usuário

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                raiz = inserir_1(raiz, valor); // Insere o valor na árvore usando a função inserir_1
                printf("Valor %d inserido com sucesso!\n", valor);
                break;

            case 2:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_2(&raiz, valor); // Insere o valor na árvore usando a função inserir_2
                printf("Valor %d inserido com sucesso!\n", valor);
                break;

            case 3:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_3(&raiz, valor); // Insere o valor na árvore usando a função inserir_3
                printf("Valor %d inserido com sucesso!\n", valor);
                break;

            case 4:
                if (raiz == NULL) { // Se a árvore está vazia
                    printf("A arvore esta vazia!\n");
                } else {
                    printf("Impressao em pre-ordem: ");
                    imprimir_arvore_pre_ordem(raiz); // Imprime a árvore em pré-ordem
                    printf("\n");
                }
                break;

            case 5:
                if (raiz == NULL) { // Se a árvore está vazia
                    printf("A arvore esta vazia!\n");
                } else {
                    printf("Impressao em in-ordem: ");
                    imprimir_arvore_in_ordem(raiz); // Imprime a árvore em in-ordem
                    printf("\n");
                }
                break;

            case 6:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor); // Lê o valor a ser buscado
                busca = buscar_1(raiz, valor); // Busca o valor na árvore usando a função buscar_1
                if (busca) {
                    printf("\n\tValor %d encontrado na arvore!\n", valor);
                }else {
                    printf("\n\tValor %d nao encontrado na arvore!\n", valor);
                }
            break;

            case 7:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 7); // Continua o loop até o usuário escolher sair

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}