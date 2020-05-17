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

    int getCantAgricultores() const;
    int getCantLeniadores() const;
    int getCantMineros() const;
    int getCantCocineros() const;
    int getCantCarpinteros() const;
    int getCantArmeros() const;

    /* Cierra los archivos */
    ~FileProcessor();
};


#endif //_FILEREADER_H
