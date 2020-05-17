#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include <iostream>
#include <unistd.h>

#include "ColaBloqueante.h"
#include "Recursos.h"
#include "Thread.h"
#include "Inventario.h"

class Recolector : public Thread{
private:
    ColaBloqueante& queue;
    Inventario& inventario;
public:
    Recolector(ColaBloqueante& queue, Inventario& inventario) :
        queue(queue), inventario(inventario) {}
    void work() override;
    ~Recolector() = default;
};


#endif //_COLLECTOR_H
