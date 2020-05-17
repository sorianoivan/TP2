#include "Productor.h"

void Productor::work() {
    int puntos_a_depositar = 0;
    while (inventario.verificarReceta(tipo) || inventario.puedoConsumir()) {
        puntos_a_depositar = this->inventario.consumirRecursos(tipo);
        usleep(60000);
        puntos.store(puntos_a_depositar);
    }
}

