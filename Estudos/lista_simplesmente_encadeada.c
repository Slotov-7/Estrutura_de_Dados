//
// Created by Guilherme Araújo on 29/01/2025.
//
#include <stdio.h>
#include <stdlib.h>

//definindo a estrutura do nó
typedef struct no {
    int valor;          // Valor armazenado no nó
    struct no *prox;    // Ponteiro para o próximo nó da lista
} No;

typedef struct {
    No *inicio;
    int tam;
}Lista;

void criar_lista(Lista *lista) {
    lista -> inicio = NULL;
    lista -> tam = 0;
}

//procedimento para inserir um elemento no inicio da lista
//procedimento para inserir um elemento no inicio da lista
void inserir_no_inicio(No **lista, int num) {
    // Aloca memória para o novo nó
    No *novo = malloc(sizeof(No));

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        // Atribui o valor 'num' ao campo 'valor' do novo nó
        novo->valor = num;

        // O novo nó aponta para o antigo início da lista (ou NULL se a lista estava vazia)
        novo->prox = *lista;

        // Atualiza o ponteiro da lista para apontar para o novo nó (novo início)
        *lista = novo;
    } else {
        printf("Erro de alocação de memória\n");
    }
}
//procedimento para inserir um elemento no final da lista

void inserir_no_final(No **lista, int num) {
    // Declara ponteiros auxiliares e aloca memória para o novo nó
    No *aux, *novo = malloc(sizeof(No));

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        // Atribui o valor 'num' ao novo nó
        novo->valor = num;
        // Define o próximo do novo nó como NULL (pois ele será o último)
        novo->prox = NULL;
        // Verifica se a lista está vazia
        if (*lista == NULL) {
            // Se estiver vazia, o novo nó é o primeiro (e único) elemento
            *lista = novo;
        } else {
            // Se não estiver vazia, usa 'aux' para percorrer a lista sem perder a referência
            aux = *lista;
            // Percorre a lista até encontrar o último nó (cujo 'prox' é NULL)
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            // Conecta o último nó da lista ao novo nó
            aux->prox = novo;
        }
    } else {
        printf("Erro de alocação de memória\n");
    }
}
//procedimento para inserir um elemento no meio da lista

void inserir_no_meio(No **lista, int num, int ant) {
    // Declara ponteiros auxiliares e aloca memória para o novo nó
    No *aux, *novo = malloc(sizeof(No));

    // Verifica se a alocação foi bem-sucedida
    if (novo) {
        // Atribui o valor 'num' ao novo nó
        novo->valor = num;
        // Verifica se a lista está vazia
        if (*lista == NULL) {
            // Se estiver vazia, o novo nó é o primeiro (e único) elemento
            novo->prox = NULL;
            *lista = novo;
        } else {
            // Se não estiver vazia, usa 'aux' para percorrer a lista
            aux = *lista;
            // Procura o nó com valor 'ant' OU para no último nó (se 'ant' não existir)
            while (aux->valor != ant && aux->prox) {
                aux = aux->prox;
            }
            // Insere o novo nó após o nó encontrado (ou após o último se 'ant' não existir)
            novo->prox = aux->prox; // Novo nó aponta para o próximo do nó atual
            aux->prox = novo;       // Nó atual aponta para o novo nó
        }
    } else {
        printf("Erro de alocação de memória\n");
    }
}

// procedimento para inserir um valor na lista de forma ordenada
void inserir_ordenado(No **lista, int num) {
    // Declaração de variáveis:
    // - aux: ponteiro auxiliar para percorrer a lista.
    // - novo: ponteiro para o novo nó a ser inserido.
    No *aux, *novo = malloc(sizeof(No));

    // Verifica se a alocação de memória para o novo nó foi bem-sucedida.
    if (novo) {
        // Atribui o valor 'num' ao novo nó.
        novo->valor = num;

        // Verifica se a lista está vazia (ou seja, se *lista é NULL).
        if (*lista == NULL) {
            // Se a lista estiver vazia, o novo nó será o primeiro e único nó da lista.
            novo->prox = NULL; // O próximo do novo nó é NULL.
            *lista = novo;     // O início da lista aponta para o novo nó.
        }
        // Verifica se o valor do novo nó é menor que o valor do primeiro nó da lista.
        else if (novo->valor < (*lista)->valor) {
            // Se for menor, o novo nó será inserido no início da lista.
            novo->prox = *lista; // O próximo do novo nó aponta para o antigo início da lista.
            *lista = novo;       // O início da lista agora aponta para o novo nó.
        }
        // Caso o novo nó não seja o menor, procura a posição correta para inseri-lo.
        else {
            aux = *lista; // Inicializa aux com o início da lista.

            // Percorre a lista enquanto houver um próximo nó (aux->prox) e o valor do novo nó for maior que o valor do próximo nó.
            while (aux->prox && novo->valor > aux->prox->valor) {
                aux = aux->prox; // Avança para o próximo nó.
            }

            // Insere o novo nó na posição correta.
            novo->prox = aux->prox; // O próximo do novo nó aponta para o próximo nó de aux.
            aux->prox = novo;       // O próximo de aux aponta para o novo nó.
        }
    }
    // Caso a alocação de memória falhe, exibe uma mensagem de erro.
    else {
        printf("Erro de alocação de memória\n");
    }
}

