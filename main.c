#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// bibliotecas locais
#include "packages\paciente.h"
#include "packages\Utils.h"
//
#include "packages\Consulta.h"
#include "packages\Exame.h"
#include "packages\Emergencia.h"

// Filas
// deixamos o limite em 10 pacientes para emergência e consulta, e 8 para exame, mas isso pode ser ajustado conforme necessário
//
Emergencia *Pilha_Emergencia;
Consulta *Fila_Consulta;
Exame *Fila_Exame_Circular;
//
//
Emergencia* Criar_Pilha_Emergencia(){
    Emergencia *e = (Emergencia*) malloc(sizeof(Emergencia));
    if(e == NULL){
        printf("\nNão foi possível alocar memória para a Pilha Emergencia\n");
        segurar_leitor();
        exit(EXIT_FAILURE);
    }
    e->total_pacientes = 0;
    return e;
}
//
Consulta* Criar_Fila_Consulta(){
    Consulta *c = (Consulta*) malloc(sizeof(Consulta));
    if(c == NULL){
        printf("\nNão foi possível alocar memória para a Fila Consulta\n");
        segurar_leitor();
        exit(EXIT_FAILURE);
    }
    c->total_pacientes = 0;
    return c;
}
//
Exame* Criar_Fila_Exame(){
    Exame *e = (Exame*) malloc(sizeof(Exame));
    if(e == NULL){
        printf("\nNão foi possível alocar memória para a Fila Exame\n");
        segurar_leitor();
        exit(EXIT_FAILURE);
    }
    e->index_inicio = 0;
    e->total_pacientes = 0;
    return e;
}
//
// indeces para controlar o número de pacientes em cada fila
// exame como é circular precisamos de 2, tamanho total, e o indice atual
//
// Auxiliares
// essa função aqui só espera qualquer input para seguir em frente
void segurar_leitor(){
    printf("\n\nPressione qualquer tecla para prosseguir...");
    getchar();
}

// função simples que manda o console se limpar (uiii);
void limpar_tela(){
    system("cls");
}

// Funcoes

// Função para cadastrar no setor de Emergencia
void Cadastrar_Emergencia(Paciente paciente){
    // por ser uma pilha só adicionamos no último index já que é LIFO;
    if(Pilha_Emergencia->total_pacientes == MAX_EMERGENCIA){
        // se está cheia retornamos
        printf("Pilha de Emergência Cheia. não é possível adicionar mais pacientes!!\n"); 
        return;
    }
    //
    int index = Pilha_Emergencia->total_pacientes;
    Pilha_Emergencia->Pacientes[index] = paciente;
    Pilha_Emergencia->total_pacientes++;
}
// Nesse caso fila é FIFO (First In, First Out) -- O Primeiro a entrar é o primeiro a sair.
void Cadastrar_Consulta(Paciente paciente){
    if(Fila_Consulta->total_pacientes == MAX_CONSULTA){
        printf("Fila de consulta Cheia. não é possível adicionar mais pacientes!");
        // se está cheia simplesmente retornamos
        return;
    }
    int index = Fila_Consulta->total_pacientes;
    Fila_Consulta->Pacientes[index] = paciente;
    Fila_Consulta->total_pacientes++;
}

