#ifndef _TP_H
#define _TP_H

#include <thread>
#include <vector>

#include "FileProcessor.h"
#include "BlockingQueue.h"
#include "Recursos.h"
#include "Collector.h"
#include "Inventario.h"

class TP {
private:
    int flag;
    FileProcessor file_processor;

    Inventario inventario;

    BlockingQueue agricultores_queue;
    BlockingQueue leniadores_queue;
    BlockingQueue mineros_queue;

    std::vector<Thread*> agricultores;
    std::vector<Thread*> leniadores;
    std::vector<Thread*> mineros;

public:
    TP();
    int run(const char* map, const char* trabajadores);
    void spawnTrabajadores();
    void fillQueues();
    void releaseTrabajadores();
    ~TP();

};


#endif //_TP_H
