#include "bits.h"
#include <iostream>

using namespace std;

void generarFicha(unsigned char* tablero, int fila, int columna, int columnas) {
    int indice = calcularIndice(fila, columna, columnas);
    unsigned char valorAleatorio = rand() % 6;
    escribirFicha(tablero, indice, valorAleatorio);
}

bool posicionValida(int fila, int columna, int filas, int columnas) {
    if (fila < 0 || fila >= filas) {
        return false;
    }
    if (columna < 0 || columna >= columnas) {
        return false;
    }
    return true;
}

void eliminarFicha(unsigned char* tablero, int fila, int columna, int columnas) {
    int indice = calcularIndice(fila, columna, columnas);
    escribirFicha(tablero, indice, codigo_vacio);
}

const char SIMBOLOS[6] = {'/', '*', '?', '=', '$', '%'};
char simboloDeFicha(unsigned char ficha) {
    if (ficha == codigo_vacio) return '.';
    if (ficha < 6) return SIMBOLOS[ficha];
    return '!';
}

void mostrarTablero(const unsigned char* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int indice = calcularIndice(f, c, columnas);
            unsigned char ficha = obtenerFicha(tablero, indice);
            cout << simboloDeFicha(ficha) << " ";
        }
        cout << endl;
    }
}

void mostrarBinario(const unsigned char* tablero, int bytesUsados) {
    for (int i = 0; i < bytesUsados; i++) {
        cout << "Byte " << i << ": ";
        for (int bit = 7; bit >= 0; bit--) {
            unsigned char mascara = 1 << bit;
            if (tablero[i] & mascara) {
                cout << "1";
            } else {
                cout << "0";
            }
        }
        cout << endl;
    }
}