// Funçao de cadastrar paciente no setor Exame
void Cadastrar_Exame(Paciente paciente){
   
    if(Fila_Exame_Circular->total_pacientes == MAX_EXAME){
        printf("Fila de Exame Cheia. não é possível adicionar mais pacientes!");
        return;
    }
    int total_exame = Fila_Exame_Circular->total_pacientes;
    int index_inicio = Fila_Exame_Circular->index_inicio;
    //
    int posicao_insercao = (index_inicio + total_exame) % MAX_EXAME; //
    //
    Fila_Exame_Circular->Pacientes[posicao_insercao] = paciente;
    Fila_Exame_Circular->total_pacientes++;

    //
    printf("Cadastrado Paciente %s na fila de exame na posição [%d]",paciente.nome,posicao_insercao+1);
}
// auxiliares de cadastro
// aqui usamos as funcoes
void Cadastrar_Paciente(){
    //
    limpar_tela();
    //
    printf("\nBem vindo ao Cadastro de Paciente\n");
    // variaveis temporarias para o cadastro
    char nome_temp[100];
    int idade_temp, gravidade_temp,tipo_temp;
    //
    printf("\nDigite o nome do Paciente: ");
    // usamos o fgets porque ele aceita espaços e por algum motivo o scanf não???
    fgets(nome_temp,sizeof(nome_temp),stdin); // isso aqui não entendo muito como funciona, descobri pesquisando mas não entendi ;-;

    nome_temp[strcspn(nome_temp, "\n")] = 0; 
    //
    printf("\nDigite a idade do Paciente: ");
    scanf("%d",&idade_temp);
    //
    printf("\nGravidade (1-5): ");
    scanf("%d",&gravidade_temp);
    //
    if(gravidade_temp < 4){
        printf("\nTipo (1-Emergencia, 2-Consulta, 3-Exame): ");
        scanf("%d",&tipo_temp);
    }else{
        tipo_temp = 1;
    }
    //
    Paciente paciente = criar_paciente(nome_temp,idade_temp,gravidade_temp,tipo_temp);
    //
    // Verificamos o tipo de atendimento do paciente e o adicionamos à fila correspondente,
    // desde que haja espaço disponível na fila;

    if(paciente.tipo_atendimento == 1){ // emergencia
        Cadastrar_Emergencia(paciente);
    }
    else if (paciente.gravidade >= 4){
        Cadastrar_Emergencia(paciente);
        //
        printf("\nPaciente Cadastrado Na Emergência por Conta da Alta Gravidade!\n");
    }
    else if (paciente.tipo_atendimento == 2){ // consulta
        Cadastrar_Consulta(paciente);
    }
    else if (paciente.tipo_atendimento == 3){ // exame
        Cadastrar_Exame(paciente);
    }
    segurar_leitor();
}


// Funcoes auxiliares do atendimento

void Atender_Pilha_Emergencia(){
    // Limpamos a tela
    limpar_tela();
    // iniciamos o atendimento do último da pilha (topo)
    if(Pilha_Emergencia->total_pacientes == 0){
        //
        printf("\nO Setor de Emergencia nao possui pacientes!\n\n");
        //
        segurar_leitor();
        //
        return;
    }
    int index = Pilha_Emergencia->total_pacientes;
    Paciente paciente = Pilha_Emergencia->Pacientes[index-1]; // aqui usamos o contador com o -1 porque se tem 5 elementos o último é indice 4 ( i = c - 1 )
    //
    printf("\nRealizando Atendimento do Paciente: %s, no setor de EMERGENCIA\n",paciente.nome);
    //
    Pilha_Emergencia->total_pacientes--; // aqui só reduzimos a contagem porque o próximo que entrar vai sobreescrever;
    free(paciente.nome);
    segurar_leitor();
    //
}
//
void Atender_Fila_Consulta(){
    // fila, FIFO
    // limpamos a tela
    limpar_tela();
    if(Fila_Consulta->total_pacientes == 0){
        //
        printf("\nO Setor de Consulta nao possui pacientes!\n\n");
        //
        segurar_leitor();
        return;
    }
    Paciente paciente = Fila_Consulta->Pacientes[0]; // sempre o primeiro é que vai ser atendido.
    //
    printf("\nRealizando Atendimento do Paciente: %s, no setor de CONSULTA\n",paciente.nome);
    // a gente anda com a fila;
    for (int i = 0; i < Fila_Consulta->total_pacientes; i++)
    {
        if(i > 0){
            Fila_Consulta->Pacientes[i-1] = Fila_Consulta->Pacientes[i]; // aqui passamos todo mundo pra esquerda (andamos com a fila)
        }
    }
    //
    Fila_Consulta->total_pacientes--;
    free(paciente.nome);
    segurar_leitor();
}
//
void Atender_Fila_Exame_Circular(){
    // fila, FIFO - circular
    if(Fila_Exame_Circular->total_pacientes == 0){
        printf("\nO Setor de Exames nao possui pacientes!\n\n");
        segurar_leitor();
        return;
    }
    //
    int index_inicio = Fila_Exame_Circular->index_inicio;
    Paciente paciente = Fila_Exame_Circular->Pacientes[index_inicio];
    //
    printf("\nRealizando Atendimento do Paciente: %s, no setor de EXAME\n",paciente.nome);
    //
    Fila_Exame_Circular->index_inicio = (index_inicio + 1) % MAX_EXAME;
    //
    Fila_Exame_Circular->total_pacientes--; // diminuimos o tamanho da fila já que a pessoa foi atendida
    free(paciente.nome);
    segurar_leitor();
    //
}

