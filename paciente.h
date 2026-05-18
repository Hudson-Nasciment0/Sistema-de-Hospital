typedef struct Paciente
{
    char* nome; // auto explicativo
    int idade; // auto explicativo 
    int gravidade; // -- 1 a 5, sendo 1 o mais grave
    int tipo_atendimento; // -- 1 para emergência, 2 para consulta , 3 para exame    
} Paciente;



// Função para criar um paciente
// Parâmetros:
// - nome: nome do paciente
// - idade: idade do paciente
// - gravidade: gravidade do caso (1 a 5, sendo 1 o mais grave)
// - tipo_atendimento: tipo de atendimento (1 para emergência, 2 para consulta, 3 para exame)
// Retorna:
// - Uma estrutura Paciente preenchida com os dados fornecidos
Paciente criar_paciente(const char* nome, int idade, int gravidade, int tipo_atendimento);