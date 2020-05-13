#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <iostream>
#include <fstream>
#include <istream>
#include <string>

#include "Recursos.h"

class FileProcessor {
private:
    std::ifstream map;
    std::ifstream trabajadores;

    int cant_agricultores;
    int cant_leniadores;
    int cant_mineros;

    int cant_cocineros;
    int cant_carpinteros;
    int cant_armeros;

public:
    FileProcessor();

    void openFiles(std::string map_filename,
                   std::string trabajadores_filename);

    void processTrabajadores();
    char getRecurso();
    bool recursosDepleted();

    int getCantAgricultores() const;
    int getCantLeniadores() const;
    int getCantMineros() const;
    int getCantCocineros() const;
    int getCantCarpinteros() const;
    int getCantArmeros() const;

    ~FileProcessor();
};


#endif //_FILEREADER_H
