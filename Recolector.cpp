#include "Recolector.h"

void Recolector::work() {
    Recurso recurso;
    while (this->queue.puedoQuitar()) {
        recurso = this->queue.pop();
        usleep(50000);
        if (recurso != NoRecurso){
            inventario.store(recurso);
        }
    }
}
