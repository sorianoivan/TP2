#include "TP.h"

#include <string>
#include <vector>

TP::TP() {
    flag = 0;
}

int TP::ejecutar(const std::string& mapa, const std::string& trabajadores) {
    flag = file_processor.abrirArchivos(trabajadores, mapa);
    if (flag != 0) return ERROR;

    _invocarTrabajadores();

    _llenarColasDeRecursos();

    _finalizar();

    _mostrarResultados();

    return OK;
}

/* Crea "cant" de recolectores con su respectiva cola bloqueante
     * y se guardan en "vector" */
void TP::_crearRecolectores(const int cant, std::vector<Thread*>& vector,
                            ColaBloqueante& cola_recolector){
    for (int i = 0; i < cant; ++i) {
        vector.push_back(new Recolector(cola_recolector, inventario));
        vector[i]->start();
    }
}

/* Crea "cant" de productores "tipo_productor" que se guardan en "vector" */
void TP::_crearProductores(const int cant, std::vector<Thread*>& vector,
                           const int tipo){
    for (int i = 0; i < cant; ++i) {
        vector.push_back(new Productor(inventario, puntos, tipo));
        vector[i]->start();
    }
}

/* Invoca recolectores y productores */
void TP::_invocarTrabajadores() {
    file_processor.processTrabajadores();

    _crearRecolectores(file_processor.getCantAgricultores(), agricultores,
                       cola_agricultores);
    _crearRecolectores(file_processor.getCantLeniadores(), leniadores,
                       cola_leniadores);
    _crearRecolectores(file_processor.getCantMineros(), mineros,
                       cola_mineros);

    _crearProductores(file_processor.getCantCocineros(), cocineros, COCINERO);
    _crearProductores(file_processor.getCantCarpinteros(), carpinteros,
            CARPINTERO);
    _crearProductores(file_processor.getCantArmeros(), armeros, ARMERO);
}

/* Llena las colas bloqueantes con los recursos leidos del mapa.
* Esta funcion se pasa de las 20 lineas unicamente por la estructura switch
* por lo que no veo razon por la cual se deberia modularizar mas */
void TP::_llenarColasDeRecursos() {
    char curr_recurso;
    while (!file_processor.recursosTerminados()){
        curr_recurso = file_processor.getRecurso();
        switch (curr_recurso) {
            case 'T':
                cola_agricultores.depositar(Trigo);
                break;
            case 'M':
                cola_leniadores.depositar(Madera);
                break;
            case 'C':
                cola_mineros.depositar(Carbon);
                break;
            case 'H':
                cola_mineros.depositar(Hierro);
                break;
            default :
                break;
        }
    }
    cola_agricultores.cerrar();
    cola_leniadores.cerrar();
    cola_mineros.cerrar(); //ver de poner las colas en un vector
}

/* Finaliza el proceso de llenar el inventario y
 * sumar los puntos de beneficio */
void TP::_finalizar() {
    _liberarTrabajadores(file_processor.getCantAgricultores(), agricultores);
    _liberarTrabajadores(file_processor.getCantLeniadores(), leniadores);
    _liberarTrabajadores(file_processor.getCantMineros(), mineros);

    inventario.cerrar();

    _liberarTrabajadores(file_processor.getCantCocineros(), cocineros);
    _liberarTrabajadores(file_processor.getCantCarpinteros(), carpinteros);
    _liberarTrabajadores(file_processor.getCantArmeros(), armeros);
}

/* Libera los recursos pertenecientes a los recolectores y productores */
void TP::_liberarTrabajadores(const int cant, std::vector<Thread*> vector) {
    for (int i = 0; i < cant; ++i) {
        vector[i]->join();
        delete vector[i];
    }
}

/* Muestra los resultados en el formato requerido */
void TP::_mostrarResultados() const {
    std::cout << "Recursos restantes:" << std::endl;
    std::cout << "  - Trigo: " << inventario.getCantTrigo() << std::endl;
    std::cout << "  - Madera: " << inventario.getCantMadera() << std::endl;
    std::cout << "  - Carbon: " << inventario.getCantCarbon() << std::endl;
    std::cout << "  - Hierro: " << inventario.getCantHierro() << std::endl;

    std::cout << std::endl << "Puntos de Beneficio acumulados: " <<
        puntos.getPuntos() << std::endl;
}

TP::~TP() {}
