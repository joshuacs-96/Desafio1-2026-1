#include "combinaciones.h"
#include "bits.h"


void detectarHorizontales(unsigned char* tablero, int filas, int columnas,
                          bool* marcarEliminar,
                          int* combinacionesDetectadas) {
    for (int f = 0; f < filas; f++) {
        int c = 0;
        while (c < columnas) {
            unsigned char fichaActual = obtenerFicha(tablero, calcularIndice(f, c, columnas));

            if (fichaActual == codigo_vacio) {
                c++;
                continue;
            }

            int inicio = c;
            int largo = 1;

            while (c + 1 < columnas &&
                   obtenerFicha(tablero, calcularIndice(f, c + 1, columnas)) == fichaActual) {
                largo++;
                c++;
            }

            if (largo >= 3) {
                (*combinacionesDetectadas)++;
                for (int k = inicio; k <= c; k++) {
                    int indice = calcularIndice(f, k, columnas);
                    marcarEliminar[indice] = true;
                }
            }

            c++;
        }
    }
}

void detectarVerticales(unsigned char* tablero, int filas, int columnas,
                        bool* marcarEliminar,
                        int* combinacionesDetectadas) {
    for (int c = 0; c < columnas; c++) {
        int f = 0;
        while (f < filas) {
            unsigned char fichaActual = obtenerFicha(tablero, calcularIndice(f, c, columnas));

            if (fichaActual == codigo_vacio) {
                f++;
                continue;
            }

            int inicio = f;
            int largo = 1;

            while (f + 1 < filas &&
                   obtenerFicha(tablero, calcularIndice(f + 1, c, columnas)) == fichaActual) {
                largo++;
                f++;
            }

            if (largo >= 3) {
                (*combinacionesDetectadas)++;
                for (int k = inicio; k <= f; k++) {
                    int indice = calcularIndice(k, c, columnas);
                    marcarEliminar[indice] = true;
                }
            }

            f++;
        }
    }
}

int eliminarMarcadas(unsigned char* tablero, const bool* marcarEliminar,
                     int totalFichas) {
    int eliminadas = 0;

    for (int indice = 0; indice < totalFichas; indice++) {
        if (marcarEliminar[indice]) {
            escribirFicha(tablero, indice, codigo_vacio);
            eliminadas++;
        }
    }

    return eliminadas;
}
