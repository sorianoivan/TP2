#include "PuntosBeneficioMonitor.h"

PuntosBeneficioMonitor::PuntosBeneficioMonitor() {
    this->puntos = 0;
}

void PuntosBeneficioMonitor::store(const int puntos_a_depositar) {
    mtx.lock();
    puntos += puntos_a_depositar;
    mtx.unlock();
}

unsigned int PuntosBeneficioMonitor::getPuntos() const {
    return puntos;
}


