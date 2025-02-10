//
// Created by Guilherme Araújo on 10/02/2025.
//
//QUESTÃO 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    float nota;
    char nome[50];
    int faltas;
    struct no *prox;
    struct no *ante;
} No;
// typedef struct {
//     No cabeça;
//     int tam;
// }Lista;

// int remover(Lista *lista, char nome[]) {
//     No *remover = NULL; // Ponteiro para armazenar o nó a ser removido
//     if (lista) { // Verifica se a lista não é nula
//         No *aux = &lista->cabeça; // Inicializa o ponteiro auxiliar com a cabeça da lista
//         while (aux && strcmp(aux->nome, nome) != 0) { // Percorre a lista até encontrar o nó com o nome correspondente
//             aux = aux->prox; // Avança para o próximo nó
//         }
//         if (aux) { // Se encontrou o nó
//             remover = aux; // Armazena o nó a ser removido
//             if (remover->ante) { // Se o nó a ser removido não é o primeiro
//                 remover->ante->prox = remover->prox; // Atualiza o ponteiro 'prox' do nó anterior
//             } else { // Se o nó a ser removido é o primeiro
//                 lista->cabeça = *remover->prox; // Atualiza a cabeça da lista
//             }
//             if (remover->prox) { // Se o nó a ser removido não é o último
//                 remover->prox->ante = remover->ante; // Atualiza o ponteiro 'ante' do próximo nó
//             }
//             free(remover); // Libera a memória do nó removido
//             lista->tam--; // Decrementa o tamanho da lista
//             return 1; // Retorna 1 indicando que a remoção foi bem-sucedida
//         }
//     }
//     return 0; // Retorna 0 se o nó não foi encontrado ou a lista é nula
// }

int remover(No **lista, char nome[]) {
    No *aux, *remover = NULL; // Declara ponteiros auxiliares e inicializa 'remover' como NULL
    if (*lista) {
        if (strcmp((*lista)->nome, nome) == 0) {// Se o valor a ser removido está no início
            remover = *lista; // Armazena o nó a ser removido
            *lista = remover->prox;// Atualiza o início da lista para o próximo nó
            if (*lista) {// Se a lista não estiver vazia
                (*lista)->ante = NULL; // O anterior do novo início é NULL
            }
            return 1;
        }else {
            aux = *lista; // Inicializa 'aux' com o início da lista
            while (aux->prox && strcmp(aux->prox->nome, nome) !=0) {
                aux = aux->prox; // Percorre a lista até encontrar o nó a ser removido
            }
            if (aux->prox) {
                remover = aux->prox; // Armazena o nó a ser removido
                aux->prox = remover->prox;
                if (remover->prox) {
                    remover->prox->ante = aux; // Atualiza o ponteiro 'ante' do próximo nó
                }
                free(remover);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    No *lista = NULL;

    // Adiciona alguns nós à lista
    No *novo = malloc(sizeof(No));
    novo->nota = 7.5;
    strcpy(novo->nome, "Joao");
    novo->faltas = 2;
    novo->prox = lista;
    novo->ante = NULL;
    if (lista) lista->ante = novo;
    lista = novo;

    novo = malloc(sizeof(No));
    novo->nota = 8.0;
    strcpy(novo->nome, "Maria");
    novo->faltas = 1;
    novo->prox = lista;
    novo->ante = NULL;
    if (lista) lista->ante = novo;
    lista = novo;

    novo = malloc(sizeof(No));
    novo->nota = 6.5;
    strcpy(novo->nome, "Pedro");
    novo->faltas = 3;
    novo->prox = lista;
    novo->ante = NULL;
    if (lista) lista->ante = novo;
    lista = novo;

    // Imprime a lista de alunos
    printf("Lista de alunos:\n");
    No *aux = lista;
    while (aux) {
        printf("Nome: %s\nNota: %.2f\nFaltas: %d\n\n", aux->nome, aux->nota, aux->faltas);
        aux = aux->prox;
    }

    // Remove um aluno
    char nome[50];
    printf("Digite o nome do aluno a ser removido: ");
    scanf("%s", nome);
    if (remover(&lista, nome)) {
        printf("Aluno removido com sucesso!\n");
    } else {
        printf("Aluno não encontrado!\n");
    }

    // Imprime a lista de alunos atualizada
    printf("Lista de alunos atualizada:\n");
    aux = lista;
    while (aux) {
        printf("Nome: %s\nNota: %.2f\nFaltas: %d\n\n", aux->nome, aux->nota, aux->faltas);
        aux = aux->prox;
    }

    // Libera a memória alocada
    while (lista) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

    return 0;
}