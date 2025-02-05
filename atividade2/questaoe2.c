//
// Created by Guilherme Araújo on 28/12/2024.
//
#include <stdio.h>
int somador(int n) {
    int sum = 0;
    int i = 1;
    while (i <= n) {
        sum+=i;
        i++;
    }
    return sum;
}

int main() {
    printf("Soma = %d\n", somador(8));
    return 0;
}


