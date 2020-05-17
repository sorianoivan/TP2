#include "Productor.h"

#define TIEMPO_ESPERA_PRODUCTOR 60000

void Productor::work() {
    int puntos_a_depositar = 0;
    while (inventario.verificarReceta(tipo) || inventario.puedoConsumir()) {
        puntos_a_depositar = this->inventario.consumirRecursos(tipo);
        usleep(TIEMPO_ESPERA_PRODUCTOR);
        puntos.store(puntos_a_depositar);
    }
}

Productor::~Productor() {}

