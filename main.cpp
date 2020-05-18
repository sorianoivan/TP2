#include "TP.h"

int main(int argc, char* argv[]) {
    TP tp;
    if (argc == 3) {
       return tp.ejecutar(argv[1], argv[2]);
    } else {
        std::cerr << "Argumentos invalidos" << std::endl;
        return ERROR;
    }
}
