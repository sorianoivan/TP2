#include "FileProcessor.h"

#include <string>

FileProcessor::FileProcessor() {
    cant_agricultores = 0;
    cant_leniadores = 0;
    cant_mineros = 0;

    cant_cocineros = 0;
    cant_carpinteros = 0;
    cant_armeros = 0;
}

int FileProcessor::abrirArchivos(const std::string& mapa_filename,
                                 const std::string& trabajadores_filename) {
    this->mapa.open(mapa_filename);
    if (!this->mapa.is_open()){
        std::cerr << "Error abriendo el archivo de mapa" << std::endl;
        return ERROR_ARCHIVO;
    }

    this->trabajadores.open(trabajadores_filename);
    if (!this->trabajadores.is_open()){
        std::cerr << "Error abriendo el archivo de trabajadores" << std::endl;
        return ERROR_ARCHIVO;
    }
    return OK;
}

char FileProcessor::getRecurso() {
    return this->mapa.get();
}

void FileProcessor::processTrabajadores() {
    std::string curr_worker;
    int curr_len = 0;
    while (!this->trabajadores.eof()) {
        //Leo el tipo_productor de trabajador
        std::getline(this->trabajadores, curr_worker, '=');
        //Leo la cantidad de trabajadores del tipo_productor que lei
        this->trabajadores >> curr_len;
        if (curr_worker == "Agricultores") cant_agricultores = curr_len;
        else if (curr_worker == "Leniadores") cant_leniadores = curr_len;
        else if (curr_worker == "Mineros") cant_mineros = curr_len;
        else if (curr_worker == "Cocineros") cant_cocineros = curr_len;
        else if (curr_worker == "Carpinteros") cant_carpinteros = curr_len;
        else if (curr_worker == "Armeros") cant_armeros = curr_len;
        this->trabajadores.get();  //leo el \n que no me interesa
        this->trabajadores.peek(); //este es para ver el EOF y que termine
    }
}

int FileProcessor:: getCantAgricultores() const{
    return this->cant_agricultores;
}

int FileProcessor:: getCantLeniadores() const{
    return this->cant_leniadores;
}

int FileProcessor:: getCantMineros() const{
    return this->cant_mineros;
}

int FileProcessor:: getCantCocineros() const{
    return this->cant_cocineros;
}

int FileProcessor:: getCantCarpinteros() const{
    return this->cant_carpinteros;
}

int FileProcessor:: getCantArmeros() const{
    return this->cant_armeros;
}

bool FileProcessor::recursosTerminados() const{
    return this->mapa.eof();
}

FileProcessor::~FileProcessor() {
    this->mapa.close();
    this->trabajadores.close();
}
