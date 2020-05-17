#include "Inventario.h"

Inventario::Inventario() {
    trigo = 0;
    madera = 0;
    carbon = 0;
    hierro = 0;

    done_adding = false;
}

void Inventario::store(const Recurso recurso) {
    std::unique_lock<std::mutex> lock(mtx);
    switch (recurso) {
        case Trigo:
            trigo++;
            break;
        case Madera:
            madera++;
            break;
        case Carbon:
            carbon++;
            break;
        case Hierro:
            hierro++;
            break;
        default:
            break;
    }
    if (verificarRecursos()) cond_var.notify_all();
}

int Inventario::_consumir(int tipo) {//privada
    switch (tipo) {
        case COCINERO:
            trigo -= 2;
            carbon -= 1;
            return 5;

        case CARPINTERO:
            madera -= 3;
            hierro -= 1;
            return 2;

        case ARMERO:
            hierro -= 2;
            carbon -= 2;
            return 3;

        default:
            return 0;
    }
}

int Inventario::consumirRecursos(int tipo){
    std::unique_lock<std::mutex> lock(mtx);

    while (!verificarReceta(tipo)){
        if (done_adding) return 0;
        cond_var.wait(lock);
    }
    return _consumir(tipo);
}


bool Inventario::_verificarRecetaCocinero() const{//privada
    return (trigo >= 2 && carbon >= 1);
}

bool Inventario::_verificarRecetaCarpintero() const{//privada
    return (madera >= 3 && hierro >= 1);
}

bool Inventario::_verificarRecetaArmero() const{//privada
    return (carbon >= 2 && hierro >= 2);
}

bool Inventario::verificarReceta(int tipo) const {
    switch (tipo) {
        case COCINERO:
            return _verificarRecetaCocinero();

        case CARPINTERO:
            return _verificarRecetaCarpintero();

        case ARMERO:
            return _verificarRecetaArmero();

        default:
            return false;
    }
}

bool Inventario::verificarRecursos() const{
    return (_verificarRecetaCocinero() || _verificarRecetaCarpintero()
            || _verificarRecetaArmero());
}

bool Inventario::puedoConsumir() const{
    return !(done_adding);
}

void Inventario::cerrar(){
    std::unique_lock<std::mutex> lock(mtx);
    done_adding = true;
    cond_var.notify_all();
}

int Inventario::getCantTrigo() const {
    return trigo;
}

int Inventario::getCantMadera() const {
    return madera;
}

int Inventario::getCantHierro() const {
    return hierro;
}

int Inventario::getCantCarbon() const {
    return carbon;
}
