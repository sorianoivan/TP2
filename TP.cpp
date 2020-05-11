#include "TP.h"

#define ERROR_FILE -2
#define ERROR 1

TP::TP() {
    flag = 0;
}

int TP::run(const char *map, const char *trabajadores) {
    try{
        file_processor.openFiles(map, trabajadores);
    } catch (int e) { flag = ERROR_FILE; }
    if(flag != 0) return ERROR;

    spawnTrabajadores(); // falta agregar aca los productores
    fillQueues();
    releaseTrabajadores();

    return 0;
}

TP::~TP() {
    //do nothing
}

void TP::spawnTrabajadores() {
    file_processor.processTrabajadores();
    for (int i = 0; i < file_processor.getCantAgricultores(); ++i) {
        agricultores.push_back(new Collector(agricultores_queue));
        agricultores[i]->start();
    }

    for (int i = 0; i < file_processor.getCantLeniadores(); ++i) {
        leniadores.push_back(new Collector(leniadores_queue));
        leniadores[i]->start();
    }

    for (int i = 0; i < file_processor.getCantMineros(); ++i) {
        mineros.push_back(new Collector(mineros_queue));
        mineros[i]->start();
    }
}

void TP::releaseTrabajadores() {
    for (int i = 0; i < file_processor.getCantAgricultores(); ++i) {
        agricultores[i]->join();
        delete agricultores[i];
    }

    for (int i = 0; i < file_processor.getCantLeniadores(); ++i) {
        leniadores[i]->join();
        delete leniadores[i];
    }

    for (int i = 0; i < file_processor.getCantMineros(); ++i) {
        mineros[i]->join();
        delete mineros[i];
    }
}

void TP::fillQueues() {
    char curr_recurso;
    while (!file_processor.recursosDepleted()){
        curr_recurso = file_processor.getRecurso();
        switch (curr_recurso) {
            case 'T':
                agricultores_queue.push(Trigo);
                break;
            case 'M':
                leniadores_queue.push(Madera);
                break;
            case 'C':
                mineros_queue.push(Carbon);
                break;
            case 'H':
                mineros_queue.push(Hierro);
                break;
            default :
                break;
        }
    }
    agricultores_queue.close();
    leniadores_queue.close();
    mineros_queue.close();
}
