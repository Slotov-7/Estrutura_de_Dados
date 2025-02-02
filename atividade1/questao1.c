//
// Created by Guilherme Araújo on 09/12/2024.
//
/*Guarde N números em um vetor alocado dinamicamente. Exiba a
média dos números lidos e os múltiplos de 6 digitados.*/

#include <stdio.h>
#include <stdlib.h>

void main() {
    int num, sum =0;
    printf("qual o tamanho do vetor?");
    scanf("%d", &num);
    int *vet = (int *) calloc(num, sizeof(int));
    if (!vet) {
        printf("Memoria nao alocada. \nEncerrando programa...");
        return;
    }

    printf("Informe os valores do vetor:\n");
    for (int i = 0; i < num; i++) {
        printf("Digite o valor: \n");
        scanf("%d", &vet[i]);
        sum += vet[i];
    }
    printf("Os multiplos de 6 sao:");
    for (int i = 0; i < num; i++) {
        if (vet[i] % 6 == 0) {
            printf("\n%d ", vet[i]);
        }
    }
    printf("\n Media = %.2f", (double) sum/num);
    free(vet);
}
