#ifndef TP2_CARPINTERO_H
#define TP2_CARPINTERO_H

#include <unistd.h>

#include "Thread.h"
#include "Inventario.h"
#include "PuntosBeneficioMonitor.h"

class Carpintero : public Thread {
private:
    Inventario& inventario;
    PuntosBeneficioMonitor& puntos;
public:
    Carpintero(Inventario& inventario, PuntosBeneficioMonitor& puntos) :
        inventario(inventario), puntos(puntos) {}
    void work() override;
    ~Carpintero() = default;
};


#endif //TP2_CARPINTERO_H
