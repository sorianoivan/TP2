#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#include "Recursos.h"
#include "Constantes.h"

class FileProcessor {
private:
    std::ifstream mapa;
    std::ifstream trabajadores;

    int cant_agricultores;
    int cant_leniadores;
    int cant_mineros;

    int cant_cocineros;
    int cant_carpinteros;
    int cant_armeros;

public:
    /* Constructor */
    FileProcessor();

    /* Abre los archivos de mapa y trabajadores. Devuelve 0 si los archivos
     * se abrieron bien y ERROR_ARCHIVO en caso contrario*/
    int abrirArchivos(const std::string& mapa_filename,
                      const std::string& trabajadores_filename);
    /* Procesa el archivo de trabajadores para obtener la cantidad
     * de cada tipo de trabajador*/
    void processTrabajadores();
    /* Devuelve el recurso leido */
    char getRecurso();
    /* Devuelve true si ya no quedan mas recursos por leer */
    bool recursosTerminados() const;

    /* Devuelve la cantidad de agricultores */
    int getCantAgricultores() const;
    /* Devuelve la cantidad de leniadores */
    int getCantLeniadores() const;
    /* Devuelve la cantidad de mineros */
    int getCantMineros() const;
    /* Devuelve la cantidad de cocineros */
    int getCantCocineros() const;
    /* Devuelve la cantidad de carpinteros */
    int getCantCarpinteros() const;
    /* Devuelve la cantidad de armeros */
    int getCantArmeros() const;


    /* Destructor */
    ~FileProcessor();
};

#endif //_FILEREADER_H
