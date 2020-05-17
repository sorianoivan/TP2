#ifndef _PRODUCTOR_H
#define _PRODUCTOR_H

#include <unistd.h>

#include "Inventario.h"
#include "Thread.h"
#include "PuntosBeneficioMonitor.h"
#include "Constantes.h"

class Productor : public Thread {
private:
    Inventario& inventario;
    PuntosBeneficioMonitor& puntos;
    int tipo;

public:
    Productor(Inventario &inventario, PuntosBeneficioMonitor& puntos,
            int tipo) : inventario(inventario), puntos(puntos), tipo(tipo) {}

    void work() override;
    ~Productor() = default;
};


#endif //_PRODUCTOR_H
