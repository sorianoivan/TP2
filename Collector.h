#ifndef TP2_COLLECTOR_H
#define TP2_COLLECTOR_H

#include <iostream>
#include <unistd.h>

#include "BlockingQueue.h"
#include "Recursos.h"
#include "Thread.h"
#include "Inventario.h"

class Collector : public Thread{
private:
    Recurso recurso;
    BlockingQueue& queue;
    Inventario& inventario;
public:
    Collector(BlockingQueue& queue, Inventario& inventario) :
        queue(queue), inventario(inventario) {}
    void work() override;
    ~Collector();

};


#endif //TP2_COLLECTOR_H
