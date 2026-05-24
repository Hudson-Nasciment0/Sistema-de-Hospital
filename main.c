#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "packages\paciente.h"
#include "packages\Utils.h"
#include "packages\Consulta.h"
#include "packages\Exame.h"
#include "packages\Emergencia.h"

Emergencia *Pilha_Emergencia;
Consulta *Fila_Consulta;
Exame *Fila_Exame_Circular;

void segurar_leitor()
{
    printf("\n\nPressione qualquer tecla para prosseguir...");
    getchar();
    getchar();
}

Emergencia *Criar_Pilha_Emergencia()
{
    Emergencia *e = (Emergencia *)malloc(sizeof(Emergencia));

    if (e == NULL)
    {
        printf("\nNao foi possivel alocar memoria para a Pilha Emergencia\n");
        segurar_leitor();
        exit(EXIT_FAILURE);
    }

    e->total_pacientes = 0;

    return e;
}

Consulta *Criar_Fila_Consulta()
{
    Consulta *c = (Consulta *)malloc(sizeof(Consulta));

    if (c == NULL)
    {
        printf("\nNao foi possivel alocar memoria para a Fila Consulta\n");
        segurar_leitor();
        exit(EXIT_FAILURE);
    }

    c->total_pacientes = 0;

    return c;
}

Exame *Criar_Fila_Exame()
{
    Exame *e = (Exame *)malloc(sizeof(Exame));

    if (e == NULL)
    {
        printf("\nNao foi possivel alocar memoria para a Fila Exame\n");
        segurar_leitor();
        exit(EXIT_FAILURE);
    }

    e->index_inicio = 0;
    e->total_pacientes = 0;

    return e;
}

void limpar_tela()
{
    system("cls");
}

//
// Limpa o buffer de entrada para não causar um "Enter" acidental
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



void Cadastrar_Emergencia(Paciente paciente)
{
    if (Pilha_Emergencia->total_pacientes == MAX_EMERGENCIA)
    {
        printf("Pilha de Emergencia Cheia. nao e possivel adicionar mais pacientes!\n");
        return;
    }

    int index = Pilha_Emergencia->total_pacientes;

    Pilha_Emergencia->Pacientes[index] = paciente;

    Pilha_Emergencia->total_pacientes++;
    //
    printf("Cadastrado Paciente %s na Pilha de Emergencia na posicao [%d]\n",
           paciente.nome,
           index + 1);
}

void Cadastrar_Consulta(Paciente paciente)
{
    if (Fila_Consulta->total_pacientes == MAX_CONSULTA)
    {
        printf("Fila de consulta Cheia. nao e possivel adicionar mais pacientes!");
        return;
    }

    int index = Fila_Consulta->total_pacientes;

    Fila_Consulta->Pacientes[index] = paciente;

    Fila_Consulta->total_pacientes++;
    //
    printf("Cadastrado Paciente %s na fila de Consulta na posicao [%d]\n",
           paciente.nome,
           index + 1);
}

void Cadastrar_Exame(Paciente paciente)
{
    if (Fila_Exame_Circular->total_pacientes == MAX_EXAME)
    {
        printf("Fila de Exame Cheia. nao e possivel adicionar mais pacientes!");
        return;
    }

    int total_exame = Fila_Exame_Circular->total_pacientes;

    int index_inicio = Fila_Exame_Circular->index_inicio;

    int posicao_insercao = (index_inicio + total_exame) % MAX_EXAME;

    Fila_Exame_Circular->Pacientes[posicao_insercao] = paciente;

    Fila_Exame_Circular->total_pacientes++;

    printf("Cadastrado Paciente %s na fila de exame na posicao [%d]\n",
           paciente.nome,
           posicao_insercao + 1);
}

void Cadastrar_Paciente()
{
    limpar_tela();
    limparBuffer();
    
    printf("\nBem vindo ao Cadastro de Paciente\n");
    char nome_temp[100];
    char cpf_temp[100];

    int idade_temp;
    int gravidade_temp;
    int tipo_temp;
    //

    printf("\nDigite o nome do Paciente: ");
    //
    fgets(nome_temp, sizeof(nome_temp), stdin);
    nome_temp[strcspn(nome_temp, "\n")] = 0;
    //
    //
    printf("\nDigite o CPF do Paciente: ");
    //
    fgets(cpf_temp, sizeof(cpf_temp), stdin);
    cpf_temp[strcspn(cpf_temp, "\n")] = 0;
    //
    printf("\nDigite a idade do Paciente: ");
    scanf("%d", &idade_temp);
    //
    printf("\nGravidade (1-5): ");
    scanf("%d", &gravidade_temp);
    //
    if (gravidade_temp < 4)
    {
        printf("\nTipo (1-Emergencia, 2-Consulta, 3-Exame): ");

        scanf("%d", &tipo_temp);
    }
    else
    {
        tipo_temp = 1;
    }
    //
    Paciente paciente = criar_paciente(
        nome_temp,
        idade_temp,
        gravidade_temp,
        tipo_temp,
        cpf_temp);
    //
    if (paciente.tipo_atendimento == 1)
    {
        Cadastrar_Emergencia(paciente);
    }
    else if (paciente.tipo_atendimento == 2)
    {
        Cadastrar_Consulta(paciente);
    }
    else if (paciente.tipo_atendimento == 3)
    {
        Cadastrar_Exame(paciente);
    }

    segurar_leitor();
}

