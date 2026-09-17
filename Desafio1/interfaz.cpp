#include "interfaz.h"
#include "tablero.h"
#include <iostream>
using namespace std;


void pedirDimensiones(int* filas, int* columnas) {
    int f, c;

    do {
        cout << "Ingrese el numero de filas (minimo 3): ";
        cin >> f;
    } while (f < 3);

    do {
        cout << "Ingrese el numero de columnas (minimo 3): ";
        cin >> c;
    } while (c < 3);

    *filas = f;
    *columnas = c;
}

int mostrarMenu() {
    int opcion;

    cout << endl;
    cout << "===== MENU =====" << endl;
    cout << "1. Eliminar ficha" << endl;
    cout << "2. Agregar fila" << endl;
    cout << "3. Eliminar fila" << endl;
    cout << "4. Agregar columna" << endl;
    cout << "5. Eliminar columna" << endl;
    cout << "6. Ver tablero en binario" << endl;
    cout << "7. Ver estadisticas" << endl;
    cout << "8. Salir" << endl;
    cout << "Seleccione una opcion: ";

    cin >> opcion;

    while (opcion < 1 || opcion > 8) {
        cout << "Opcion invalida. Intente de nuevo: ";
        cin >> opcion;
    }

    return opcion;
}

void leerMovimiento(int* fila, int* columna, int filas, int columnas) {
    int f, c;

    do {
        cout << "Ingrese la fila de la ficha a eliminar (0 a " << (filas - 1) << "): ";
        cin >> f;
        cout << "Ingrese la columna de la ficha a eliminar (0 a " << (columnas - 1) << "): ";
        cin >> c;

        if (!posicionValida(f, c, filas, columnas)) {
            cout << "Posicion invalida, intente de nuevo." << std::endl;
        }

    } while (!posicionValida(f, c, filas, columnas));

    *fila = f;
    *columna = c;
}