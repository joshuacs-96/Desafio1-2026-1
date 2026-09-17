#include "bits.h"
#include "organizacion.h"
#include "combinaciones.h"
#include "tablero.h"

void aplicarGravedad(unsigned char* tablero, int filas, int columnas) {
    for (int c = 0; c < columnas; c++) {
        int filaDestino = filas - 1;

        for (int f = filas - 1; f >= 0; f--) {
            int indiceOrigen = calcularIndice(f, c, columnas);
            unsigned char ficha = obtenerFicha(tablero, indiceOrigen);

            if (ficha != codigo_vacio) {
                if (f != filaDestino) {
                    int indiceDestino = calcularIndice(filaDestino, c, columnas);
                    escribirFicha(tablero, indiceDestino, ficha);
                    escribirFicha(tablero, indiceOrigen, codigo_vacio);
                }
                filaDestino--;
            }
        }
    }
}

void rellenarVacios(unsigned char* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int indice = calcularIndice(f, c, columnas);
            unsigned char ficha = obtenerFicha(tablero, indice);

            if (ficha == codigo_vacio) {
                generarFicha(tablero, f, c, columnas);
            }
        }
    }
}

int procesarCascadas(unsigned char* tablero, int filas, int columnas,
                     int* fichasEliminadasTotal, int* combinacionesTotal) {
    int cascadas = 0;
    bool huboCombinacion = true;

    while (huboCombinacion) {
        int* filasEliminar = new int[filas * columnas];
        int* columnasEliminar = new int[filas * columnas];
        int cantidad = 0;

        detectarHorizontales(tablero, filas, columnas, filasEliminar, columnasEliminar, &cantidad);
        detectarVerticales(tablero, filas, columnas, filasEliminar, columnasEliminar, &cantidad);

        huboCombinacion = (cantidad > 0);

        if (huboCombinacion) {
            int eliminadas = eliminarPorCoordenadas(tablero, filasEliminar, columnasEliminar,
                                                    cantidad, columnas);
            *fichasEliminadasTotal += eliminadas;
            (*combinacionesTotal)++;

            aplicarGravedad(tablero, filas, columnas);
            rellenarVacios(tablero, filas, columnas);

            cascadas++;
        }

        delete[] filasEliminar;
        delete[] columnasEliminar;
    }

    return cascadas;
}