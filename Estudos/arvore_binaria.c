#include <stddef.h>
//
// Created by Guilherme Araújo on 17/02/2025.
//
typedef struct no {
    int valor; // Valor armazenado no nó
    struct no *filhoEsq; // Ponteiro para o filho esquerdo
    struct no *filhoDir; // Ponteiro para o filho direito
} No;
typedef struct {
    No *raiz; // Ponteiro para a raiz da árvore
} Arvore;

// Função para criar uma árvore
