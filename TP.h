#ifndef _TP_H
#define _TP_H

#include <thread>
#include <vector>
#include <string>

#include "FileProcessor.h"
#include "BlockingQueue.h"
#include "PuntosBeneficioMonitor.h"
#include "Recursos.h"
#include "Collector.h"
#include "Cocinero.h"
#include "Carpintero.h"
#include "Armero.h"
#include "Inventario.h"

class TP {
private:
    int flag;
    FileProcessor file_processor;

    Inventario inventario;

    PuntosBeneficioMonitor puntos;

    BlockingQueue agricultores_queue;
    BlockingQueue leniadores_queue;
    BlockingQueue mineros_queue;

    std::vector<Thread*> agricultores;
    std::vector<Thread*> leniadores;
    std::vector<Thread*> mineros;

    std::vector<Thread*> cocineros;
    std::vector<Thread*> carpinteros;
    std::vector<Thread*> armeros;

public:
    TP();
    int run(std::string map, std::string trabajadores);
    void spawnTrabajadores();
    void fillQueues();
    void releaseRecolectores();
    void releaseProductores();
    ~TP() = default;

    void mostrarResultados() const;
};

#endif //_TP_H
