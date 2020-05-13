#include "Collector.h"

void Collector::work() {
    Recurso recurso;
    while (this->queue.canPop()) {
        recurso = this->queue.pop();
        usleep(50000);
        if (recurso != NoRecurso){
            inventario.store(recurso);
        }
    }
}
