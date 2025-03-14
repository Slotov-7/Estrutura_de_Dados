// Bibliotecas necessárias
#include <stdio.h>      // Funções de entrada/saída, como printf e scanf.
#include <stdlib.h>     // Funções de alocação de memória, como malloc e free.
#include <string.h>     // Funções para manipulação de strings, como strlen, strcmp e strdup.

// Definição da estrutura do nó da árvore Patricia.
typedef struct No {
    char *chave;         // Ponteiro para a string que armazena a chave.
    int bit;             // Índice do bit que diferencia as chaves (para decidir o caminho).
    struct No *esq;      // Ponteiro para o filho à esquerda.
    struct No *dir;      // Ponteiro para o filho à direita.
} No;

// Função para extrair um bit específico da string.
// Exemplo: Se a chave for "ABC", para pos = 0 a função acessa o primeiro bit do 'A'.
int getBit(const char *chave, int pos, int len) {
    int byte = pos / 8;         // Determina qual byte contém o bit da posição.
    int bit = pos % 8;          // Determina a posição do bit dentro do byte.
    if (byte >= len) return 0;  // Se o índice do byte ultrapassar o tamanho da string, retorna 0.
    // Desloca os bits para a direita e "mask" para isolar o bit desejado.
    return (chave[byte] >> (7 - bit)) & 1;
}

// Função para criar um nó externo (folha) que contém uma chave.
// Exemplo: ao inserir "teste", um novo nó será criado e a string será copiada.
No* criarNoExterno(const char *chave) {
    No *novo = (No*)malloc(sizeof(No)); // Aloca memória para o novo nó.
    novo->chave = strdup(chave);          // Duplica a string para evitar modificações externas.
    novo->bit = -1;                       // Bit -1 indica que este é um nó externo (folha).
    novo->esq = novo->dir = NULL;         // Inicializa os ponteiros dos filhos como nulos.
    return novo;                          // Retorna o endereço do novo nó.
}

// Função para criar um nó interno, que não armazena chave, mas direciona a busca.
No* criarNoInterno(int bit, No *esq, No *dir) {
    No *novo = (No*)malloc(sizeof(No));  // Aloca memória para o nó.
    novo->chave = NULL;                   // Nós internos não armazenam chave.
    novo->bit = bit;                      // Armazena qual bit será usado para diferenciar os ramos.
    novo->esq = esq;                      // Define o filho à esquerda.
    novo->dir = dir;                      // Define o filho à direita.
    return novo;                          // Retorna o nó interno.
}

// Função recursiva para inserir uma nova chave na árvore Patricia.
// 'nivel' indica a posição atual do bit a ser comparado e 'len' é o comprimento da nova chave.
// Exemplo: Ao inserir "exemplo", a função compara os bits de "exemplo" com os armazenados.
No* inserir_rec(No *raiz, const char *chave, int nivel, int len) {
    if (raiz == NULL)
        return criarNoExterno(chave); // Se chegou em um nó vazio, cria um novo nó externo.

    if (raiz->bit == -1) {  // Se o nó atual é externo (folha)
        int i = nivel;
        int lenNo = (int)strlen(raiz->chave); // Calcula o tamanho da chave já presente.
        // Compara os bits da chave existente com os da nova chave até encontrar diferença.
        while (getBit(raiz->chave, i, lenNo) == getBit(chave, i, len))
            i++;
        // Cria um nó externo para a nova chave.
        No *novoNo = criarNoExterno(chave);
        /*
           Se o bit na posição 'i' da nova chave for 0, o novo nó fica à esquerda;
           caso contrário, à direita.
           Exemplo: se getBit(chave, i) retorna 0, então o endereço do nó novo será anexado
           ao ramo da esquerda.
        */
        if (getBit(chave, i, len) == 0)
            return criarNoInterno(i, novoNo, raiz);
        else
            return criarNoInterno(i, raiz, novoNo);
    }

    /*
       Se o nó é interno, utiliza o bit armazenado (raiz->bit) para decidir
       se a chave será inserida no ramo esquerdo ou direito.
       Exemplo: Se getBit(chave, raiz->bit, len)==0, a função é chamada recursivamente para o filho esquerdo.
    */
    if (getBit(chave, raiz->bit, len) == 0)
        raiz->esq = inserir_rec(raiz->esq, chave, raiz->bit + 1, len);
    else
        raiz->dir = inserir_rec(raiz->dir, chave, raiz->bit + 1, len);

    return raiz; // Retorna a raiz atualizada com a nova chave inserida.
}

// Função wrapper para inserção, que calcula o comprimento da chave uma única vez.
No* inserir(No *raiz, const char *chave) {
    int len = (int)strlen(chave);             // Calcula o tamanho da chave.
    return inserir_rec(raiz, chave, 0, len);    // Inicia a inserção recursiva a partir do nível 0.
}

// Função recursiva para buscar uma chave na árvore.
int buscar_rec(No *raiz, const char *chave, int len) {
    if (raiz == NULL)
        return 0; // Chave não encontrada se o nó é nulo.
    if (raiz->bit == -1)
        return strcmp(raiz->chave, chave) == 0; // Em nó externo, compara as chaves.
    // Decide qual ramo seguir com base no bit na posição indicada pelo nó interno.
    if (getBit(chave, raiz->bit, len) == 0)
        return buscar_rec(raiz->esq, chave, len);
    else
        return buscar_rec(raiz->dir, chave, len);
}

