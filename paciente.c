#include "paciente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Paciente criar_paciente(const char* nome, int idade, int gravidade, int tipo_atendimento) {
    Paciente paciente;
    // Aloca memória para o nome do paciente;
    paciente.nome = malloc(strlen(nome) + 1);
    // Aqui verificamos se a alocação de memória foi bem-sucedida;
    if (paciente.nome == NULL) {
        // Se a alocação falhar, imprimimos uma mensagem de erro e encerramos o programa;
        printf("Erro ao alocar memória para o nome do paciente\n");
        exit(EXIT_FAILURE); // -- Exit_Failure é uma macro definida em stdlib.h que indica que o programa terminou com um erro (ou seja, retornou 1);
    }
    //
    // agora é so preencher os dados do paciente e retornar a estrutura preenchida;
    //
    strcpy(paciente.nome, nome); // -- Copia a string do nome para a memória alocada;
    paciente.idade = idade;
    paciente.gravidade = gravidade;
    paciente.tipo_atendimento = tipo_atendimento;
    return paciente;
}