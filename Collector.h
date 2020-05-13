#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include <iostream>
#include <unistd.h>

#include "BlockingQueue.h"
#include "Recursos.h"
#include "Thread.h"
#include "Inventario.h"

class Collector : public Thread{
private:
    BlockingQueue& queue;
    Inventario& inventario;
public:
    Collector(BlockingQueue& queue, Inventario& inventario) :
        queue(queue), inventario(inventario) {}
    void work() override;
    ~Collector() = default;
};


#endif //_COLLECTOR_H
