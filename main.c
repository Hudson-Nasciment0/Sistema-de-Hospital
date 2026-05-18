#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// bibliotecas locais
#include "paciente.h"

// aqui por algum motivo não funciona o ';'
#define MAX_EMERGENCIA 10
#define MAX_CONSULTA 10
#define MAX_EXAME 8

// Filas
// deixamos o limite em 10 pacientes para emergência e consulta, e 8 para exame, mas isso pode ser ajustado conforme necessário
Paciente Pilha_Emergencia[MAX_EMERGENCIA];
//
int count_emergencia = 0;
//
Paciente fila_consulta[MAX_CONSULTA];
int count_consulta = 0;
//
Paciente fila_exame_circular[MAX_EXAME];
int count_exame = 0;
int index_inicio_exame = 0;
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
    if(count_emergencia == MAX_EMERGENCIA){
        // se está cheia retornamos
        printf("Pilha de Emergência Cheia. não é possível adicionar mais pacientes!!\n"); 
        return;
    }
    //
    Pilha_Emergencia[count_emergencia] = paciente;
    count_emergencia ++;
}
// Nesse caso fila é FIFO (First In, First Out) -- O Primeiro a entrar é o primeiro a sair.
void Cadastrar_Consulta(Paciente paciente){
    if(count_consulta == MAX_CONSULTA){
        printf("Fila de consulta Cheia. não é possível adicionar mais pacientes!");
        // se está cheia simplesmente retornamos
        return;
    }
    fila_consulta[count_consulta] = paciente;
    count_consulta ++;
}

