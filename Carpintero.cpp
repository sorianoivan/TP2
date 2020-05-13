#include "Carpintero.h"

void Carpintero::work() {
    int puntos_a_depositar = 0;
    while (inventario.verificarRecetaCarpintero() || inventario.canRetrieve()){
        puntos_a_depositar = this->inventario.retrieveCarpintero();
        usleep(60000);
        puntos.store(puntos_a_depositar);
    }
}
