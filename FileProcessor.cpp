#include "FileProcessor.h"

#include <string>

#define ERROR_FILE -2

FileProcessor::FileProcessor() {
    cant_agricultores = 0;
    cant_leniadores = 0;
    cant_mineros = 0;

    cant_cocineros = 0;
    cant_carpinteros = 0;
    cant_armeros = 0;
}

void FileProcessor::openFiles(std::string map_filename,
                              std::string trabajadores_filename) {
    this->map.open(map_filename);
    if (!this->map.is_open()) throw ERROR_FILE;

    this->trabajadores.open(trabajadores_filename);
    if (!this->trabajadores.is_open()) throw ERROR_FILE;
}

char FileProcessor::getRecurso() {
    return this->map.get();
}

void FileProcessor::processTrabajadores() {
    std::string curr_worker;
    int curr_len = 0;
    while (!this->trabajadores.eof()) {
        std::getline(this->trabajadores, curr_worker, '=');
        this->trabajadores >> curr_len;
        if (curr_worker == "Agricultores") cant_agricultores = curr_len;
        else if (curr_worker == "Leniadores") cant_leniadores = curr_len;
        else if (curr_worker == "Mineros") cant_mineros = curr_len;
        else if (curr_worker == "Cocineros") cant_cocineros = curr_len;
        else if (curr_worker == "Carpinteros") cant_carpinteros = curr_len;
        else if (curr_worker == "Armeros") cant_armeros = curr_len;
        this->trabajadores.get();  //agarra el \n que no me interesa
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

bool FileProcessor::recursosDepleted() {
    return this->map.eof();
}

FileProcessor::~FileProcessor() {
    this->map.close();
    this->trabajadores.close();
}
