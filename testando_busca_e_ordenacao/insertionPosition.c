//
// Created by Guilherme Araújo on 19/01/2025.
//
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
int unorderedInsertionPosition(int *vector, int position, int value) {
    if (position >= 0 && position < qntElements) {//verifica se a posição é válida
        for (int i = qntElements; i > position; i--) {
            vector[i] = vector[i - 1];//move os elementos para a direita
        }
        vector[position] = value;//insere o valor na posição
        qntElements++;//aumenta a quantidade de elementos
        return 1;//retorna 1 se a inserção foi bem sucedida
    }
    return 0;//retorna 0 se a inserção não foi bem sucedida
}
int main() {
    max = 10;
    int initialValues[] = {12, 37, 5, 44, 29, 3, 18, 21, 9, 50};
    qntElements = sizeof(initialValues) / sizeof(initialValues[0]);
    // Criação da lista
    int* vector = createList(initialValues);

    printf("Initial list:\n");
    printList(vector);

    // Inserir um valor na posição 3
    int value = 100;
    int position = 7;
    if (unorderedInsertionPosition(vector, position, value)) {
        printf("List after inserting value %d at position %d:\n", value, position);
        printList(vector);
    } else {
        printf("Insertion not performed\n");
    }
    free(vector);
    return 0;
}