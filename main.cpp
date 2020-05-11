#include "TP.h"

int main(int argc, char* argv[]) {
    TP tp;
    if (argc == 3) {
       return tp.run(argv[1], argv[2]);
    } else {
        return 1;
    }
}
