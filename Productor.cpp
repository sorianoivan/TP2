#include "Productor.h"

#define TIEMPO_ESPERA_PRODUCTOR 60000

void Productor::trabajar() {
    unsigned int puntos_a_depositar = 0;
    while (inventario.verificarReceta(tipo_productor) ||
            inventario.puedoConsumir()) {
        puntos_a_depositar = this->inventario.consumirRecursos(tipo_productor);
        usleep(TIEMPO_ESPERA_PRODUCTOR);
        puntos.depositar(puntos_a_depositar);
    }
}

Productor::~Productor() {}

