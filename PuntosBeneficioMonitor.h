#ifndef _PUNTOSBENEFICIOMONITOR_H
#define _PUNTOSBENEFICIOMONITOR_H

#include <mutex>

class PuntosBeneficioMonitor {
private:
    unsigned int puntos;
    std::mutex mtx;

public:
    PuntosBeneficioMonitor() : puntos(0) {}
    void store(int puntos_a_depositar);
    unsigned int getPuntos() const;
    ~PuntosBeneficioMonitor() = default;
};


#endif //_PUNTOSBENEFICIOMONITOR_H
