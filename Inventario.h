#ifndef _INVENTARIO_H
#define _INVENTARIO_H

#include <iostream>
#include <mutex>
#include <condition_variable>

#include "Recursos.h"
#include "Constantes.h"


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
    void cerrar();

    bool verificarRecursos() const;
    bool _verificarRecetaCocinero() const;
    bool _verificarRecetaCarpintero() const;
    bool _verificarRecetaArmero() const;

    bool puedoConsumir() const;
    int retrieveCocinero();
    int retrieveCarpintero();
    int retrieveArmero();

    int getCantTrigo() const;
    int getCantMadera() const;
    int getCantHierro() const;
    int getCantCarbon() const;

    ~Inventario() = default;

    bool verificarReceta(int tipo) const;

    int consumirRecursos(int tipo);

    int _consumir(int tipo);
};


#endif //_INVENTARIO_H
