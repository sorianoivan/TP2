#ifndef _PUNTOSBENEFICIOMONITOR_H
#define _PUNTOSBENEFICIOMONITOR_H

#include <mutex>

class PuntosBeneficioMonitor {
private:
    unsigned int puntos;
    std::mutex mtx;

public:
    /* Constructor */
    PuntosBeneficioMonitor();

    /* Suma los puntos correspondientes */
    void store(const int puntos_a_depositar);
    /* Devuelve la cantidad de puntos */
    unsigned int getPuntos() const;

    /* Destructor */
    ~PuntosBeneficioMonitor() = default;
};


#endif //_PUNTOSBENEFICIOMONITOR_H
