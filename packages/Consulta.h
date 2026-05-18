#include "paciente.h"
#include "Utils.h"

typedef struct Consulta{
    Paciente Pacientes[MAX_CONSULTA];
    int total_pacientes;
} Consulta;