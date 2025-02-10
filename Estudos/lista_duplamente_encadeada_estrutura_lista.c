#include <stdio.h>
#include <stdlib.h>

// Definindo a estrutura do nó
typedef struct no {
    int valor;          // Valor armazenado no nó
    struct no *prox;    // Ponteiro para o próximo nó da lista
    struct no *ante;    // Ponteiro para o nó anterior
} No;

// Definindo a estrutura da lista
typedef struct {
    No *inicio; // Ponteiro para o início da lista
    int tam;    // Tamanho da lista
} Lista;

// Função para criar uma lista
void criar_lista(Lista *lista) {
    lista->inicio = NULL; // Inicializa o início da lista como NULL
    lista->tam = 0;       // Inicializa o tamanho da lista como 0
}

// Função para inserir um elemento no início da lista
void inserir_no_inicio(Lista *lista, int num) {
    No *novo = malloc(sizeof(No)); // Aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num;         // Atribui o valor ao novo nó
        novo->prox = lista->inicio; // O novo nó aponta para o antigo início da lista
        novo->ante = NULL;         // O anterior do novo nó é NULL
        if (lista->inicio) {
            lista->inicio->ante = novo; // O anterior do início da lista aponta para o novo nó
        }
        lista->inicio = novo;      // Atualiza o início da lista para o novo nó
        lista->tam++;              // Incrementa o tamanho da lista
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para inserir um elemento no final da lista
void inserir_no_final(Lista *lista, int num) {
    No *aux, *novo = malloc(sizeof(No)); // Declara ponteiros auxiliares e aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num;         // Atribui o valor ao novo nó
        novo->prox = NULL;         // Define o próximo do novo nó como NULL (pois ele será o último)
        novo->ante = NULL;         // Define o anterior do novo nó como NULL

        // Verifica se a lista está vazia
        if (lista->inicio == NULL) {
            lista->inicio = novo;  // Se estiver vazia, o novo nó é o primeiro (e único) elemento
        } else {
            aux = lista->inicio;   // Usa 'aux' para percorrer a lista sem perder a referência
            while (aux->prox != NULL) {
                aux = aux->prox;   // Percorre a lista até encontrar o último nó (cujo 'prox' é NULL)
            }
            aux->prox = novo;      // Conecta o último nó da lista ao novo nó
            novo->ante = aux;      // O anterior do novo nó aponta para o nó anterior
        }
        lista->tam++;              // Incrementa o tamanho da lista
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para inserir um elemento no meio da lista
void inserir_no_meio(Lista *lista, int num, int ant) {
    No *aux, *novo = malloc(sizeof(No)); // Declara ponteiros auxiliares e aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num;         // Atribui o valor ao novo nó

        // Verifica se a lista está vazia
        if (lista->inicio == NULL) {
            novo->prox = NULL;     // O próximo do novo nó é NULL
            novo->ante = NULL;     // O anterior do novo nó é NULL
            lista->inicio = novo;  // O início da lista aponta para o novo nó
        } else {
            aux = lista->inicio;   // Usa 'aux' para percorrer a lista
            while (aux->valor != ant && aux->prox) {
                aux = aux->prox;   // Procura o nó com valor 'ant' ou para no último nó
            }
            novo->prox = aux->prox; // O novo nó aponta para o próximo do nó atual
            if (aux->prox) {
                aux->prox->ante = novo; // O anterior do próximo nó aponta para o novo nó
            }
            novo->ante = aux;      // O anterior do novo nó aponta para o nó atual
            aux->prox = novo;      // O nó atual aponta para o novo nó
        }
        lista->tam++;              // Incrementa o tamanho da lista
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para inserir um valor na lista de forma ordenada
void inserir_ordenado(Lista *lista, int num) {
    No *aux, *novo = malloc(sizeof(No)); // Declara ponteiros auxiliares e aloca memória para o novo nó

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        novo->valor = num;         // Atribui o valor ao novo nó

        // Verifica se a lista está vazia
        if (lista->inicio == NULL) {
            novo->prox = NULL;     // O próximo do novo nó é NULL
            novo->ante = NULL;     // O anterior do novo nó é NULL
            lista->inicio = novo;  // O início da lista aponta para o novo nó
        } else if (novo->valor < lista->inicio->valor) {
            novo->prox = lista->inicio; // O novo nó aponta para o antigo início da lista
            lista->inicio->ante = novo; // O anterior do início da lista aponta para o novo nó
            lista->inicio = novo;       // O início da lista agora aponta para o novo nó
        } else {
            aux = lista->inicio;   // Inicializa 'aux' com o início da lista
            while (aux->prox && novo->valor > aux->prox->valor) {
                aux = aux->prox;   // Percorre a lista até encontrar a posição correta
            }
            novo->prox = aux->prox; // O novo nó aponta para o próximo nó de 'aux'
            if (aux->prox) {
                aux->prox->ante = novo; // O anterior do próximo nó aponta para o novo nó
            }
            novo->ante = aux;      // O anterior do novo nó aponta para 'aux'
            aux->prox = novo;      // O próximo de 'aux' aponta para o novo nó
        }
        lista->tam++;              // Incrementa o tamanho da lista
    } else {
        printf("Erro de alocação de memória\n"); // Mensagem de erro se a alocação falhar
    }
}

// Função para remover um nó da lista
No* remover(Lista *lista, int num) {
    No *aux, *remover = NULL; // Declara ponteiros auxiliares e inicializa 'remover' como NULL

    // Verifica se a lista não está vazia
    if (lista->inicio) {
        if (lista->inicio->valor == num) {
            remover = lista->inicio; // Armazena o nó a ser removido
            lista->inicio = remover->prox; // Atualiza o início da lista para o próximo nó
            if (lista->inicio) {
                lista->inicio->ante = NULL; // O anterior do novo início é NULL
            }
        } else {
            aux = lista->inicio;    // Inicializa 'aux' com o início da lista
            while (aux->prox && aux->prox->valor != num) {
                aux = aux->prox;   // Percorre a lista até encontrar o nó a ser removido
            }
            if (aux->prox) {
                remover = aux->prox; // Armazena o nó a ser removido
                aux->prox = remover->prox; // Atualiza o próximo do nó atual
                if (aux->prox) {
                    aux->prox->ante = aux; // O anterior do próximo nó aponta para 'aux'
                }
            }
        }
        lista->tam--;              // Decrementa o tamanho da lista
    }
    return remover; // Retorna o nó removido (ou NULL se não encontrado)
}

// Função para buscar um nó na lista
No* buscar(Lista *lista, int num) {
    No *aux = lista->inicio; // Inicializa 'aux' com o início da lista
    while (aux && aux->valor != num) {
        aux = aux->prox; // Percorre a lista até encontrar o nó ou chegar ao final
    }
    return aux; // Retorna o nó encontrado (ou NULL se não encontrado)
}

// Função para imprimir os elementos da lista
void imprimir(Lista lista) {
    No *no = lista.inicio; // Inicializa 'no' com o início da lista
    printf("\n\tLista: ");
    while (no) {
        printf("%d ", no->valor); // Imprime o valor do nó atual
        no = no->prox; // Avança para o próximo nó
    }
    printf("\n \n");
}

// Função para obter o último nó da lista
No* ultimo_no(Lista *lista) {
    No *aux = lista->inicio; // Inicializa 'aux' com o início da lista
    while (aux->prox) {
        aux = aux->prox; // Percorre a lista até o último nó
    }
    return aux; // Retorna o último nó
}

// Função para imprimir os elementos da lista em ordem inversa
void imprimir_contraio(No *no) {
    printf("\n\tLista: ");
    while (no) {
        printf("%d ", no->valor); // Imprime o valor do nó atual
        no = no->ante; // Retrocede para o nó anterior
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
        printf("[8] Imprimir lista ao contrario\n");
        printf("[9] Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // Lê a opção escolhida pelo usuário

        // Switch para tratar a opção escolhida
        switch (opcao) {
            case 1: // Inserir no início
                printf("Digite o valor a ser inserido no inicio: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_no_inicio(&lista, valor); // Chama a função para inserir no início
                imprimir(lista); // Imprime a lista atualizada
                break;

            case 2: // Inserir no fim
                printf("Digite o valor a ser inserido no fim: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_no_final(&lista, valor); // Chama a função para inserir no fim
                imprimir(lista); // Imprime a lista atualizada
                break;

            case 3: // Inserir após um valor (meio)
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                printf("Digite o valor de referencia (inserir apos): ");
                scanf("%d", &referencia); // Lê o valor de referência
                inserir_no_meio(&lista, valor, referencia); // Chama a função para inserir no meio
                imprimir(lista); // Imprime a lista atualizada
                break;

            case 4: // Inserir ordenado
                printf("Digite o valor a ser inserido ordenadamente: ");
                scanf("%d", &valor); // Lê o valor a ser inserido
                inserir_ordenado(&lista, valor); // Chama a função para inserir ordenado
                imprimir(lista); // Imprime a lista atualizada
                break;

            case 5: // Remover
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor); // Lê o valor a ser removido
                ajudador = remover(&lista, valor); // Chama a função para remover o nó
                if (ajudador) {
                    free(ajudador); // Libera a memória do nó removido
                }
                imprimir(lista); // Imprime a lista atualizada
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

            case 8: // Imprimir lista ao contrário
                imprimir_contraio(ultimo_no(&lista)); // Chama a função para imprimir a lista ao contrário
                break;

            case 9: // Sair
                printf("Encerrando o programa...\n");
                break;

            default: // Opção inválida
                printf("Opcao invalida! Tente novamente.\n");
        }

        // Limpa o buffer do teclado para evitar leituras fantasmas
        while (getchar() != '\n');
    } while (opcao != 9); // Repete o loop até que o usuário escolha sair

    // Libera a memória alocada para a lista
    No *atual = lista.inicio; // Ponteiro para percorrer a lista
    while (atual != NULL) {
        No *temp = atual; // Armazena o nó atual
        atual = atual->prox; // Avança para o próximo nó
        free(temp); // Libera a memória do nó atual
    }

    return 0; // Fim do programa
}