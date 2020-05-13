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

    bool done_adding;

    std::mutex mtx;
    std::condition_variable cond_var;

public:
    Inventario();
    void store(Recurso recurso);
    void close();

    bool verificarRecursos() const;
    bool verificarRecetaCocinero() const;
    bool verificarRecetaCarpintero() const;
    bool verificarRecetaArmero() const;

    bool canRetrieve() const;
    int retrieveCocinero();
    int retrieveCarpintero();
    int retrieveArmero();

    int getCantTrigo() const;
    int getCantMadera() const;
    int getCantHierro() const;
    int getCantCarbon() const;

    ~Inventario() = default;
};


#endif //_INVENTARIO_H
