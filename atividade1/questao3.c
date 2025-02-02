//
// Created by Guilherme Araújo on 09/12/2024.
//
/*Construa um programa que armazene nome, matrícula e média de
até N alunos e dê ao usuário a possibilidade de ver a listagem dos
alunos em ordem alfabética ou em ordem de classificação. Obs: uma
vez que os dados sejam digitados, o usuário deve poder ver as listagens
quantas vezes ele desejar.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno {
    char nome[15];
    int matricula;
    float media;
};
int main() {
    int num;
    printf("qual a quantidade de alunos?");
    scanf("%d", &num);
    struct Aluno *alunos = (struct Aluno *)malloc(num * sizeof(struct Aluno));
    if (!alunos) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    for (int i = 0; i < num; ++i) {
        printf("Digite os dados do aluno %d\n", i + 1);
        printf("Digite o nome: \n");
        scanf(" %[^\n]", &alunos[i].nome);
        printf("Digite a idade: \n");
        scanf("%d", &alunos[i].matricula);
        printf("Digite o media: \n");
        scanf("%f", &alunos[i].media);
    }
    int opcao;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Exibir alunos em ordem alfabetica\n");
        printf("2. Exibir alunos em ordem de classificacao\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            for (int i = 0; i < num - 1; i++) {
                for (int j = i + 1; j < num; j++) {
                    if (strcmp(alunos[i].nome, alunos[j].nome) > 0) {
                        struct Aluno temp = alunos[i];
                        alunos[i] = alunos[j];
                        alunos[j] = temp;
                    }
                }
            }


            printf("\n--- Lista de Alunos (Ordem Alfabetica) ---\n");
            for (int i = 0; i < num; i++) {
                printf("Nome: %s, Matricula: %d, Média: %.2f\n",
                       alunos[i].nome, alunos[i].matricula, alunos[i].media);
            }
        } else if (opcao == 2) {
            for (int i = 0; i < num - 1; i++) {
                for (int j = i + 1; j < num; j++) {
                    if (alunos[i].media < alunos[j].media) {
                        struct Aluno temp = alunos[i];
                        alunos[i] = alunos[j];
                        alunos[j] = temp;
                    }
                }
            }

            // Exibir alunos ordenados por média
            printf("\n--- Lista de Alunos (Ordem de Classificacao) ---\n");
            for (int i = 0; i < num; i++) {
                printf("Nome: %s, Matrícula: %d, Média: %.2f\n",
                       alunos[i].nome, alunos[i].matricula, alunos[i].media);
            }
        } else if (opcao == 3) {
            printf("Saindo...\n");
        } else {
            printf("Opção invalida! Tente novamente.\n");
        }
    } while (opcao != 3);

    free(alunos);
    return 0;
}


