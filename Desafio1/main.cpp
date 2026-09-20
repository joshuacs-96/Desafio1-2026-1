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
    int cascadasTotales = cascadasActuales;
    int puntuacion = fichasEliminadasTotal;

    int opcion;
    do {
        mostrarEstado(tablero, filas, columnas);
        mostrarEstadisticas(filas, columnas, bytesReservados,
                            eliminacionesUsuario, fichasEliminadasTotal,
                            combinacionesTotal, cascadasActuales, cascadasTotales,
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
            cascadasTotales += cascadasActuales;
        }
        else if (opcion == 2) {
            int posicion = leerEnteroEnRango(
                "Posicion para insertar la fila", 0, filas);
            int fichasAntes = fichasEliminadasTotal;
            tablero = agregarFila(tablero, &filas, columnas, posicion,
                                  &bytesReservados);
            cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                &fichasEliminadasTotal,
                                                &combinacionesTotal);
            cascadasTotales += cascadasActuales;
            puntuacion += calcularPuntuacion(
                fichasEliminadasTotal - fichasAntes);
        }
        else if (opcion == 3) {
            if (filas > 3) {
                int posicion = leerEnteroEnRango("Fila a eliminar", 0, filas - 1);
                int fichasAntes = fichasEliminadasTotal;
                tablero = eliminarFila(tablero, &filas, columnas, posicion,
                                       &bytesReservados);
                cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                    &fichasEliminadasTotal,
                                                    &combinacionesTotal);
                cascadasTotales += cascadasActuales;
                puntuacion += calcularPuntuacion(
                    fichasEliminadasTotal - fichasAntes);
            } else {
                cout << "El tablero debe conservar al menos 3 filas." << endl;
            }
        }
        else if (opcion == 4) {
            int posicion = leerEnteroEnRango(
                "Posicion para insertar la columna", 0, columnas);
            int fichasAntes = fichasEliminadasTotal;
            unsigned char* tableroNuevo = agregarColumna(
                tablero, filas, columnas, posicion, bytesReservados,
                &bytesReservados);
            if (tableroNuevo != nullptr) {
                tablero = tableroNuevo;
                columnas++;
                cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                    &fichasEliminadasTotal,
                                                    &combinacionesTotal);
                cascadasTotales += cascadasActuales;
                puntuacion += calcularPuntuacion(
                    fichasEliminadasTotal - fichasAntes);
            } else {
                cout << "No fue posible ampliar el tablero." << endl;
            }
        }
        else if (opcion == 5) {
            if (columnas > 3) {
                int posicion = leerEnteroEnRango("Columna a eliminar", 0, columnas - 1);
                int fichasAntes = fichasEliminadasTotal;
                unsigned char* tableroNuevo = eliminarColumna(
                    tablero, filas, columnas, posicion, bytesReservados,
                    &bytesReservados);
                if (tableroNuevo != nullptr) {
                    tablero = tableroNuevo;
                    columnas--;
                    cascadasActuales = procesarCascadas(tablero, filas, columnas,
                                                        &fichasEliminadasTotal,
                                                        &combinacionesTotal);
                    cascadasTotales += cascadasActuales;
                    puntuacion += calcularPuntuacion(
                        fichasEliminadasTotal - fichasAntes);
                } else {
                    cout << "No fue posible reducir el tablero." << endl;
                }
            } else {
                cout << "El tablero debe conservar al menos 3 columnas." << endl;
            }
        }
        else if (opcion == 6) {
            mostrarBinario(tablero, filas, columnas);
        }
    } while (opcion != 7);

    LiberarMemoria(tablero);
    cout << "Gracias por jugar Sweet Crush." << endl;
    return 0;
}
