#include "combinaciones.h"
#include "bits.h"


bool yaEstaEnLista(int fila, int columna, int* filasEliminar, int* columnasEliminar, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (filasEliminar[i] == fila && columnasEliminar[i] == columna) {
            return true;
        }
    }
    return false;
}

void detectarHorizontales(unsigned char* tablero, int filas, int columnas,
                          int* filasEliminar, int* columnasEliminar, int* cantidad) {
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
                for (int k = inicio; k <= c; k++) {
                    if (!yaEstaEnLista(f, k, filasEliminar, columnasEliminar, *cantidad)) {
                        filasEliminar[*cantidad] = f;
                        columnasEliminar[*cantidad] = k;
                        (*cantidad)++;
                    }
                }
            }

            c++;
        }
    }
}

void detectarVerticales(unsigned char* tablero, int filas, int columnas,
                        int* filasEliminar, int* columnasEliminar, int* cantidad) {
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
                for (int k = inicio; k <= f; k++) {
                    // ACA esta el paso clave: verificar contra lo que ya dejo la horizontal
                    if (!yaEstaEnLista(k, c, filasEliminar, columnasEliminar, *cantidad)) {
                        filasEliminar[*cantidad] = k;
                        columnasEliminar[*cantidad] = c;
                        (*cantidad)++;
                    }
                }
            }

            f++;
        }
    }
}

int eliminarPorCoordenadas(unsigned char* tablero, int* filasEliminar, int* columnasEliminar,
                           int cantidad, int columnas) {
    for (int i = 0; i < cantidad; i++) {
        int indice = calcularIndice(filasEliminar[i], columnasEliminar[i], columnas);
        escribirFicha(tablero, indice, codigo_vacio);
    }
    return cantidad; // cuantas fichas se eliminaron en total
}