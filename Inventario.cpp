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

void Inventario::depositar(const Recurso recurso) {
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
    if (_verificarRecursos()) cond_var.notify_all();
}

unsigned int Inventario::consumirRecursos(const int tipo_productor){
    std::unique_lock<std::mutex> lock(mtx);

    while (!verificarReceta(tipo_productor)){
        if (cerrado) return 0;
        cond_var.wait(lock);
    }
    return _consumir(tipo_productor);
}

bool Inventario::verificarReceta(const int tipo_productor) const {
    switch (tipo_productor) {
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

bool Inventario::puedoConsumir() {
    std::unique_lock<std::mutex> lock(mtx);
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

/* Verifica si los recursos para el cocinero estan disponibles */
bool Inventario::_verificarRecetaCocinero() const{
    return (trigo >= RECETA_COCINERO_TRIGO &&
            carbon >= RECETA_COCINERO_CARBON);
}

/* Verifica si los recursos para el carpintero estan disponibles */
bool Inventario::_verificarRecetaCarpintero() const{
    return (madera >= RECETA_CARPINTERO_MADERA &&
            hierro >= RECETA_CARPINTERO_HIERRO);
}

/* Verifica si los recursos para el armero estan disponibles */
bool Inventario::_verificarRecetaArmero() const{
    return (carbon >= RECETA_ARMERO_CARBON &&
            hierro >= RECETA_ARMERO_HIERRO);
}

/* Retorna true si hay recursos disponibles para que alguno de los
     * productores consuma */
bool Inventario::_verificarRecursos() const{
    return (_verificarRecetaCocinero() || _verificarRecetaCarpintero()
            || _verificarRecetaArmero());
}

/* Consume los recursos del productor "tipo_productor" y devuelve la cantidad
     * de puntos correspondiente */
unsigned int Inventario::_consumir(const int tipo) {
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

Inventario::~Inventario() {}