///

//
void Atender_Paciente_Nos_Setores(){
    Atender_Pilha_Emergencia();
    Atender_Fila_Consulta();
    Atender_Fila_Exame_Circular();
}

///

//
void Mostrar_Pacientes(){
    limpar_tela();
    //
    printf("---EXIBINDO PACIENTES DO HOSPITAL-----\n");
    //
    printf("\n---EMERGENCIA---\n");
    //
    if(Pilha_Emergencia->total_pacientes > 0){
        //
        for (int i = 0; i < Pilha_Emergencia->total_pacientes; i++)
        {
            // pegamos cada paciente para mostrar os dados dele;
            Paciente p = Pilha_Emergencia->Pacientes[i];
            //
            printf("Paciente: %s, Idade: %d, Gravidade: %d, Tipo de Atendimento: EMERGENCIA (%d)\n",p.nome,p.idade,p.gravidade,p.tipo_atendimento);
        }
        //
    } else { printf("\nSetor de EMERGENCIA Vazio!\n"); }
    //
    printf("\n---CONSULTA---\n");
    //
    if(Fila_Consulta->total_pacientes > 0){
        //
        for (int i = 0; i < Fila_Consulta->total_pacientes; i++)
        {
            // pegamos cada paciente para mostrar os dados dele;
            Paciente p = Fila_Consulta->Pacientes[i];
            //
            printf("Paciente: %s, Idade: %d, Gravidade: %d, Tipo de Atendimento: CONSULTA (%d)\n",p.nome,p.idade,p.gravidade,p.tipo_atendimento);
        }
        //
    }else{ printf("\nSetor de CONSULTA Vazio!\n"); }
    //
    printf("\n---EXAME---\n");
    //
    if(Fila_Exame_Circular->total_pacientes > 0){
        //
        for (int i = 0; i < Fila_Exame_Circular->total_pacientes; i++)
        {
            // pegamos cada paciente para mostrar os dados dele;
            Paciente p = Fila_Exame_Circular->Pacientes[i];
            //
            printf("Paciente: %s, Idade: %d, Gravidade: %d, Tipo de Atendimento: EXAME (%d)\n",p.nome,p.idade,p.gravidade,p.tipo_atendimento);
        }
        //
    }else{ printf("\nSetor de EXAME Vazio!\n"); }
    //
    segurar_leitor();
    
}
//
void Transferir_Paciente(){
    // aqui criamos variaveis temporarias para retar a opção e também o paciente para transferencia
    int origem, destino;
    Paciente paciente;

    printf("\n===== TRANSFERIR PACIENTE =====\n");
    printf("Origem: 1-Emergencia | 2-Consulta | 3-Exame: ");
    scanf("%d", &origem);

    printf("Destino: 1-Emergencia | 2-Consulta | 3-Exame: ");
    scanf("%d", &destino);
    //
    // aqui garantimos que a origem e o destino não sejam iguais
    //
    if(origem == destino){
        printf("Origem e destino nao podem ser iguais!\n");
        segurar_leitor();
        return;
    }
    //
    // Removemos o paciente da origem para passar ele para o setor correspondente
    // Aqui cuidamos do setor de Emergenica
    if(origem == 1){
        if(Pilha_Emergencia->total_pacientes == 0){
            printf("Emergencia vazia!\n");
            segurar_leitor();
            return;
        }
        int index = Pilha_Emergencia->total_pacientes - 1;
        paciente = Pilha_Emergencia->Pacientes[index];
        Pilha_Emergencia->total_pacientes--;
    }
    // Aqui cuidamos do setor de Consulta
    else if(origem == 2){
        if(Fila_Consulta->total_pacientes == 0){
            printf("Consulta vazia!\n");
            segurar_leitor();
            return;
        }

        paciente = Fila_Consulta->Pacientes[0];

        for(int i = 1; i < Fila_Consulta->total_pacientes; i++){
            Fila_Consulta->Pacientes[i - 1] = Fila_Consulta->Pacientes[i];
        }

        Fila_Consulta->total_pacientes--;
    }
    // Aqui cuidamos do setor de Exames
    else if(origem == 3){
        if(Fila_Exame_Circular->total_pacientes == 0){
            printf("Exame vazio!\n");
            segurar_leitor();
            return;
        }
        int index_inicio = Fila_Exame_Circular->index_inicio;
        //
        paciente = Fila_Exame_Circular->Pacientes[index_inicio];
        //
        Fila_Exame_Circular->index_inicio = (index_inicio + 1) % MAX_EXAME;
        //
        Fila_Exame_Circular->total_pacientes--;
    }
    // caso o setor de origem não exista:
    else{
        printf("Setor de origem invalido!\n");
        segurar_leitor();
        return;
    }

    // Aqui fazemos a adição no setor de destino
    // Respeitando o limite de pessoas no setor
    if(destino == 1){
        if(Pilha_Emergencia->total_pacientes == MAX_EMERGENCIA){
            printf("Emergencia cheia!\n");
            segurar_leitor();
            return;
        }
        // pegamos o paciente e adicionamos no setor correspondente
        int index = Pilha_Emergencia->total_pacientes;
        Pilha_Emergencia->Pacientes[index] = paciente;
        Pilha_Emergencia->total_pacientes++;
    }

    else if(destino == 2){
        if(Fila_Consulta->total_pacientes == MAX_CONSULTA){
            printf("Consulta cheia!\n");
            segurar_leitor();
            return;
        }
        // o mesmo processo do descrito acima
        int index = Fila_Consulta->total_pacientes;
        //
        Fila_Consulta->Pacientes[index] = paciente;
        //
        Fila_Consulta->total_pacientes++;
    }

    else if(destino == 3){
        if(Fila_Exame_Circular->total_pacientes == MAX_EXAME){
            printf("Exame cheio!\n");
            segurar_leitor();
            return;
        }
        // aqui temos que usar o cálculo usado no cadastro para ter o indice correto para a inserção
        int inicio_exame = Fila_Exame_Circular->index_inicio;
        int total_exame = Fila_Exame_Circular->total_pacientes;
        //
        int fim = (inicio_exame + total_exame) % MAX_EXAME;
        Fila_Exame_Circular->Pacientes[fim] = paciente;
        //
        Fila_Exame_Circular->total_pacientes++;
    }
    // caso o destino inserido não exista:
    else{
        printf("Setor de destino invalido!\n");
        segurar_leitor();
        return;
    }
    // se tudo deu certo avisamos.
    printf("Paciente transferido com sucesso!\n");
    segurar_leitor();
}

