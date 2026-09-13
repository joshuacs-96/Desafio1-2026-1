#include "memoria.h"


unsigned char* ReservarMemoria(int bytes){
    unsigned char* bloque = new unsigned char[bytes];
    for (int i = 0; i < bytes; i++) {
        bloque[i] = 0;
    }
    return bloque;
}

void LiberarMemoria(unsigned char*&tablero){
    delete[] tablero;
    tablero = nullptr;
}

void CopiarBytes(unsigned char* destino, const unsigned char* origen, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        destino[i] = origen[i];
    }
}

unsigned char* RedimensionarMemoria(unsigned char* actual, int bytesActuales, int bytesNuevos) {

    unsigned char* nuevo = ReservarMemoria(bytesNuevos);
    int aCopiar = bytesActuales;

    if (bytesNuevos < bytesActuales) {
        aCopiar = bytesNuevos;
    }

    CopiarBytes(nuevo, actual, aCopiar);
    LiberarMemoria(actual);

    return nuevo;
}
