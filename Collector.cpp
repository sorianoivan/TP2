#include "Collector.h"
Collector::~Collector() {
    //do nothing
}

void Collector::work() {
    while (this->queue.canPop()) {
        this->recurso = this->queue.pop();
        usleep(50000);
        //agregar recurso al inventario
        if (this->recurso != NoRecurso){
            //std::cout << this->recurso;
            inventario.store(recurso);
        }
    }
}