void Atender_Pilha_Emergencia()
{
    limpar_tela();

    if (Pilha_Emergencia->total_pacientes == 0)
    {
        printf("\nO Setor de Emergencia nao possui pacientes!\n\n");
        segurar_leitor();
        return;
    }

    int index = Pilha_Emergencia->total_pacientes;

    Paciente paciente = Pilha_Emergencia->Pacientes[index - 1];

    printf("\nRealizando Atendimento do Paciente: %s, no setor de EMERGENCIA\n",
           paciente.nome);

    Pilha_Emergencia->total_pacientes--;

    free(paciente.nome);
    free(paciente.CPF);

    segurar_leitor();
}

void Atender_Fila_Consulta()
{
    limpar_tela();

    if (Fila_Consulta->total_pacientes == 0)
    {
        printf("\nO Setor de Consulta nao possui pacientes!\n\n");
        segurar_leitor();
        return;
    }

    Paciente paciente = Fila_Consulta->Pacientes[0];

    printf("\nRealizando Atendimento do Paciente: %s, no setor de CONSULTA\n",
           paciente.nome);

    for (int i = 0; i < Fila_Consulta->total_pacientes; i++)
    {
        if (i > 0)
        {
            Fila_Consulta->Pacientes[i - 1] = Fila_Consulta->Pacientes[i];
        }
    }

    Fila_Consulta->total_pacientes--;

    free(paciente.nome);
    free(paciente.CPF);

    segurar_leitor();
}

void Atender_Fila_Exame_Circular()
{
    limpar_tela();

    if (Fila_Exame_Circular->total_pacientes == 0)
    {
        printf("\nO Setor de Exames nao possui pacientes!\n\n");
        segurar_leitor();
        return;
    }

    int index_inicio = Fila_Exame_Circular->index_inicio;

    Paciente paciente = Fila_Exame_Circular->Pacientes[index_inicio];

    printf("\nRealizando Atendimento do Paciente: %s, no setor de EXAME\n",
           paciente.nome);

    Fila_Exame_Circular->index_inicio =
        (index_inicio + 1) % MAX_EXAME;

    Fila_Exame_Circular->total_pacientes--;

    free(paciente.nome);
    free(paciente.CPF);

    segurar_leitor();
}

void RealizarTesteEstresse()
{
    limpar_tela();

    printf("\nIniciando Teste de estresse...\n");

    clock_t inicio = clock();

    int testes_realizados = 0;

    for (int i = 0; i < MAX_STRESS_TEST; i++)
    {
        char nome[50];
        char cpf[30];

        sprintf(nome, "Paciente_%d", i + 1);

        sprintf(cpf, "000.000.000-%02d", i % 100);

        int idade = (i % 90) + 1;

        int gravidade = (i % 5) + 1;

        int tipo_atendimento = (i % 3) + 1;

        Paciente paciente = criar_paciente(
            nome,
            idade,
            gravidade,
            tipo_atendimento,
            cpf);

        if (tipo_atendimento == 1)
        {
            if (Pilha_Emergencia->total_pacientes < MAX_EMERGENCIA)
            {
                Cadastrar_Emergencia(paciente);
            }
        }
        else if (tipo_atendimento == 2)
        {
            if (Fila_Consulta->total_pacientes < MAX_CONSULTA)
            {
                Cadastrar_Consulta(paciente);
            }
        }
        else
        {
            if (Fila_Exame_Circular->total_pacientes < MAX_EXAME)
            {
                Cadastrar_Exame(paciente);
            }
        }
        testes_realizados++;
    }

    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nTeste finalizado.\n");

    printf("Foram feitas %d tentativas de cadastro.\n", testes_realizados);

    printf("\nPacientes na Emergencia: %d",
           Pilha_Emergencia->total_pacientes);

    printf("\nPacientes na Consulta: %d",
           Fila_Consulta->total_pacientes);

    printf("\nPacientes no Exame: %d",
           Fila_Exame_Circular->total_pacientes);

    printf("\nTempo de execucao: %.4f segundos\n", tempo);

    segurar_leitor();
}

