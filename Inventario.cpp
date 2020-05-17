#include "Inventario.h"

#define PUNTOS_COCINERO 5
#define PUNTOS_CARPINTERO 2
#define PUNTOS_ARMERO 3

#define RECETA_COCINERO_TRIGO 2
#define RECETA_COCINERO_CARBON 1
#define RECETA_CARPINTERO_MADERA 3
#define RECETA_CARPINTERO_HIERRO 1
#define RECETA_ARMERO_CARBON 2
#define RECETA_ARMERO_HIERRO 2

Inventario::Inventario() {
    trigo = 0;
    madera = 0;
    carbon = 0;
    hierro = 0;

    cerrado = false;
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

int Inventario::_consumir(const int tipo) {//privada
    switch (tipo) {
        case COCINERO:
            trigo -= RECETA_COCINERO_TRIGO;
            carbon -= RECETA_COCINERO_CARBON;
            return PUNTOS_COCINERO;

        case CARPINTERO:
            madera -= RECETA_CARPINTERO_MADERA;
            hierro -= RECETA_CARPINTERO_HIERRO;
            return PUNTOS_CARPINTERO;

        case ARMERO:
            hierro -= RECETA_ARMERO_HIERRO;
            carbon -= RECETA_ARMERO_CARBON;
            return PUNTOS_ARMERO;

        default:
            return 0;
    }
}

int Inventario::consumirRecursos(const int tipo){
    std::unique_lock<std::mutex> lock(mtx);

    while (!verificarReceta(tipo)){
        if (cerrado) return 0;
        cond_var.wait(lock);
    }
    return _consumir(tipo);
}


bool Inventario::_verificarRecetaCocinero() const{//privada
    return (trigo >= RECETA_COCINERO_TRIGO &&
            carbon >= RECETA_COCINERO_CARBON);
}

bool Inventario::_verificarRecetaCarpintero() const{//privada
    return (madera >= RECETA_CARPINTERO_MADERA &&
            hierro >= RECETA_CARPINTERO_HIERRO);
}

bool Inventario::_verificarRecetaArmero() const{//privada
    return (carbon >= RECETA_ARMERO_CARBON &&
            hierro >= RECETA_ARMERO_HIERRO);
}

bool Inventario::verificarReceta(const int tipo) const {
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
    return !(cerrado);
}

void Inventario::cerrar(){
    std::unique_lock<std::mutex> lock(mtx);
    cerrado = true;
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

Inventario::~Inventario() {}
