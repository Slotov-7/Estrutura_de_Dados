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
// Função para imprimir a árvore em pós-ordem
void imprimir_arvore_pos_ordem(No *raiz) {
    if (raiz) { // Se o nó não é NULL
        imprimir_arvore_pos_ordem(raiz->filhoEsq); // Imprime o filho esquerdo em pré-ordem
        imprimir_arvore_pos_ordem(raiz->filhoDir); // Imprime o filho direito em pré-ordem
        printf("%d ", raiz->valor); // Imprime o valor do nó
    }
}

No* buscar_1(No *raiz, int valor) {// Busca um valor na árvore
    if (raiz) {// Se a árvore não está vazia
        if (valor == raiz->valor) {// Se o valor é igual ao valor do nó atual
            return raiz;// Retorna o nó atual
        }
        if(valor < raiz->valor) {// Se o valor é menor que o valor do nó atual
            return buscar_1(raiz->filhoEsq, valor);// Busca no filho esquerdo
        }
            return buscar_1(raiz->filhoDir, valor);// Busca no filho direito
    }
    return NULL;// Retorna NULL se a árvore está vazia
}

No* buscar_2(No *raiz, int valor) {// Busca um valor na árvore
    if (raiz) {// Se a árvore não está vazia
        while (raiz) {// Enquanto não chegar ao final da árvore
            if (valor < raiz->valor) {// Se o valor é menor que o valor do nó atual
                raiz = raiz->filhoEsq;// Move para o filho esquerdo
            }else if (valor > raiz->valor) {// Se o valor é maior que o valor do nó atual
                raiz = raiz->filhoEsq;// Move para o filho direito
            }else {// Se o valor é igual ao valor do nó atual
                return raiz;// Retorna o nó atual
            }
        }
    }
    return NULL;// Retorna NULL se a árvore está vazia
}

int calcular_altura(No *raiz) {
    if (raiz == NULL) {// Se a árvore está vazia
        return -1;// Retorna -1
    }else {// Se a árvore não está vazia
        int esq = calcular_altura(raiz->filhoEsq);// Calcula a altura do filho esquerdo
        int dir = calcular_altura(raiz->filhoDir);// Calcula a altura do filho direito
        if (esq > dir) {// Se a altura do filho esquerdo é maior que a do filho direito
            return esq + 1;// Retorna a altura do filho esquerdo + 1
        }else {// Se a altura do filho direito é maior que a do filho esquerdo
            return dir + 1;// Retorna a altura do filho direito + 1
        }
    }
}
int calcular_nos(No *raiz) {// Calcula o número de nós da árvore
    if (raiz == NULL) {// Se a árvore está vazia
        return 0;// Retorna 0
    }else {// Se a árvore não está vazia
        return calcular_nos(raiz->filhoEsq) + calcular_nos(raiz->filhoDir) + 1;// Retorna o número de nós do filho esquerdo + o número de nós do filho direito + 1
    }
    // return (raiz == NULL)? 0 : calcular_nos(raiz->filhoEsq) + calcular_nos(raiz->filhoDir) + 1;// Retorna 0 se a árvore está vazia, senão retorna o número de nós do filho esquerdo + o número de nós do filho direito + 1
}
int calcular_folhas(No *raiz) {
    if (raiz == NULL) {
        return 0;
    }
    else if(raiz->filhoEsq == NULL && raiz->filhoDir == NULL) {
        return 1;
    }else {
        return  calcular_folhas(raiz->filhoDir) + calcular_folhas( raiz->filhoEsq);
    }
}

//funcao para remover o nó folha de uma arcore binária

No* remover(No *raiz, int valor) {
    if (raiz == NULL) {
        printf("Erro ao remver\n");
        return NULL;
    }else {
        if (raiz->valor == valor) {
            if (raiz->filhoEsq == NULL && raiz->filhoDir == NULL) {
                free(raiz);
                printf("elemento folha removido: %d\n", valor);
                return NULL;
            }else {
                //remover nos com 1 ou 2 filhos
                if (raiz->filhoEsq != NULL && raiz->filhoDir != NULL) {//

                }else {//remover nó com 1 filho
                    No *aux = raiz->filhoEsq != NULL ? raiz->filhoEsq : raiz->filhoDir;
                    free(raiz);
                    printf("elemento com um filho removido: %d\n", valor);
                    return aux;
                }
            }
        }else {
            if (valor < raiz->valor) {
                raiz->filhoEsq = remover(raiz->filhoEsq, valor);
            }else {
                raiz->filhoDir = remover(raiz->filhoDir, valor);
            }
            return raiz;
        }
    }
}

// Função principal
int main() {
    No *busca, *raiz = NULL; // Inicializa a árvore como vazia
    int opcao, valor; // Variáveis para armazenar a opção do menu e o valor a ser inserido

    inserir_2(&raiz, 50);
    inserir_2(&raiz, 30);
    inserir_2(&raiz, 25);
    inserir_2(&raiz, 35);
    inserir_2(&raiz, 60);
    inserir_2(&raiz, 75);
    inserir_2(&raiz, 70);
    inserir_2(&raiz, 80);


    imprimir_arvore_in_ordem(raiz);
    printf("\n");
    imprimir_arvore_pos_ordem(raiz);


    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}