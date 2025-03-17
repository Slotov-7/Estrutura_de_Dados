// Bibliotecas necessárias
#include <stdio.h>      // Funções de entrada/saída, como printf e scanf.
#include <stdlib.h>     // Funções de alocação de memória, como malloc e free.
#include <string.h>     // Funções para manipulação de strings, como strlen, strcmp e strdup.

// Definição da estrutura do nó da árvore Patricia.
typedef struct No {
    char *chave;         // Ponteiro para a string que armazena a chave.
    int bit;             // Índice do bit utilizado para diferenciar os nós (-1 indica nó externo).
    struct No *esq;      // Ponteiro para o filho à esquerda.
    struct No *dir;      // Ponteiro para o filho à direita.
} No;

// Função para extrair um bit específico de uma string.
// Exemplo: Se a chave for "ABC", para pos = 0 acessa o primeiro bit do caractere 'A'.
int getBit(const char *chave, int pos, int len) {
    int byte = pos / 8;         // Determina qual byte contém o bit desejado.
    int bit = pos % 8;          // Determina a posição dentro do byte.
    if (byte >= len) return 0;  // Se ultrapassar o tamanho da chave, retorna 0.
    return (chave[byte] >> (7 - bit)) & 1; // Desloca os bits e isola o bit de interesse.
}

// Função para criar um nó externo (folha) com a chave fornecida.
// Exemplo: ao inserir "teste", um nó externo é criado e a string é duplicada.
No* criarNoExterno(const char *chave) {
    No *novo = (No*)malloc(sizeof(No));   // Aloca memória para o novo nó.
    novo->chave = strdup(chave);            // Duplica a chave para evitar alterações externas.
    novo->bit = -1;                         // -1 indica que este é um nó externo.
    novo->esq = novo->dir = NULL;           // Inicializa os ponteiros dos filhos.
    return novo;                            // Retorna o endereço do nó criado.
}

// Função para criar um nó interno, que não armazena chave e serve apenas para direcionamento.
No* criarNoInterno(int bit, No *esq, No *dir) {
    No *novo = (No*)malloc(sizeof(No));     // Aloca memória para o nó.
    novo->chave = NULL;                       // Nós internos não armazenam chave.
    novo->bit = bit;                          // Armazena o bit utilizado para diferenciar os ramos.
    novo->esq = esq;                          // Define o filho à esquerda.
    novo->dir = dir;                          // Define o filho à direita.
    return novo;                              // Retorna o nó interno criado.
}

/*
 * Função unificada de inserção na árvore Patricia.
 * Parâmetros:
 *   raiz  - nó atual (raiz da subárvore).
 *   chave - chave a ser inserida.
 *   nivel - nível atual do bit (comece com 0 na chamada inicial).
 *   len   - comprimento da chave (calculado previamente com strlen).
 *
 * Essa função é recursiva e trata tanto nós externos quanto internos.
 */
No* inserir(No *raiz, const char *chave, int nivel, int len) {
    if (raiz == NULL)
        return criarNoExterno(chave);      // Se a árvore estiver vazia, cria um novo nó externo.

    // Se chegou a um nó externo, comparar os bits para identificar o ponto de divergência.
    if (raiz->bit == -1) {
        int i = nivel;
        int lenNo = (int)strlen(raiz->chave); // Calcula o tamanho da chave existente.
        // Enquanto os bits da chave armazenada e da nova chave forem iguais, incrementa i.
        while (getBit(raiz->chave, i, lenNo) == getBit(chave, i, len))
            i++;
        // Cria um novo nó externo para a chave que está sendo inserida.
        No *novoNo = criarNoExterno(chave);
        // Verifica qual dos nós deve ficar à esquerda ou direita, conforme o bit divergente.
        if (getBit(chave, i, len) == 0)
            return criarNoInterno(i, novoNo, raiz);
        else
            return criarNoInterno(i, raiz, novoNo);
    }

    // Se estiver em nó interno, decide qual ramo seguir com base no bit armazenado.
    if (getBit(chave, raiz->bit, len) == 0)
        raiz->esq = inserir(raiz->esq, chave, raiz->bit + 1, len);
    else
        raiz->dir = inserir(raiz->dir, chave, raiz->bit + 1, len);

    return raiz; // Retorna a raiz atualizada.
}

/*
 * Função unificada de busca na árvore Patricia.
 * Parâmetros:
 *   raiz  - nó atual (raiz da subárvore).
 *   chave - chave a ser buscada.
 *   len   - comprimento da chave.
 *
 * Retorna 1 se encontrar a chave; caso contrário, 0.
 */
int buscar(No *raiz, const char *chave, int len) {
    if (raiz == NULL)
        return 0; // Retorna 0 se a árvore estiver vazia.
    if (raiz->bit == -1)
        return strcmp(raiz->chave, chave) == 0; // Em nó externo, compara as chaves.
    // Seleciona o ramo de acordo com o bit da chave.
    if (getBit(chave, raiz->bit, len) == 0)
        return buscar(raiz->esq, chave, len);
    else
        return buscar(raiz->dir, chave, len);
}

