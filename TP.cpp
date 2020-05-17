#include "TP.h"

TP::TP() {
    flag = 0;
}

int TP::ejecutar(const std::string& mapa, const std::string& trabajadores) {
    flag = file_processor.abrirArchivos(trabajadores, mapa);
    if (flag != 0) return ERROR;

    invocarTrabajadores();

    llenarColasDeRecursos();

    finalizar();

    mostrarResultados();

    return OK;
}

void TP::crearRecolectores(int cant, std::vector<Thread*>& vector,
                           ColaBloqueante& queue){
    for (int i = 0; i < cant; ++i) {
        vector.push_back(new Recolector(queue, inventario));
        vector[i]->start();
    }
}

void TP::crearProductores(int cant, std::vector<Thread*>& vector,
        int tipo){
    for (int i = 0; i < cant; ++i) {
        vector.push_back(new Productor(inventario, puntos, tipo));
        vector[i]->start();
    }
}

void TP::invocarTrabajadores() {
    file_processor.processTrabajadores();

    crearRecolectores(file_processor.getCantAgricultores(), agricultores,
                      cola_agricultores);
    crearRecolectores(file_processor.getCantLeniadores(), leniadores,
                      cola_leniadores);
    crearRecolectores(file_processor.getCantMineros(), mineros,
                      cola_mineros);

    crearProductores(file_processor.getCantCocineros(), cocineros, COCINERO);
    crearProductores(file_processor.getCantCarpinteros(), carpinteros, CARPINTERO);
    crearProductores(file_processor.getCantArmeros(), armeros, ARMERO);

}

void TP::llenarColasDeRecursos() {
    char curr_recurso;
    while (!file_processor.recursosTerminados()){
        curr_recurso = file_processor.getRecurso();
        switch (curr_recurso) {
            case 'T':
                cola_agricultores.push(Trigo);
                break;
            case 'M':
                cola_leniadores.push(Madera);
                break;
            case 'C':
                cola_mineros.push(Carbon);
                break;
            case 'H':
                cola_mineros.push(Hierro);
                break;
            default :
                break;
        }
    }
    cola_agricultores.cerrar();
    cola_leniadores.cerrar();
    cola_mineros.cerrar(); //ver de poner las colas en un vector
}

void TP::finalizar() {
    liberarTrabajadores(file_processor.getCantAgricultores(), agricultores);
    liberarTrabajadores(file_processor.getCantLeniadores(), leniadores);
    liberarTrabajadores(file_processor.getCantMineros(), mineros);

    inventario.cerrar();

    liberarTrabajadores(file_processor.getCantCocineros(), cocineros);
    liberarTrabajadores(file_processor.getCantCarpinteros(), carpinteros);
    liberarTrabajadores(file_processor.getCantArmeros(), armeros);
}

void TP::liberarTrabajadores(int cant, std::vector<Thread*> vector) {
    for (int i = 0; i < cant; ++i) {
        vector[i]->join();
        delete vector[i];
    }
}

void TP::mostrarResultados() const {
    std::cout << "Recursos restantes:" << std::endl;
    std::cout << "  - Trigo: " << inventario.getCantTrigo() << std::endl;
    std::cout << "  - Madera: " << inventario.getCantMadera() << std::endl;
    std::cout << "  - Carbon: " << inventario.getCantCarbon() << std::endl;
    std::cout << "  - Hierro: " << inventario.getCantHierro() << std::endl;

    std::cout << std::endl << "Puntos de Beneficio acumulados: " <<
        puntos.getPuntos() << std::endl;
}
