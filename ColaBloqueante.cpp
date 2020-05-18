#include "ColaBloqueante.h"

ColaBloqueante::ColaBloqueante() {
    this->cerrada = false;
}

void ColaBloqueante::depositar(const Recurso recurso) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(recurso);
    cond_var.notify_all();
}

Recurso ColaBloqueante::quitar() {
    std::unique_lock<std::mutex> lock(mtx);

    while (queue.empty()){
        if (cerrada){
            return NoRecurso;//Cuando un recolector hace quitar y recibe
                             //NoRecurso sabe que la cola termino
                             //de llenarse y termina de trabajar
        }
        cond_var.wait(lock);
    }
    Recurso recurso = queue.front();
    queue.pop();
    return recurso;
}

bool ColaBloqueante::puedoQuitar() {
    std::unique_lock<std::mutex> lock(mtx);
    return !(queue.empty() && cerrada);
}

void ColaBloqueante::cerrar() {
    std::unique_lock<std::mutex> lock(mtx);
    cerrada = true;
    cond_var.notify_all();
}

ColaBloqueante::~ColaBloqueante() {}