/*
 * Função unificada de remoção na árvore Patricia.
 * Parâmetros:
 *   raiz  - nó atual (raiz da subárvore).
 *   chave - chave a ser removida.
 *   len   - comprimento da chave.
 *
 * Retorna o nó atualizado após a remoção.
 */
No* remover(No *raiz, const char *chave, int len) {
    if (raiz == NULL)
        return NULL;  // Retorna NULL se a árvore estiver vazia.

    // Em nó externo, compara a chave e remove se for igual.
    if (raiz->bit == -1) {
        if (strcmp(raiz->chave, chave) == 0) {
            free(raiz->chave);  // Libera a memória da chave.
            free(raiz);         // Libera o nó.
            return NULL;        // Retorna NULL para retirar o nó da árvore.
        }
        return raiz;
    }
    // Em nó interno, percorre o ramo correto.
    if(getBit(chave, raiz->bit, len) == 0){
        raiz->esq = remover(raiz->esq, chave, len);
    }else {
        raiz->dir = remover(raiz->dir, chave, len);
    }
    // Se um dos ramos for nulo, elimina o nó interno e promove o outro ramo.
    if (raiz->esq == NULL && raiz->dir != NULL) {
        No *temp = raiz->dir;
        free(raiz);
        return temp;
    }
    if (raiz->dir == NULL && raiz->esq != NULL) {
        No *temp = raiz->esq;
        free(raiz);
        return temp;
    }
    return raiz; // Retorna a árvore atualizada.
}

// Função para imprimir a árvore Patricia (em ordem - Inorder).
void imprimir(No *raiz) {
    if (raiz == NULL)
        return; // Se o nó for nulo, retorna sem imprimir.
    imprimir(raiz->esq);               // Imprime o ramo esquerdo.
    if (raiz->bit == -1)
        printf("  - %s\n", raiz->chave); // Se for nó externo, imprime a chave.
    imprimir(raiz->dir);               // Imprime o ramo direito.
}

// Função para liberar toda a memória alocada na árvore.
void liberar(No *raiz) {
    if (raiz == NULL)
        return; // Caso o nó seja nulo, encerra.
    liberar(raiz->esq);              // Libera o ramo esquerdo.
    liberar(raiz->dir);              // Libera o ramo direito.
    if (raiz->chave)
        free(raiz->chave);           // Libera a memória da chave, se existir.
    free(raiz);                      // Libera o nó.
}

// Função para limpar o buffer de entrada.
// Exemplo: Após usar scanf, remove caracteres extras do buffer.
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal que apresenta um menu interativo para manipular a árvore Patricia.
int main(void) {
    No *raiz = NULL;               // Inicializa a árvore como vazia.
    char chave[50];                // Vetor para armazenar a chave (máximo de 49 caracteres + '\0').
    int opcao;                     // Variável para armazenar a opção escolhida.

    printf("=== Arvore Patricia Interativa ===\n");
    while (1) { // Loop infinito do menu.
        printf("\nEscolha uma opcao:\n");
        printf("1. Inserir chave\n");
        printf("2. Buscar chave\n");
        printf("3. Remover chave\n");
        printf("4. Imprimir todas as chaves\n");
        printf("5. Sair\nOpcao: ");

        if (scanf("%d", &opcao) != 1) { // Lê a opção
            printf("Entrada invalida! Digite um numero.\n");
            limparBuffer();          // Limpa o buffer de entrada
            continue;
        }
        limparBuffer();              // Limpa o buffer de entrada após ler a opção.
        if (opcao == 5)
            break;                   // Encerra o loop se o usuário escolher sair.

        // Para as opções que necessitam a chave.
        if (opcao != 4) {
            printf("Digite a chave (max. 49 caracteres): ");
            fgets(chave, sizeof(chave), stdin);             // Lê a chave do usuário.
            chave[strcspn(chave, "\n")] = '\0';               // Remove o caractere '\n'.
        }

        switch (opcao) {
            case 1:
                // Calcula o comprimento da chave e insere com nível 0.
                raiz = inserir(raiz, chave, 0, (int)strlen(chave));
                printf("'%s' inserido na arvore.\n", chave);
                break;
            case 2:
                if (buscar(raiz, chave, (int)strlen(chave)))
                    printf("'%s' encontrado na arvore.\n", chave);
                else
                    printf("'%s' nao encontrado.\n", chave);
                break;
            case 3:
                raiz = remover(raiz, chave, (int)strlen(chave));
                printf("'%s' removido (se existia).\n", chave);
                break;
            case 4:
                printf("Chaves na arvore:\n");
                if (raiz == NULL)
                    printf("  (Arvore vazia)\n");
                else
                    imprimir(raiz);
                break;
            default:
                printf("Opcao invalida! Escolha entre 1 e 5.\n");
        }
    }

    liberar(raiz); // Libera a memória da árvore.
    printf("\nArvore liberada. Programa encerrado.\n");
    return 0;
}