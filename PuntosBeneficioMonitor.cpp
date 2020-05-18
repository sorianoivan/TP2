#include "PuntosBeneficioMonitor.h"

PuntosBeneficioMonitor::PuntosBeneficioMonitor() {
    this->puntos = 0;
}

void PuntosBeneficioMonitor::depositar(const unsigned int puntos_a_depositar) {
    mtx.lock();
    puntos += puntos_a_depositar;
    mtx.unlock();
}

unsigned int PuntosBeneficioMonitor::getPuntos() const {
    return puntos;
}

PuntosBeneficioMonitor::~PuntosBeneficioMonitor() {}


