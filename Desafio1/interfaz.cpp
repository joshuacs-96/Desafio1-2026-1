#include "interfaz.h"
#include "tablero.h"
#include "organizacion.h"
#include <iostream>
using namespace std;

int leerEnteroMinimo(const char* mensaje, int minimo)
{
    int valor;

    while (true) {
        cout << mensaje << " (minimo " << minimo << "): ";

        if (cin >> valor) {
            cin.ignore(10000, '\n');
            if (valor >= minimo) {
                return valor;
            }
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Entrada invalida. Intente de nuevo." << endl;
    }
}

int leerEnteroEnRango(const char* mensaje, int minimo, int maximo)
{
    int valor;

    while (true) {
        cout << mensaje << " (" << minimo << " a " << maximo << "): ";

        if (cin >> valor) {
            cin.ignore(10000, '\n');
            if (valor >= minimo && valor <= maximo) {
                return valor;
            }
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Entrada invalida. Intente de nuevo." << endl;
    }
}


void pedirDimensiones(int* filas, int* columnas) {
    *filas = leerEnteroMinimo("Ingrese el numero de filas", 3);
    *columnas = leerEnteroMinimo("Ingrese el numero de columnas", 3);
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
    opcion = leerEnteroEnRango("Seleccione una opcion", 1, 7);

    return opcion;
}

void leerMovimiento(int* fila, int* columna, int filas, int columnas) {
    *fila = leerEnteroEnRango("Ingrese la fila de la ficha a eliminar", 0, filas - 1);
    *columna = leerEnteroEnRango("Ingrese la columna de la ficha a eliminar", 0, columnas - 1);
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
                         int combinacionesTotal, int cascadasActuales, int cascadasTotales,
                         int puntuacion)
{
    cout << "\n===== ESTADISTICAS =====" << endl;
    cout << "Dimensiones: " << filas << " x " << columnas << endl;
    cout << "Bytes reservados: " << bytesReservados << endl;
    cout << "Eliminaciones del usuario: " << eliminacionesUsuario << endl;
    cout << "Fichas eliminadas: " << fichasEliminadasTotal << endl;
    cout << "Combinaciones detectadas: " << combinacionesTotal << endl;
    cout << "Cascadas de la ultima operacion: " << cascadasActuales << endl;
    cout << "Cascadas acumuladas: " << cascadasTotales << endl;
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
