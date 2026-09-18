#include "interfaz.h"
#include "tablero.h"
#include "organizacion.h"
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
    cout << "7. Salir" << endl;
    cout << "Seleccione una opcion: ";

    while (!(cin >> opcion) || opcion < 1 || opcion > 7) {
        cout << "Opcion invalida. Intente de nuevo: ";
        cin.clear();
        cin.ignore(10000, '\n');
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

int calcularPuntuacion(int fichasEliminadasEnEstaCascada) {
    return fichasEliminadasEnEstaCascada;
}

void mostrarEstado(const unsigned char* tablero, int filas, int columnas)
{
    cout << "\n===== TABLERO =====" << endl;
    mostrarTablero(tablero, filas, columnas);
}

void mostrarEstadisticas(int filas, int columnas, int bytesReservados,
                         int eliminacionesUsuario, int fichasEliminadasTotal,
                         int combinacionesTotal, int cascadasActuales,
                         int puntuacion)
{
    cout << "\n===== ESTADISTICAS =====" << endl;
    cout << "Dimensiones: " << filas << " x " << columnas << endl;
    cout << "Bytes reservados: " << bytesReservados << endl;
    cout << "Eliminaciones del usuario: " << eliminacionesUsuario << endl;
    cout << "Fichas eliminadas: " << fichasEliminadasTotal << endl;
    cout << "Combinaciones detectadas: " << combinacionesTotal << endl;
    cout << "Cascadas de la ultima operacion: " << cascadasActuales << endl;
    cout << "Puntuacion: " << puntuacion << endl;
}

void procesarEliminacionUsuario(unsigned char* tablero, int filas, int columnas,
                                int fila, int columna, int* eliminacionesUsuario,
                                int* fichasEliminadasTotal, int* combinacionesTotal,
                                int* cascadasActuales, int* puntuacion) {

    int fichasAntes = *fichasEliminadasTotal;

    eliminarFicha(tablero, fila, columna, columnas);
    (*eliminacionesUsuario)++;
    (*fichasEliminadasTotal)++;

    // Una ficha eliminada deja un espacio: primero se reorganiza el tablero
    // y se completan los vacíos antes de buscar combinaciones automáticas.
    aplicarGravedad(tablero, filas, columnas);
    rellenarVacios(tablero, filas, columnas);

    *cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                         fichasEliminadasTotal, combinacionesTotal);

    int fichasEnEstaJugada = *fichasEliminadasTotal - fichasAntes;
    *puntuacion += calcularPuntuacion(fichasEnEstaJugada);
}
