#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó
typedef struct no {
    int valor;          // Valor armazenado no nó
    struct no *prox;    // Ponteiro para o próximo nó da lista
} No;

// Definindo a estrutura da lista
typedef struct {
    No *inicio; // Ponteiro para o início da lista
    No *fim;    // Ponteiro para o fim da lista
    int tam;    // Tamanho da lista
} Lista;

// Função para criar uma lista
void criar_lista(Lista *lista) {
    lista->inicio = NULL; // Inicializa o início da lista como NULL
    lista->fim = NULL;    // Inicializa o fim da lista como NULL
    lista->tam = 0;       // Inicializa o tamanho da lista como 0
}

// Função para inserir um elemento no início da lista
void inserir_no_inicio(Lista *lista, int num) {
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num;         // Atribui o valor ao novo nó
        novo->prox = lista->inicio; // O novo nó aponta para o antigo início da lista
        lista->inicio = novo;      // Atualiza o início da lista para o novo nó
        if (lista->fim == NULL) {  // Se a lista estava vazia, atualiza o fim também
            lista->fim = novo;
        }
        lista->fim->prox = lista->inicio; // Mantém a circularidade da lista
        lista->tam++;                     // Incrementa o tamanho da lista
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para inserir um elemento no final da lista
void inserir_no_final(Lista *lista, int num) {
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor ao novo nó
        if (lista->inicio == NULL) { // Se a lista está vazia, insere no início
            inserir_no_inicio(lista, num);
        } else {
            lista->fim->prox = novo; // O último nó aponta para o novo nó
            lista->fim = novo;       // Atualiza o fim da lista para o novo nó
            lista->fim->prox = lista->inicio; // Mantém a circularidade da lista
        }
        lista->tam++; // Incrementa o tamanho da lista
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para inserir um elemento no meio da lista
void inserir_no_meio(Lista *lista, int num, int ant) {
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor ao novo nó
        if (lista->inicio == NULL) { // Se a lista está vazia, insere no início
            novo->prox = NULL;
            lista->inicio = novo;
        } else {
            No *aux = lista->inicio; // Usa 'aux' para percorrer a lista
            while (aux->valor != ant && aux->prox != lista->inicio) {
                aux = aux->prox; // Procura o nó com valor 'ant' ou para no último nó
            }
            novo->prox = aux->prox; // O novo nó aponta para o próximo do nó atual
            aux->prox = novo;       // O nó atual aponta para o novo nó
        }
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para inserir um valor na lista de forma ordenada
void inserir_ordenado(Lista *lista, int num) {
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num; // Atribui o valor ao novo nó
        if (lista->inicio == NULL || novo->valor < lista->inicio->valor) {
            inserir_no_inicio(lista, num); // Insere no início se a lista está vazia ou o valor é menor
        } else {
            No *aux = lista->inicio; // Usa 'aux' para percorrer a lista
            while (aux->prox != lista->inicio && novo->valor > aux->prox->valor) {
                aux = aux->prox; // Procura a posição correta para inserir
            }
            if (aux->prox == lista->inicio) {
                inserir_no_final(lista, num); // Insere no final se for o maior valor
            } else {
                novo->prox = aux->prox; // O novo nó aponta para o próximo do nó atual
                aux->prox = novo;       // O nó atual aponta para o novo nó
                lista->tam++;           // Incrementa o tamanho da lista
            }
        }
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para remover um nó da lista
No* remover(Lista *lista, int num) {
    No *remover = NULL; // Inicializa um ponteiro para armazenar o nó a ser removido

    // Verifica se a lista não está vazia
    if (lista->inicio) {
        if (lista->inicio == lista->fim && lista->inicio->valor == num) {
            remover = lista->inicio; // Armazena o nó a ser removido
            lista->fim = NULL;       // Atualiza o fim da lista para NULL
            lista->inicio = NULL;    // Atualiza o início da lista para NULL
            lista->tam--;            // Decrementa o tamanho da lista
        } else if (lista->inicio->valor == num) {
            remover = lista->inicio; // Armazena o nó a ser removido
            lista->inicio = remover->prox; // Atualiza o início da lista para o próximo nó
            lista->fim->prox = lista->inicio; // Mantém a circularidade da lista
            lista->tam--;            // Decrementa o tamanho da lista
        } else {
            No *aux = lista->inicio; // Usa 'aux' para percorrer a lista
            while (aux->prox != lista->inicio && aux->prox->valor != num) {
                aux = aux->prox; // Procura o nó com valor 'num'
            }
            if (aux->prox->valor == num) {
                remover = aux->prox; // Armazena o nó a ser removido
                aux->prox = remover->prox; // Atualiza o próximo do nó atual
                if (lista->fim == remover) {
                    lista->fim = aux; // Atualiza o fim da lista se necessário
                }
                lista->tam--; // Decrementa o tamanho da lista
            }
        }
    }
    return remover; // Retorna o nó removido (ou NULL se não encontrado)
}

// Função para buscar um nó na lista
No* buscar(Lista *lista, int num) {
    No *aux = lista->inicio; // Usa 'aux' para percorrer a lista
    if (aux) {
        do {
            if (aux->valor == num) {
                return aux; // Retorna o nó se encontrado
            }
            aux = aux->prox; // Avança para o próximo nó
        } while (aux != lista->inicio);
    }
    return NULL; // Retorna NULL se não encontrado
}

// Função para imprimir os elementos da lista
void imprimir(Lista lista) {
    No *no = lista.inicio; // Usa 'no' para percorrer a lista
    printf("\n Lista: ");
    if (no) {
        do {
            printf("%d ", no->valor); // Imprime o valor do nó atual
            no = no->prox; // Avança para o próximo nó
        } while (no != lista.inicio);
        printf("\nInicio: %d\n", no->valor); // Imprime o valor do nó inicial
    }
    printf("\n \n");
}

// Função principal
int main() {
    Lista lista; // Declara uma variável do tipo Lista
    int opcao, valor, referencia; // Variáveis para armazenar a opção do menu, valor e referência
    No *ajudador = NULL; // Ponteiro auxiliar para operações de remoção e busca

    // Inicializa a lista
    criar_lista(&lista);

    // Loop do menu de opções
    do {
        // Menu de opções
        printf("\n--------------------------------------\n");
        printf("[1] Inserir no inicio\n");
        printf("[2] Inserir no fim\n");
        printf("[3] Inserir apos um valor\n");
        printf("[4] Inserir ordenado\n");
        printf("[5] Remover\n");
        printf("[6] Buscar\n");
        printf("[7] Imprimir lista\n");
        printf("[8] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário

        // Switch para tratar a opção escolhida
        switch (opcao) {
            case 1: // Inserir no início
                printf("Digite o valor a ser inserido no inicio: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_no_inicio(&lista, valor); // Chama a função para inserir no início
                break;

            case 2: // Inserir no fim
                printf("Digite o valor a ser inserido no fim: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_no_final(&lista, valor); // Chama a função para inserir no fim
                break;

            case 3: // Inserir após um valor (meio)
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                printf("Digite o valor de referencia (inserir apos): ");
                scanf("%d", &referencia); // Lê o valor de referência
                inserir_no_meio(&lista, valor, referencia); // Chama a função para inserir no meio
                break;

            case 4: // Inserir ordenado
                printf("Digite o valor a ser inserido ordenadamente: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_ordenado(&lista, valor); // Chama a função para inserir ordenado
                break;

            case 5: // Remover
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor); // Lê o valor a ser removido
                ajudador = remover(&lista, valor); // Chama a função para remover o nó
                if (ajudador) {
                    free(ajudador); // Libera a memória do nó removido
                }
                break;

            case 6: // Buscar
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor); // Lê o valor a ser buscado
                ajudador = buscar(&lista, valor); // Chama a função para buscar o nó
                if (ajudador) {
                    printf("Elemento encontrado: %d\n", ajudador->valor); // Imprime o valor encontrado
                } else {
                    printf("Elemento nao encontrado\n"); // Mensagem se o valor não for encontrado
                }
                break;

            case 7: // Imprimir lista
                imprimir(lista); // Chama a função para imprimir a lista
                break;

            case 8: // Sair
                printf("Encerrando o programa...\n");
                break;

            default: // Opção inválida
                printf("Opcao invalida! Tente novamente.\n");
        }

        // Limpa o buffer do teclado para evitar leituras fantasmas
        while (getchar() != '\n');
    } while (opcao != 8); // Repete o loop até que o usuário escolha sair

    // Libera a memória alocada para a lista
    No *atual = lista.inicio; // Ponteiro para percorrer a lista
    while (atual != NULL) {
        No *temp = atual; // Armazena o nó atual
        atual = atual->prox; // Avança para o próximo nó
        free(temp); // Libera a memória do nó atual
    }

    return 0; // Fim do programa
}