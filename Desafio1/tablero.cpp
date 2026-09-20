#include "bits.h"
#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;
const char SIMBOLOS[6] = {'/', '*', '?', '=', '$', '%'};

void generarFicha(unsigned char* tablero, int fila, int columna, int columnas) {
    int indice = calcularIndice(fila, columna, columnas);
    int limite = RAND_MAX - (RAND_MAX % 6);
    int numeroAleatorio;
    do {
        numeroAleatorio = rand();
    } while (numeroAleatorio >= limite);
    unsigned char valorAleatorio = static_cast<unsigned char>(numeroAleatorio % 6);
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

char simboloDeFicha(unsigned char ficha) {
    if (ficha == codigo_vacio) return '.';
    if (ficha < 6) return SIMBOLOS[ficha];
    return '!';
}

void mostrarTablero(const unsigned char* tablero, int filas, int columnas) {
    cout << "     ";
    for (int c = 0; c < columnas; c++) {
        cout << left << setw(3) << c;
    }
    cout << right;
    cout << endl;

    for (int f = 0; f < filas; f++) {
        cout << setw(2) << f << " | ";
        for (int c = 0; c < columnas; c++) {
            int indice = calcularIndice(f, c, columnas);
            unsigned char ficha = obtenerFicha(tablero, indice);
            cout << simboloDeFicha(ficha) << "  ";
        }
        cout << endl;
    }
}

void mostrarBinario(const unsigned char* tablero, int filas, int columnas) {
    cout << "\n===== TABLERO EN BITS =====" << endl;
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int indice = calcularIndice(f, c, columnas);
            unsigned char ficha = obtenerFicha(tablero, indice);

            for (int bit = 2; bit >= 0; bit--) {
                cout << ((ficha >> bit) & 1);
            }
            cout << " ";
        }
        cout << endl;
    }
}
