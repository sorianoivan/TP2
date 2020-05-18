#include "Recolector.h"

#define TIEMPO_ESPERA_RECOLECTOR 50000

void Recolector::trabajar() {
    Recurso recurso;
    while (this->queue.puedoQuitar()) {
        recurso = this->queue.quitar();
        usleep(TIEMPO_ESPERA_RECOLECTOR);
        if (recurso != NoRecurso){
            inventario.depositar(recurso);
        }
    }
}

Recolector::~Recolector() {}