void Atender_Paciente_Nos_Setores()
{
    Atender_Pilha_Emergencia();

    Atender_Fila_Consulta();

    Atender_Fila_Exame_Circular();
}

void Mostrar_Pacientes()
{
    limpar_tela();

    printf("---EXIBINDO PACIENTES DO HOSPITAL-----\n");

    printf("\n---EMERGENCIA---\n");

    if (Pilha_Emergencia->total_pacientes > 0)
    {
        for (int i = 0; i < Pilha_Emergencia->total_pacientes; i++)
        {
            Paciente p = Pilha_Emergencia->Pacientes[i];

            printf("Paciente: %s, Fila: [%d], CPF: %s ,Idade: %d, Gravidade: %d, Tipo de Atendimento: EMERGENCIA (%d)\n",
                   p.nome,
                   i,
                   p.CPF,
                   p.idade,
                   p.gravidade,
                   p.tipo_atendimento);
        }
    }
    else
    {
        printf("\nSetor de EMERGENCIA Vazio!\n");
    }

    printf("\n---CONSULTA---\n");

    if (Fila_Consulta->total_pacientes > 0)
    {
        for (int i = 0; i < Fila_Consulta->total_pacientes; i++)
        {
            Paciente p = Fila_Consulta->Pacientes[i];

            printf("Paciente: %s, Fila: [%d], CPF: %s ,Idade: %d, Gravidade: %d, Tipo de Atendimento: CONSULTA (%d)\n",
                   p.nome,
                   i,
                   p.CPF,
                   p.idade,
                   p.gravidade,
                   p.tipo_atendimento);
        }
    }
    else
    {
        printf("\nSetor de CONSULTA Vazio!\n");
    }

    printf("\n---EXAME---\n");

    if (Fila_Exame_Circular->total_pacientes > 0)
    {
        for (int i = 0; i < Fila_Exame_Circular->total_pacientes; i++)
        {
            int pos =
                (Fila_Exame_Circular->index_inicio + i) % MAX_EXAME;

            Paciente p =
                Fila_Exame_Circular->Pacientes[pos];

            printf("Paciente: %s, Fila: [%d], CPF: %s ,Idade: %d, Gravidade: %d, Tipo de Atendimento: EXAME (%d)\n",
                   p.nome,
                   i,
                   p.CPF,
                   p.idade,
                   p.gravidade,
                   p.tipo_atendimento);
        }
    }
    else
    {
        printf("\nSetor de EXAME Vazio!\n");
    }

    segurar_leitor();
}

