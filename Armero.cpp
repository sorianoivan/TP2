#include "Armero.h"

void Armero::work() {
    int puntos_a_depositar = 0;
    while (inventario.verificarRecetaArmero() || inventario.canRetrieve()){
        puntos_a_depositar = this->inventario.retrieveArmero();
        usleep(60000);
        puntos.store(puntos_a_depositar);
    }
}
