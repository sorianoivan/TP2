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
    void store(Recurso recurso);
    /* Cierra el inventario y notifica a todos los threads q estan esperando */
    void cerrar();
    /* Retorna true si hay recursos disponibles para que alguno de los
     * productores consuma */
    bool verificarRecursos() const;
    /* Verifica si alcanzan los recursos que el productor "tipo" necesita
     * para consumir */
    bool verificarReceta(const int tipo) const;
    /* Retorna true si el inventario no esta cerrado */
    bool puedoConsumir() const;
    /* Consume los recursos del inventario y devuelve los puntos a depositar */
    int consumirRecursos(const int tipo);

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
    /* Verifica si los recursos para el cocinero estan disponibles */
    bool _verificarRecetaCocinero() const;
    /* Verifica si los recursos para el carpintero estan disponibles */
    bool _verificarRecetaCarpintero() const;
    /* Verifica si los recursos para el armero estan disponibles */
    bool _verificarRecetaArmero() const;
    /* Consume los recursos del productor "tipo" y devuelve la cantidad
     * de puntos correspondiente */
    int _consumir(const int tipo);
};


#endif //_INVENTARIO_H