// agora a função que gera um relatório do hospital
void Gerar_Relatorios(){
    int total = Pilha_Emergencia->total_pacientes + Fila_Consulta->total_pacientes + Fila_Exame_Circular->total_pacientes;

    limpar_tela();

    printf("\n===== RELATORIOS DO HOSPITAL =====\n");
    printf("Pacientes na Emergencia: %d\n", Pilha_Emergencia->total_pacientes);
    printf("Pacientes na Consulta: %d\n", Fila_Consulta->total_pacientes);
    printf("Pacientes no Exame: %d\n", Fila_Exame_Circular->total_pacientes);
    printf("Total de Pacientes: %d\n", total);

    segurar_leitor();
}


int main(int argc, char const *argv[])
{
   int opcao;
   // Antes de rodar, criamos as filas
    Pilha_Emergencia = Criar_Pilha_Emergencia();
    Fila_Consulta = Criar_Fila_Consulta();
    Fila_Exame_Circular = Criar_Fila_Exame();
   //
   do{
        limpar_tela(); // limpamos a tela para seguir em frente (tira resto de texto desnecessário)
        printf("---------HOSPITAL---------\n");
        printf("1. Cadastrar Novo Paciente\n");
        printf("2. Atender Paciente em Cada Setor\n");
        printf("3. Mostrar Pacientes em Cada Setor\n");
        printf("4. Transferir Paciente de Setor\n");
        printf("5. Relatorios\n");
        printf("\n0. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        //
        getchar(); // limpamos o buffer depois de receber o numero escolhido.
        //
        // processamento das escolhas
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
        case 0:
            printf("\nSaindo do sistema...\n");
            break;
        default:
            limpar_tela();
            printf("\nOpcao Invalida Tente Novamente!\n");
            segurar_leitor(); // aqui seguramos para dar tempo de ler kkkkk
        }
   } while (opcao != 0); // continuamos no loop ate que o usuário escolha a opção de sair (0);
   //
   free(Pilha_Emergencia);
   free(Fila_Consulta);
   free(Fila_Exame_Circular);
    return 0;
}
