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
    int madera;
    int carbon;
    int hierro;

    bool cerrado;

    std::mutex mtx;
    std::condition_variable cond_var;

public:
    /* Constructor */
    Inventario();

    /* Guarda un recurso en el inventario */
    void depositar(const Recurso recurso);
    /* Cierra el inventario y notifica a todos los threads q estan esperando */
    void cerrar();
    /* Verifica si alcanzan los recursos que el productor "tipo_productor" necesita
     * para consumir */
    bool verificarReceta(const int tipo_productor) const;
    /* Retorna true si el inventario no esta cerrado */
    bool puedoConsumir();
    /* Consume los recursos del inventario y devuelve los puntos a depositar */
    unsigned int consumirRecursos(const int tipo_productor);

    /* Devuelve la cantidad de trigo */
    int getCantTrigo() const;
    /* Devuelve la cantidad de madera */
    int getCantMadera() const;
    /* Devuelve la cantidad de hierro */
    int getCantHierro() const;
    /* Devuelve la cantidad de carbon */
    int getCantCarbon() const;

    /* Destructor */
    ~Inventario();

private:
    bool _verificarRecursos() const;
    bool _verificarRecetaCocinero() const;
    bool _verificarRecetaCarpintero() const;
    bool _verificarRecetaArmero() const;
    unsigned int _consumir(const int tipo);
};


#endif //_INVENTARIO_H
