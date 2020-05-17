#ifndef _TP_H
#define _TP_H

#include <thread>
#include <vector>
#include <string>

#include "FileProcessor.h"
#include "ColaBloqueante.h"
#include "PuntosBeneficioMonitor.h"
#include "Recursos.h"
#include "Recolector.h"
#include "Productor.h"
#include "Inventario.h"
#include "Constantes.h"

class TP {
private:
    int flag;
    FileProcessor file_processor;

    Inventario inventario;

    PuntosBeneficioMonitor puntos;

    ColaBloqueante cola_agricultores;
    ColaBloqueante cola_leniadores;
    ColaBloqueante cola_mineros;

    std::vector<Thread*> agricultores;
    std::vector<Thread*> leniadores;
    std::vector<Thread*> mineros;

    std::vector<Thread*> cocineros;
    std::vector<Thread*> carpinteros;
    std::vector<Thread*> armeros;

public:
    /* Constructor */
    TP();

    /* Ejecuta el tp */
    int ejecutar(const std::string& mapa, const std::string& trabajadores);

    /* Destructor */
    ~TP();

private:
    /* Invoca recolectores y productores */
    void _invocarTrabajadores();
    /* Crea "cant" de recolectores con su respectiva cola bloqueante
     * y se guardan en "vector" */
    void _crearRecolectores(const int cant, std::vector<Thread *>& vector,
                            ColaBloqueante& cola_recolector);
    /* Crea "cant" de productores "tipo" que se guardan en "vector" */
    void _crearProductores(const int cant, std::vector<Thread *> &vector,
            const int tipo);
    /* Llena las colas bloqueantes con los recursos leidos del mapa */
    void _llenarColasDeRecursos();
    /* Muestra los resultados en el formato requerido */
    void _mostrarResultados() const;
    /* Libera los recursos pertenecientes a los recolectores y productores */
    void _liberarTrabajadores(const int cant, std::vector<Thread *> vector);
    /* Finaliza el proceso de llenar el inventario y
     * sumar los puntos de beneficio */
    void _finalizar();
};

#endif //_TP_H
