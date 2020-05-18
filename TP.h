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
    void _invocarTrabajadores();
    void _crearRecolectores(const int cant, std::vector<Thread *>& vector,
                            ColaBloqueante& cola_recolector);
    void _crearProductores(const int cant, std::vector<Thread *> &vector,
            const int tipo);
    void _llenarColasDeRecursos();
    void _mostrarResultados() const;
    void _liberarTrabajadores(const int cant, std::vector<Thread *> vector);
    void _finalizar();
};

#endif //_TP_H
