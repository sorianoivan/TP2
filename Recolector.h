#ifndef _RECOLECTOR_H
#define _RECOLECTOR_H

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
    /* Constructor */
    Recolector(ColaBloqueante& queue, Inventario& inventario) :
        queue(queue), inventario(inventario) {}

    /* Si hay, saca un recurso de la cola, espera 50ms y lo deposita
     * en el inventario */
    void trabajar() override;

    /* Destructor */
    ~Recolector();
};


#endif //_RECOLECTOR_H