// Funçao de cadastrar paciente no setor Exame
void Cadastrar_Exame(Paciente paciente){
   
    if(count_exame == MAX_EXAME){
        printf("Fila de Exame Cheia. não é possível adicionar mais pacientes!");
        return;
    }

    int posicao_insercao = (index_inicio_exame + count_exame) % MAX_EXAME; //
    fila_exame_circular[posicao_insercao] = paciente;
    count_exame ++; 

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
    if(count_emergencia == 0){
        //
        printf("\nO Setor de Emergencia nao possui pacientes!\n\n");
        //
        segurar_leitor();
        //
        return;
    }
    Paciente paciente = Pilha_Emergencia[count_emergencia-1]; // aqui usamos o contador com o -1 porque se tem 5 elementos o último é indice 4 ( i = c - 1 )
    //
    printf("\nRealizando Atendimento do Paciente: %s, no setor de EMERGENCIA\n",paciente.nome);
    //
    count_emergencia --; // aqui só reduzimos a contagem porque o próximo que entrar vai sobreescrever;
    free(paciente.nome); // ah, aqui também damos free() para evitar vazamento de memória ^_^ ;
    // aqui só pedimos para apertar para dar tempo de ler
    segurar_leitor();
    //
}
//
void Atender_Fila_Consulta(){
    // fila, FIFO
    // limpamos a tela
    limpar_tela();
    if(count_consulta == 0){
        //
        printf("\nO Setor de Consulta nao possui pacientes!\n\n");
        //
        segurar_leitor();
        return;
    }
    Paciente paciente = fila_consulta[0]; // sempre o primeiro é que vai ser atendido.
    //
    printf("\nRealizando Atendimento do Paciente: %s, no setor de CONSULTA\n",paciente.nome);
    // a gente anda com a fila;
    for (int i = 0; i < count_consulta; i++)
    {
        if(i > 0){
            fila_consulta[i-1] = fila_consulta[i]; // aqui passamos todo mundo pra esquerda (andamos com a fila)
        }
    }
    //
    count_consulta --;
    free(paciente.nome);
    segurar_leitor();
}
//
void Atender_Fila_Exame_Circular(){
    // fila, FIFO - circular
    if(count_exame == 0){
        printf("\nO Setor de Exames nao possui pacientes!\n\n");
        segurar_leitor();
        return;
    }
    //
    Paciente paciente = fila_exame_circular[index_inicio_exame];
    //
    printf("\nRealizando Atendimento do Paciente: %s, no setor de EXAME\n",paciente.nome);
    //
    index_inicio_exame = (index_inicio_exame + 1) % MAX_EXAME;
    //
    count_exame--; // diminuimos o tamanho da fila já que a pessoa foi atendida
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
    if(count_emergencia > 0){
        //
        for (int i = 0; i < count_emergencia; i++)
        {
            // pegamos cada paciente para mostrar os dados dele;
            Paciente p = Pilha_Emergencia[i];
            //
            printf("Paciente: %s, Idade: %d, Gravidade: %d, Tipo de Atendimento: EMERGENCIA (%d)\n",p.nome,p.idade,p.gravidade,p.tipo_atendimento);
        }
        //
    } else { printf("\nSetor de EMERGENCIA Vazio!\n"); }
    //
    printf("\n---CONSULTA---\n");
    //
    if(count_consulta > 0){
        //
        for (int i = 0; i < count_consulta; i++)
        {
            // pegamos cada paciente para mostrar os dados dele;
            Paciente p = fila_consulta[i];
            //
            printf("Paciente: %s, Idade: %d, Gravidade: %d, Tipo de Atendimento: CONSULTA (%d)\n",p.nome,p.idade,p.gravidade,p.tipo_atendimento);
        }
        //
    }else{ printf("\nSetor de CONSULTA Vazio!\n"); }
    //
    printf("\n---EXAME---\n");
    //
    if(count_exame > 0){
        //
        for (int i = 0; i < count_exame; i++)
        {
            // pegamos cada paciente para mostrar os dados dele;
            Paciente p = fila_exame_circular[(index_inicio_exame + i) % MAX_EXAME];
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

    // Removemos o paciente da origem para passar ele para o setor correspondente
    // Aqui cuidamos do setor de Emergenica
    if(origem == 1){
        if(count_emergencia == 0){
            printf("Emergencia vazia!\n");
            segurar_leitor();
            return;
        }

        paciente = Pilha_Emergencia[count_emergencia - 1];
        count_emergencia--;
    }
    // Aqui cuidamos do setor de Consulta
    else if(origem == 2){
        if(count_consulta == 0){
            printf("Consulta vazia!\n");
            segurar_leitor();
            return;
        }

        paciente = fila_consulta[0];

        for(int i = 1; i < count_consulta; i++){
            fila_consulta[i - 1] = fila_consulta[i];
        }

        count_consulta--;
    }
    // Aqui cuidamos do setor de Exames
    else if(origem == 3){
        if(count_exame == 0){
            printf("Exame vazio!\n");
            segurar_leitor();
            return;
        }

        paciente = fila_exame_circular[index_inicio_exame];
        index_inicio_exame = (index_inicio_exame + 1) % MAX_EXAME;
        count_exame--;
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
        if(count_emergencia == MAX_EMERGENCIA){
            printf("Emergencia cheia!\n");
            segurar_leitor();
            return;
        }
        // pegamos o paciente e adicionamos no setor correspondente
        Pilha_Emergencia[count_emergencia] = paciente;
        count_emergencia++;
    }

    else if(destino == 2){
        if(count_consulta == MAX_CONSULTA){
            printf("Consulta cheia!\n");
            segurar_leitor();
            return;
        }
        // o mesmo processo do descrito acima
        fila_consulta[count_consulta] = paciente;
        count_consulta++;
    }

    else if(destino == 3){
        if(count_exame == MAX_EXAME){
            printf("Exame cheio!\n");
            segurar_leitor();
            return;
        }
        // aqui temos que usar o cálculo usado no cadastro para ter o indice correto para a inserção
        int fim = (index_inicio_exame + count_exame) % MAX_EXAME;
        fila_exame_circular[fim] = paciente;
        count_exame++;
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
    int total = count_emergencia + count_consulta + count_exame;

    limpar_tela();

    printf("\n===== RELATORIOS DO HOSPITAL =====\n");
    printf("Pacientes na Emergencia: %d\n", count_emergencia);
    printf("Pacientes na Consulta: %d\n", count_consulta);
    printf("Pacientes no Exame: %d\n", count_exame);
    printf("Total de Pacientes: %d\n", total);

    segurar_leitor();
}


int main(int argc, char const *argv[])
{
   int opcao;
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

    return 0;
}
