#include "Collector.h"
Collector::~Collector() {
    //do nothing
}

void Collector::work() {
    while (this->queue.canPop()) {
        this->recurso = this->queue.pop();
        usleep(50000);
        std::cout << this->recurso;
    }
}