// Função wrapper para buscar, calculando o comprimento da chave primeiro.
int buscar(No *raiz, const char *chave) {
    int len = (int)strlen(chave);              // Calcula o tamanho da chave.
    return buscar_rec(raiz, chave, len);         // Inicia a busca recursiva.
}

// Função recursiva para remover uma chave na árvore.
No* remover_rec(No *raiz, const char *chave, int len) {
    if (raiz == NULL)
        return NULL; // Se o nó é nulo, não há nada para remover.
    if (raiz->bit == -1) {  // Se é um nó externo
        // Compara a chave do nó com a chave a ser removida.
        if (strcmp(raiz->chave, chave) == 0) {
            free(raiz->chave);   // Libera a memória alocada para a chave.
            free(raiz);          // Libera a memória do nó.
            return NULL;         // Retorna NULL para que o nó seja removido da árvore.
        }
        return raiz; // Se a chave não confere, retorna o nó sem alterações.
    }
    // Se o nó é interno, decide qual ramo seguir para procurar a chave.
    if (getBit(chave, raiz->bit, len) == 0)
        raiz->esq = remover_rec(raiz->esq, chave, len);
    else
        raiz->dir = remover_rec(raiz->dir, chave, len);

    /*
       Após a remoção, se um dos filhos é nulo, o nó interno pode ser eliminado,
       fazendo com que o outro filho ocupe seu lugar.
       Exemplo: Se raiz->esq == NULL e raiz->dir != NULL, o filho direito sobe.
    */
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
    return raiz; // Retorna o nó atualizado após a remoção.
}

// Função wrapper para remoção, calculando o comprimento da chave.
No* remover(No *raiz, const char *chave) {
    int len = (int)strlen(chave);               // Calcula o tamanho da chave.
    return remover_rec(raiz, chave, len);         // Inicia a remoção recursiva.
}

// Função para imprimir as chaves armazenadas na árvore em ordem (Inorder).
void imprimir(No *raiz) {
    if (raiz == NULL)
        return; // Se o nó é nulo, não imprime nada.
    imprimir(raiz->esq); // Imprime primeiro o ramo esquerdo.
    if (raiz->bit == -1)
        printf("  - %s\n", raiz->chave); // Se for nó externo, imprime a chave.
    imprimir(raiz->dir); // Imprime depois o ramo direito.
}

// Função para liberar toda a memória alocada na árvore.
void liberar(No *raiz) {
    if (raiz == NULL)
        return; // Se o nó é nulo, encerra a função.
    liberar(raiz->esq); // Libera recursivamente o ramo esquerdo.
    liberar(raiz->dir); // Libera recursivamente o ramo direito.
    if (raiz->chave)
        free(raiz->chave); // Libera a memória da chave, se existir.
    free(raiz); // Libera a memória do nó.
}

// Função para limpar o buffer de entrada.
// Exemplo: Após ler um número com scanf, caracteres extras podem permanecer; esta função os remove.
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função principal que apresenta um menu interativo para manipular a árvore Patricia.
int main(void) {
    No *raiz = NULL;              // Inicializa a árvore como vazia.
    char chave[50];               // Vetor para armazenar a chave (até 49 caracteres + '\0').
    int opcao;                    // Variável para armazenar a opção escolhida pelo usuário.

    printf("=== Arvore Patricia Interativa ===\n"); // Mensagem de abertura do programa.
    while (1) {  // Loop infinito para o menu.
        // Exibe as opções do menu.
        printf("\nEscolha uma opcao:\n");
        printf("1. Inserir chave\n");
        printf("2. Buscar chave\n");
        printf("3. Remover chave\n");
        printf("4. Imprimir todas as chaves\n");
        printf("5. Sair\nOpcao: ");

        // Lê a opção do usuário. Se a entrada for inválida, exibe uma mensagem e repete.
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Digite um numero.\n");
            limparBuffer(); // Limpa o buffer de entrada.
            continue;
        }
        limparBuffer(); // Limpa o buffer após ler a opção.
        if (opcao == 5)
            break;      // Se o usuário escolher sair, encerra o loop.

        // Para as opções que exigem a inserção de uma chave.
        if (opcao != 4) {
            printf("Digite a chave (max. 49 caracteres): ");
            fgets(chave, sizeof(chave), stdin);           // Lê a string do usuário.
            chave[strcspn(chave, "\n")] = '\0';             // Remove o caractere de nova linha.
        }

        // Estrutura de decisão para as diferentes opções do menu.
        switch (opcao) {
            case 1:
                raiz = inserir(raiz, chave);  // Insere a nova chave na árvore.
                printf("'%s' inserido na arvore.\n", chave);
                break;
            case 2:
                if (buscar(raiz, chave))
                    printf("'%s' encontrado na arvore.\n", chave);
                else
                    printf("'%s' nao encontrado.\n", chave);
                break;
            case 3:
                raiz = remover(raiz, chave);  // Remove a chave, se existir.
                printf("'%s' removido (se existia).\n", chave);
                break;
            case 4:
                printf("Chaves na arvore:\n");
                if (raiz == NULL)
                    printf("  (Arvore vazia)\n");
                else
                    imprimir(raiz);  // Imprime todas as chaves em ordem.
                break;
            default:
                printf("Opcao invalida! Escolha entre 1 e 5.\n"); // Trata opções inválidas.
        }
    }

    liberar(raiz); // Libera toda a memória alocada para a árvore.
    printf("\nArvore liberada. Programa encerrado.\n");
    return 0; // Termina o programa com retorno 0.
}
