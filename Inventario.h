#ifndef _INVENTARIO_H
#define _INVENTARIO_H

#include <iostream>
#include <mutex>
#include <condition_variable>

#include "Recursos.h"


class Inventario {
private:
    int trigo;
    int madera;//seria facil cambiar a una cola
    int carbon;
    int hierro;

    //bool recursos_disponibles;

    std::mutex mtx;
    std::condition_variable cond_var;

public:
    Inventario();
    void store(Recurso recurso);
    void retrieve();
    bool verificarRecursos() const;
    void showLeft() const;
    ~Inventario();
};


#endif //_INVENTARIO_H
