//
// Created by Guilherme Araújo on 19/01/2025.
//
// Implementar Remoção em posição, considerando que a lista esteja ordenada
#include <stdio.h>
#include <stdlib.h>
int qntElements = 0;
int max = 0;
void printList(const int* vector) {
    for (int i = 0; i < qntElements; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int* createList(const int* initialValues) {
    int* vector = malloc(qntElements * sizeof(int));  // Aloca memória para o vetor
    if (!vector) {  // Verifica se a alocação foi bem-sucedida
        printf("Memory allocation error\n");
        exit(1);
    }
    for (int i = 0; i < qntElements; i++) {
        vector[i] = initialValues[i];
    }
    return vector;
}
void organizer(int* vector) {
    for (int i = 0; i < qntElements - 1; i++) {
        for (int j = i + 1; j < qntElements; j++) {
            if (vector[j] < vector[i]) {
                int aux = vector[j];
                vector[j] = vector[i];
                vector[i] = aux;
            }
        }
    }
}

int orderedRemovalPosition(int *vector, int position) {
    if (position >= 0 && position < qntElements) {//verifica se a posição é válida
        for (int i = position; i < qntElements - 1; i++) {
            vector[i] = vector[i + 1];//move os elementos para a esquerda
        }
        qntElements--;//diminui a quantidade de elementos
        return 1;//retorna 1 se a remoção foi bem sucedida
    }
    return 0;//retorna 0 se a remoção não foi bem sucedida
}
int main() {
    max = 10;
    int initialValues[] = {12, 37, 5, 44, 29, 3, 18, 21, 9, 50};
    qntElements = sizeof(initialValues) / sizeof(initialValues[0]);
    // Criação da lista
    int* vector = createList(initialValues);

    printf("Initial list:\n");
    printList(vector);

    // Ordenar a lista
    organizer(vector);
    printf("\nOrdered list:\n");
    printList(vector);

    int position = 10;

    if (orderedRemovalPosition(vector, position)) {
        printf("\nLList with element at position %d removed :\n", position);
        printList(vector);
    }else {
        printf("removal not performed\n");
    }


    free(vector);
    return 0;
}
