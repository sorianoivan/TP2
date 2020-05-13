#include "TP.h"

#include <string>

#define ERROR_FILE -2
#define ERROR 1

TP::TP() {
    flag = 0;
}

int TP::run(std::string map, std::string trabajadores) {
    try{
        file_processor.openFiles(std::move(map), std::move(trabajadores));
    } catch(int e) {flag = ERROR_FILE;}
    if (flag != 0) return ERROR;

    spawnTrabajadores();
    fillQueues();
    releaseRecolectores();

    releaseProductores();

    mostrarResultados();

    return 0;
}

void TP::spawnTrabajadores() {
    file_processor.processTrabajadores();
    for (int i = 0; i < file_processor.getCantAgricultores(); ++i) {
        agricultores.push_back(new Collector(agricultores_queue, inventario));
        agricultores[i]->start();
    }

    for (int i = 0; i < file_processor.getCantLeniadores(); ++i) {
        leniadores.push_back(new Collector(leniadores_queue, inventario));
        leniadores[i]->start();
    }

    for (int i = 0; i < file_processor.getCantMineros(); ++i) {
        mineros.push_back(new Collector(mineros_queue, inventario));
        mineros[i]->start();
    }

    for (int i = 0; i < file_processor.getCantCocineros(); ++i) {
        cocineros.push_back(new Cocinero(inventario, puntos));
        cocineros[i]->start();
    }

    for (int i = 0; i < file_processor.getCantCarpinteros(); ++i) {
        carpinteros.push_back(new Carpintero(inventario, puntos));
        carpinteros[i]->start();
    }

    for (int i = 0; i < file_processor.getCantArmeros(); ++i) {
        armeros.push_back(new Armero(inventario, puntos));
        armeros[i]->start();
    }
}

void TP::releaseRecolectores() {
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
    inventario.close();
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
    mineros_queue.close(); //ver de poner las colas en un vector
}

void TP::releaseProductores() {
    for (int i = 0; i < file_processor.getCantCocineros(); ++i) {
        cocineros[i]->join();
        delete cocineros[i];
    }

    for (int i = 0; i < file_processor.getCantCarpinteros(); ++i) {
        carpinteros[i]->join();
        delete carpinteros[i];
    }

    for (int i = 0; i < file_processor.getCantArmeros(); ++i) {
        armeros[i]->join();
        delete armeros[i];
    }
}

void TP::mostrarResultados() const {
    std::cout << "Recursos Restantes:" << std::endl;
    std::cout << "  - Trigo: " << inventario.getCantTrigo() << std::endl;
    std::cout << "  - Madera: " << inventario.getCantMadera() << std::endl;
    std::cout << "  - Carbon: " << inventario.getCantCarbon() << std::endl;
    std::cout << "  - Hierro: " << inventario.getCantHierro() << std::endl;

    std::cout << std::endl << "Puntos de Beneficio acumulados: " <<
        puntos.getPuntos() << std::endl;
}
