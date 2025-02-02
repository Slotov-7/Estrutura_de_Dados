//
// Created by Guilherme Araújo on 09/12/2024.
//
/*Crie um struct que guarde nome, idade e peso um atletas. Em um
vetor, alocado dinamicamente, guarde os dados de N atletas. Exiba uma
listagem dos dados dos atletas cadastrados. Ao final exiba a média dos
pesos e quantos atletas são menores de idade.*/

#include <stdio.h>
#include <stdlib.h>
struct Atleta {
    char nome[15];
    int idade;
    float peso;
};
int main() {
    int num;
    printf("qual a quantidade de atletas?");
    scanf("%d", &num);
    struct Atleta *atletas = (struct Atleta *)malloc(num * sizeof(struct Atleta));
    if (!atletas) { // Verifica se a alocação falhou
        printf("Erro ao alocar memória.\n");
        return;
    }

    for (int i = 0; i < num; ++i) {
        printf("Digite os dados do atleta %d\n", i + 1);
        printf("Digite o nome: \n");
        scanf(" %[^\n]", &atletas[i].nome);
        printf("Digite a idade: \n");
        scanf("%d", &atletas[i].idade);
        printf("Digite o peso: \n");
        scanf("%f", &atletas[i].peso);
    }
    int menor_idade = 0;
    float sump = 0;
    for (int i = 0; i < num; i++) {
        if (atletas[i].idade < 18) {
            menor_idade++;
        }
        sump += atletas[i].peso;
    }
    printf("\n--- Dados dos Atletas ---\n");
    for (int i = 0; i < num; i++) {
        printf("Atleta %d: Nome: %s, Idade: %d, Peso: %.2f\n",
               i + 1, atletas[i].nome, atletas[i].idade, atletas[i].peso);
    }

    printf("\nMedia = %.2f", (double) sump/num);
    printf("\nQuantidade de atletas menores de idade e igual a %d", menor_idade);

    free(atletas);
    return 0;

}
