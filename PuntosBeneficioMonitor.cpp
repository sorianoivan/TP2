#include "PuntosBeneficioMonitor.h"

void PuntosBeneficioMonitor::store(int puntos_a_depositar) {
    mtx.lock();
    puntos += puntos_a_depositar;
    mtx.unlock();
}

unsigned int PuntosBeneficioMonitor::getPuntos() const {
    return puntos;
}
