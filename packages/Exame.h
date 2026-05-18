#include "paciente.h"
#include "Utils.h"

typedef struct Exame{
    Paciente Pacientes[MAX_EXAME];
    int total_pacientes;
    int index_inicio;
} Exame;