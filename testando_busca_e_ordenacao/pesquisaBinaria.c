// Created by Guilherme Araújo on 16/01/2025.
#include <stdio.h>
#include <stdlib.h>
int qntElements = 0;
int max = 0;

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

void printList(const int* vector) {
    for (int i = 0; i < qntElements; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int binarySearch(const int* vector, int valueSought) {
    int begin = 0;
    int end = qntElements - 1;

    while (begin <= end) {
        int middle = (begin + end) / 2;

        if (vector[middle] == valueSought) {
            return middle;
        } else if (vector[middle] < valueSought) {
            begin = middle + 1;
        } else {
            end = middle - 1;
        }
    }
    return -1;
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

    int valueSought = 4;
    int result = binarySearch(vector, valueSought);

    if (result != -1) {
        printf("Value %d found at position %d\n", valueSought, result);
    } else {
        printf("Value %d not found in list \n", valueSought);
    }
    free(vector);
    return 0;
}
