#include "paciente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Paciente criar_paciente(const char *nome, int idade, int gravidade, int tipo_atendimento, const char *cpf)
{
    Paciente paciente;
    paciente.nome = malloc(strlen(nome) + 1);
    if (paciente.nome == NULL)
    {
        printf("Erro ao alocar memoria para o nome do paciente\n");
        exit(EXIT_FAILURE);
    }
    paciente.CPF = malloc(strlen(cpf) + 1);
    if (paciente.CPF == NULL)
    {
        printf("Erro ao alocar memoria para o CPF do paciente\n");
        exit(EXIT_FAILURE);
    }
    strcpy(paciente.nome, nome);
    strcpy(paciente.CPF, cpf);

        paciente.idade = idade;
        paciente.gravidade = gravidade;
        paciente.tipo_atendimento = tipo_atendimento;
        return paciente;
    }