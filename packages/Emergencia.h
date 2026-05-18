#include "Utils.h"
#include "paciente.h"
//
typedef struct Emergencia{
    Paciente Pacientes[MAX_EMERGENCIA];
    int total_pacientes;
} Emergencia;