void Transferir_Paciente()
{
    int origem;
    int destino;

    Paciente paciente;

    printf("\n===== TRANSFERIR PACIENTE =====\n");

    printf("Origem: 1-Emergencia | 2-Consulta | 3-Exame: ");

    scanf("%d", &origem);

    printf("Destino: 1-Emergencia | 2-Consulta | 3-Exame: ");

    scanf("%d", &destino);

    getchar();

    if (origem == destino)
    {
        printf("Origem e destino nao podem ser iguais!\n");

        segurar_leitor();

        return;
    }

    if (origem == 1)
    {
        if (Pilha_Emergencia->total_pacientes == 0)
        {
            printf("Emergencia vazia!\n");

            segurar_leitor();

            return;
        }

        int index = Pilha_Emergencia->total_pacientes - 1;

        paciente = Pilha_Emergencia->Pacientes[index];

        Pilha_Emergencia->total_pacientes--;
    }
    else if (origem == 2)
    {
        if (Fila_Consulta->total_pacientes == 0)
        {
            printf("Consulta vazia!\n");

            segurar_leitor();

            return;
        }

        paciente = Fila_Consulta->Pacientes[0];

        for (int i = 1; i < Fila_Consulta->total_pacientes; i++)
        {
            Fila_Consulta->Pacientes[i - 1] =
                Fila_Consulta->Pacientes[i];
        }

        Fila_Consulta->total_pacientes--;
    }
    else if (origem == 3)
    {
        if (Fila_Exame_Circular->total_pacientes == 0)
        {
            printf("Exame vazio!\n");

            segurar_leitor();

            return;
        }

        int index_inicio =
            Fila_Exame_Circular->index_inicio;

        paciente =
            Fila_Exame_Circular->Pacientes[index_inicio];

        Fila_Exame_Circular->index_inicio =
            (index_inicio + 1) % MAX_EXAME;

        Fila_Exame_Circular->total_pacientes--;
    }
    else
    {
        printf("Setor de origem invalido!\n");

        segurar_leitor();

        return;
    }

    if (destino == 1)
    {
        if (Pilha_Emergencia->total_pacientes ==
            MAX_EMERGENCIA)
        {
            printf("Emergencia cheia!\n");

            segurar_leitor();

            return;
        }

        int index = Pilha_Emergencia->total_pacientes;

        Pilha_Emergencia->Pacientes[index] = paciente;

        Pilha_Emergencia->total_pacientes++;
    }
    else if (destino == 2)
    {
        if (Fila_Consulta->total_pacientes ==
            MAX_CONSULTA)
        {
            printf("Consulta cheia!\n");

            segurar_leitor();

            return;
        }

        int index = Fila_Consulta->total_pacientes;

        Fila_Consulta->Pacientes[index] = paciente;

        Fila_Consulta->total_pacientes++;
    }
    else if (destino == 3)
    {
        if (Fila_Exame_Circular->total_pacientes ==
            MAX_EXAME)
        {
            printf("Exame cheio!\n");

            segurar_leitor();

            return;
        }

        int inicio_exame =
            Fila_Exame_Circular->index_inicio;

        int total_exame =
            Fila_Exame_Circular->total_pacientes;

        int fim =
            (inicio_exame + total_exame) % MAX_EXAME;

        Fila_Exame_Circular->Pacientes[fim] = paciente;

        Fila_Exame_Circular->total_pacientes++;
    }
    else
    {
        printf("Setor de destino invalido!\n");

        segurar_leitor();

        return;
    }

    printf("Paciente transferido com sucesso!\n");

    segurar_leitor();
}

void Gerar_Relatorios()
{
    int total =
        Pilha_Emergencia->total_pacientes +
        Fila_Consulta->total_pacientes +
        Fila_Exame_Circular->total_pacientes;

    limpar_tela();

    printf("\n===== RELATORIOS DO HOSPITAL =====\n");

    printf("Pacientes na Emergencia: %d\n",
           Pilha_Emergencia->total_pacientes);

    printf("Pacientes na Consulta: %d\n",
           Fila_Consulta->total_pacientes);

    printf("Pacientes no Exame: %d\n",
           Fila_Exame_Circular->total_pacientes);

    printf("Total de Pacientes: %d\n", total);

    segurar_leitor();
}

void CriarArquivoTempo(double time_used)
{
    FILE *f_ptr;

    f_ptr = fopen("tempo_execucao.txt", "w");

    if (f_ptr == NULL)
    {
        printf("\nNão foi possível criar o arquivo especificado\n");

        return;
    }

    fprintf(f_ptr, "\nTempo de Execucao: %f\n", time_used);

    fclose(f_ptr);
}

int main(int argc, char const *argv[])
{
    clock_t comeco;
    clock_t final;

    double tempo_execucao;

    comeco = clock();

    int opcao;

    Pilha_Emergencia = Criar_Pilha_Emergencia();

    Fila_Consulta = Criar_Fila_Consulta();

    Fila_Exame_Circular = Criar_Fila_Exame();

    do
    {
        limpar_tela();

        printf("---------HOSPITAL---------\n");
        printf("1. Cadastrar Novo Paciente\n");
        printf("2. Atender Paciente em Cada Setor\n");
        printf("3. Mostrar Pacientes em Cada Setor\n");
        printf("4. Transferir Paciente de Setor\n");
        printf("5. Relatorios\n");
        printf("6. Realizar Teste de Estresse\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        printf("Opcao digitada: %d\n", opcao);

        switch (opcao)
        {
        case 1:
            Cadastrar_Paciente();
            break;

        case 2:
            Atender_Paciente_Nos_Setores();
            break;

        case 3:
            Mostrar_Pacientes();
            break;

        case 4:
            Transferir_Paciente();
            break;

        case 5:
            Gerar_Relatorios();
            break;

        case 6:
            RealizarTesteEstresse();
            break;

        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            limpar_tela();

            printf("\nOpcao Invalida Tente Novamente!\n");

            segurar_leitor();

            break;
        }

    } while (opcao != 0);

    free(Pilha_Emergencia);

    free(Fila_Consulta);

    free(Fila_Exame_Circular);

    final = clock();

    tempo_execucao =
        ((double)(final - comeco)) / CLOCKS_PER_SEC;

    CriarArquivoTempo(tempo_execucao);

    return 0;
}