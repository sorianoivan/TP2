#ifndef TP2_COLLECTOR_H
#define TP2_COLLECTOR_H

#include <iostream>
#include <unistd.h>

#include "BlockingQueue.h"
#include "Recursos.h"
#include "Thread.h"

class Collector : public Thread{
private:
    Recurso recurso;
    BlockingQueue& queue;
public:
    explicit Collector(BlockingQueue& queue) : queue(queue) {};
    void work() override;
    ~Collector();

};


#endif //TP2_COLLECTOR_H
