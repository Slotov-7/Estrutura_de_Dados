// Created by Guilherme Araújo on 05/12/2024.

/*Declare 2 variáveis inteiras e dois ponteiros para inteiros que devem ser associados ao endereço
 das variáveis. Usando somente os ponteiros faça com que as variáveis recebam o dobro e o triplo de
 repectivamente*/
#include <stdio.h>

int main() {
    int num1 = 10;
    int *ptr1 = &num1;
    int num2 = 5;
    int *ptr2 = &num2;

    printf("Valor original do num1: %d\n", *ptr1);
    printf("Valor original do num2: %d\n", *ptr2);

    *ptr1 = *ptr1 * 2;
    *ptr2 = *ptr2 * 3;

    printf("Valor apos multiplicacao o num1: %d\n", *ptr1);
    printf("Valor de 'num1': %d\n", num1);

    printf("Valor apos multiplicacao o num2: %d\n", *ptr2);
    printf("Valor de 'num2': %d\n", num2);
    return 0;
}
