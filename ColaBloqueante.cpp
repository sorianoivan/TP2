#include "ColaBloqueante.h"

void ColaBloqueante::push(const Recurso recurso) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(recurso);
    cond_var.notify_all();
}

Recurso ColaBloqueante::pop() {
    std::unique_lock<std::mutex> lock(mtx);

    while (queue.empty()){
        if (done_pushing){
            return NoRecurso;
        }
        cond_var.wait(lock);
    }
    Recurso recurso = queue.front();
    queue.pop();
    return recurso;
}

bool ColaBloqueante::puedoQuitar() {
    return !(queue.empty() && done_pushing);
}

void ColaBloqueante::cerrar() {
    std::unique_lock<std::mutex> lock(mtx);
    done_pushing = true;
    cond_var.notify_all();
}

