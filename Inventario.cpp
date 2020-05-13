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

int Inventario::retrieveCocinero() {
    std::unique_lock<std::mutex> lock(mtx);

    while (!verificarRecetaCocinero()){
        if (done_adding) return 0;

        cond_var.wait(lock);
    }

    trigo -= 2;
    carbon--;

    return 5;
}

int Inventario::retrieveCarpintero() {
    std::unique_lock<std::mutex> lock(mtx);

    while (!verificarRecetaCarpintero()){
        if (done_adding) return 0;
        cond_var.wait(lock);
    }

    madera -= 3;
    hierro--;

    return 2;
}

int Inventario::retrieveArmero() {
    std::unique_lock<std::mutex> lock(mtx);

    while (!verificarRecetaArmero()){
        if (done_adding) return 0;
        cond_var.wait(lock);
    }

    hierro -= 2;
    carbon -= 2;

    return 3;
}

bool Inventario::verificarRecetaCocinero() const{
    return (trigo >= 2 && carbon >= 1);
}

bool Inventario::verificarRecetaCarpintero() const{
    return (madera >= 3 && hierro >= 1);
}

bool Inventario::verificarRecetaArmero() const{
    return (carbon >= 2 && hierro >= 2);
}

bool Inventario::verificarRecursos() const{
    return (verificarRecetaCocinero() || verificarRecetaCarpintero()
            || verificarRecetaArmero());
}

bool Inventario::canRetrieve() const{
    return !(done_adding);
}

void Inventario::close(){
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