No* remover(No **lista, int num) {
    // Declaração de variáveis:
    // - aux: ponteiro auxiliar para percorrer a lista.
    // - remover: ponteiro que armazenará o nó a ser removido (inicialmente NULL).
    No *aux, *remover = NULL;

    // Verifica se a lista não está vazia (ou seja, se *lista não é NULL).
    if (*lista) {

        // Verifica se o valor do primeiro nó da lista é igual ao valor procurado (num).
        if ((*lista)->valor == num) {
            // Se for igual, o nó a ser removido é o primeiro nó.
            remover = *lista; // Armazena o nó a ser removido.
            *lista = remover->prox; // Atualiza o início da lista para o próximo nó.
        } else {
            // Se o valor não estiver no primeiro nó, percorre a lista para encontrá-lo.
            aux = *lista; // Inicializa aux com o início da lista.

            // Percorre a lista enquanto houver um próximo nó (aux->prox) e o valor do próximo nó não for igual a num.
            while (aux->prox && aux->prox->valor != num) {
                aux = aux->prox; // Avança para o próximo nó.
            }

            // Após o loop, verifica se o próximo nó existe (ou seja, se o valor foi encontrado).
            if (aux->prox) {
                // Armazena o nó a ser removido.
                remover = aux->prox;
                // Atualiza o ponteiro do nó atual (aux) para pular o nó removido.
                aux->prox = remover->prox;
            }
        }
    }

    // Retorna o nó removido (ou NULL se o nó não foi encontrado).
    return remover;
}
No* buscar(No **lista, int num) {
    No *aux, *no = NULL;
    aux = *lista;
    while (aux && aux ->valor != num) { //precorre a lista enquanto o prox nao for NULL
        aux = aux -> prox;
    }
    if (aux) {
        no = aux;
    }
    return no;
}

void imprimir(Lista lista) {
    No *no = lista.inicio;
    printf("\n\tLista: ");
    while (no) {
        printf("%d ", no -> valor);
        no = no -> prox;
    }
    printf("\n \n");
}

int main() {
    Lista lista; // Declara uma variável do tipo Lista
    int opcao, valor, referencia; // Variáveis para armazenar a opção do menu, valor e referência
    No *ajudador = NULL;
    // Inicializa a lista (inicio = NULL, tam = 0)
    criar_lista(&lista);

    // Loop do menu de opções
    do {
        // Menu de opções
        printf("\n--------------------------------------\n");
        printf("[1] Inserir no inicio\n");
        printf("[2] Inserir no fim\n");
        printf("[3] Inserir apos um valor\n");
        printf("[4] Inserir ordenado\n"); // Nova opção para inserir ordenado
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

            case 5:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                ajudador = remover(&lista, valor);
                if (ajudador) {
                    free(ajudador);
                }
                imprimir(lista);
                break;

            case 6:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                ajudador = buscar(&lista, valor);
            if (ajudador) {
                printf("Elemento encontrado: %d\n", ajudador -> valor);
            }else {
                printf("Elemento nao encontrado\n");
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
    } while (opcao != 6); // Repete o loop até que o usuário escolha sair (opção 6)

    // Liberar memória alocada para a lista (opcional, mas recomendado)
    No *atual = lista.inicio; // Ponteiro para percorrer a lista
    while (atual != NULL) {
        No *proximo = atual->prox; // Salva o próximo nó
        free(atual); // Libera o nó atual
        atual = proximo; // Avança para o próximo nó
    }
    return 0; // Fim do programa
}
