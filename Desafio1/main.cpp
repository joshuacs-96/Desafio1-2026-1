#include <iostream>
#include "tablero.h"
#include "memoria.h"
#include "bits.h"
#include "interfaz.h"
#include "estructura.h"
#include "organizacion.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    int filas;
    int columnas;
    pedirDimensiones(&filas, &columnas);

    int bytesReservados = bytesNecesarios(filas, columnas);
    unsigned char* tablero = ReservarMemoria(bytesReservados);

    if (tablero == nullptr) {
        cout << "No fue posible reservar memoria para el tablero." << endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            generarFicha(tablero, f, c, columnas);
        }
    }

    int eliminacionesUsuario = 0;
    int fichasEliminadasTotal = 0;
    int combinacionesTotal = 0;
    int cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                            &fichasEliminadasTotal,
                                            &combinacionesTotal);
    int puntuacion = fichasEliminadasTotal;

    int opcion;
    do {
        mostrarEstado(tablero, filas, columnas);
        mostrarEstadisticas(filas, columnas, bytesReservados,
                            eliminacionesUsuario, fichasEliminadasTotal,
                            combinacionesTotal, cascadasActuales,
                            puntuacion);
        opcion = mostrarMenu();
        cascadasActuales = 0;

        if (opcion == 1) {
            int fila;
            int columna;
            leerMovimiento(&fila, &columna, filas, columnas);
            procesarEliminacionUsuario(tablero, filas, columnas, fila, columna,
                                      &eliminacionesUsuario,
                                      &fichasEliminadasTotal,
                                      &combinacionesTotal,
                                      &cascadasActuales, &puntuacion);
        }
        else if (opcion == 2) {
            int posicion;
            cout << "Posicion para insertar la fila (0 a " << filas << "): ";
            cin >> posicion;
            if (posicion >= 0 && posicion <= filas) {
                tablero = agregarFila(tablero, &filas, columnas, posicion,
                                      &bytesReservados);
                cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                    &fichasEliminadasTotal,
                                                    &combinacionesTotal);
                puntuacion = fichasEliminadasTotal;
            } else {
                cout << "Posicion invalida." << endl;
            }
        }
        else if (opcion == 3) {
            int posicion;
            cout << "Fila a eliminar (0 a " << (filas - 1) << "): ";
            cin >> posicion;
            if (posicion >= 0 && posicion < filas && filas > 1) {
                tablero = eliminarFila(tablero, &filas, columnas, posicion,
                                       &bytesReservados);
                cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                    &fichasEliminadasTotal,
                                                    &combinacionesTotal);
                puntuacion = fichasEliminadasTotal;
            } else {
                cout << "No se puede eliminar esa fila." << endl;
            }
        }
        else if (opcion == 4) {
            int posicion;
            cout << "Posicion para insertar la columna (0 a " << columnas << "): ";
            cin >> posicion;
            if (posicion >= 0 && posicion <= columnas) {
                unsigned char* tableroNuevo = agregarColumna(
                    tablero, filas, columnas, posicion, bytesReservados,
                    &bytesReservados);
                if (tableroNuevo != nullptr) {
                    tablero = tableroNuevo;
                    columnas++;
                    cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                        &fichasEliminadasTotal,
                                                        &combinacionesTotal);
                    puntuacion = fichasEliminadasTotal;
                } else {
                    cout << "No fue posible ampliar el tablero." << endl;
                }
            } else {
                cout << "Posicion invalida." << endl;
            }
        }
        else if (opcion == 5) {
            int posicion;
            cout << "Columna a eliminar (0 a " << (columnas - 1) << "): ";
            cin >> posicion;
            if (posicion >= 0 && posicion < columnas && columnas > 1) {
                unsigned char* tableroNuevo = eliminarColumna(
                    tablero, filas, columnas, posicion, bytesReservados,
                    &bytesReservados);
                if (tableroNuevo != nullptr) {
                    tablero = tableroNuevo;
                    columnas--;
                    cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                        &fichasEliminadasTotal,
                                                        &combinacionesTotal);
                    puntuacion = fichasEliminadasTotal;
                } else {
                    cout << "No fue posible reducir el tablero." << endl;
                }
            } else {
                cout << "No se puede eliminar esa columna." << endl;
            }
        }
        else if (opcion == 6) {
            mostrarBinario(tablero, bytesReservados);
        }
    } while (opcion != 7);

    LiberarMemoria(tablero);
    cout << "Gracias por jugar Sweet Crush." << endl;
    return 0;
}
