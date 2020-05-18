#ifndef _COLABLOQUEANTE_H
#define _COLABLOQUEANTE_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Recursos.h"


class ColaBloqueante {
private:
    bool cerrada;
    std::mutex mtx;
    std::condition_variable cond_var;
    std::queue<Recurso> queue;

public:
    /* Constructor */
    ColaBloqueante();

    /* Pone un recurso al final de la cola */
    void depositar(const Recurso recurso);
    /* Quita el recurso del principio de la cola.
     * Si la cola esta vacia y fue cerrada devuelve
     * NoRecurso */
    Recurso quitar();
    /* Retorna false si la cola esta vacia y cerrada,
     * true en otro caso */
    bool puedoQuitar();
    /* Cierra la cola y notifica a todos los threads que estan esperando */
    void cerrar();

    /* Destructor */
    ~ColaBloqueante();
};

#endif //_COLABLOQUEANTE_H
