#ifndef _COCINERO_H
#define _COCINERO_H

#include <unistd.h>

#include "Inventario.h"
#include "Thread.h"
#include "PuntosBeneficioMonitor.h"


class Cocinero : public Thread{
private:
    Inventario& inventario;
    PuntosBeneficioMonitor& puntos;
public:
    Cocinero(Inventario &inventario, PuntosBeneficioMonitor& puntos) :
        inventario(inventario), puntos(puntos) {}
    void work() override;
    ~Cocinero() = default;
};


#endif //_COCINERO_H
