#ifndef TP2_ARMERO_H
#define TP2_ARMERO_H

#include <unistd.h>

#include "Thread.h"
#include "Inventario.h"
#include "PuntosBeneficioMonitor.h"

class Armero : public Thread {
private:
    Inventario& inventario;
    PuntosBeneficioMonitor& puntos;
public:
    Armero(Inventario& inventario, PuntosBeneficioMonitor& puntos) :
        inventario(inventario), puntos(puntos) {}
    void work() override;
    ~Armero() = default;
};


#endif //TP2_ARMERO_H
