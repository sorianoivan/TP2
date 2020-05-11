#include "Inventario.h"

Inventario::Inventario() {
    trigo = 0;
    madera = 0;
    carbon = 0;
    hierro = 0;

    //recursos_disponibles  = false;
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

Inventario::~Inventario() {
    //do nothing
}

void Inventario::showLeft() const {
    std::cout << "Recursos Restantes" << std::endl;
    std::cout << "  - Trigo: " << trigo << std::endl;
    std::cout << "  - Madera: " << madera << std::endl;
    std::cout << "  - Carbon: " << carbon << std::endl;
    std::cout << "  - Hierro: " << hierro << std::endl;
}

void Inventario::retrieve() {
    std::unique_lock<std::mutex> lock(mtx);

    while (verificarRecursos()){
        cond_var.wait(lock);
    }

}

bool Inventario::verificarRecursos() const{
    if (trigo >= 2 && carbon >= 1) return true;
    if (madera >= 3 && hierro >= 1) return true;
    if (carbon >= 2 && hierro >= 2) return true;

    return false;
}
