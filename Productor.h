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
    int tipo_productor;

public:
    /* Constructor */
    Productor(Inventario &inventario, PuntosBeneficioMonitor& puntos,
            int tipo) : inventario(inventario), puntos(puntos), 
            tipo_productor(tipo) {}

    /* Si los hay, consume los recursos del inventario, espera 60ms y deposita
     * los puntos correspondientes */
    void trabajar() override;

    /* Destructor */
    ~Productor();
};


#endif //_PRODUCTOR_H
