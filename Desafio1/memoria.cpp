#include "memoria.h"
#include <new>


unsigned char* ReservarMemoria(int bytes){
    unsigned char* bloque = new (std::nothrow) unsigned char[bytes];
    if (bloque == nullptr) {
        return nullptr;
    }
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

unsigned char* RedimensionarMemoria(int bytesReservadosActual, int bytesNecesariosNuevo,bool esReduccion,
                                    int* bytesReservadosResultado,bool* seNecesitaReemplazarBloque)
{
    if (!esReduccion) {
        *bytesReservadosResultado = bytesNecesariosNuevo;
        *seNecesitaReemplazarBloque = true;
        return ReservarMemoria(bytesNecesariosNuevo);
    }

    // Al eliminar, aplicamos la regla del 65%
    double porcentajeUso = (double)bytesNecesariosNuevo / (double)bytesReservadosActual;

    if (porcentajeUso < 0.65) {
        *bytesReservadosResultado = bytesNecesariosNuevo;
        *seNecesitaReemplazarBloque = true;
        return ReservarMemoria(bytesNecesariosNuevo);
    } else {
        *bytesReservadosResultado = bytesReservadosActual;
        *seNecesitaReemplazarBloque = false;
        return ReservarMemoria(bytesReservadosActual); // buffer temporal, mismo tamaño
    }
}
