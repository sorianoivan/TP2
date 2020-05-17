#include "Recolector.h"

#define TIEMPO_ESPERA_RECOLECTOR 50000

void Recolector::work() {
    Recurso recurso;
    while (this->queue.puedoQuitar()) {
        recurso = this->queue.pop();
        usleep(TIEMPO_ESPERA_RECOLECTOR);
        if (recurso != NoRecurso){
            inventario.store(recurso);
        }
    }
}

Recolector::~Recolector() {}
