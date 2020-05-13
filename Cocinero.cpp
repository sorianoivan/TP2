#include "Cocinero.h"

void Cocinero::work() {
    int puntos_a_depositar = 0;
    while (inventario.verificarRecetaCocinero() || inventario.canRetrieve()){
        puntos_a_depositar = this->inventario.retrieveCocinero();
        usleep(60000);
        puntos.store(puntos_a_depositar);
    }
}
