cmake_minimum_required(VERSION 3.16)
project(Estrutura_de_Dados)

# Defina a versão da linguagem C usada
set(CMAKE_C_STANDARD 99)

# Adicione os executáveis para cada arquivo com `main()`

# Atividade 1
add_executable(questao1 atividade1/questao1.c)
add_executable(questao2 atividade1/questao2.c)
add_executable(questao3 atividade1/questao3.c)

# Atividade 2
add_executable(questao2_atividade2 atividade2/questaoe2.c)

# Testando busca e ordenação
add_executable(pesquisaBinaria testando_busca_e_ordenacao/pesquisaBinaria.c
        testando_busca_e_ordenacao/insertionPosition.c)
add_executable(remove testando_busca_e_ordenacao/removePosition.c)


# Outros exercícios
add_executable(exercicioProposto exercicio_proposto.c)
add_executable(lista_simplismente_encadeada Estudos/lista_simplesmente_encadeada.c)
