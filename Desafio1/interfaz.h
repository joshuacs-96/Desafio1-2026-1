#ifndef INTERFAZ_H
#define INTERFAZ_H


void pedirDimensiones(int* filas, int* columnas);
int mostrarMenu();
void leerMovimiento(int* fila, int* columna, int filas, int columnas);
int calcularPuntuacion(int fichasEliminadasEnEstaCascada);
void procesarEliminacionUsuario(unsigned char* tablero, int filas, int columnas, int fila, int columna, int* eliminacionesUsuario, int* fichasEliminadasTotal, int* combinacionesTotal, int* cascadasActuales, int* puntuacion);
void mostrarEstado(const unsigned char* tablero, int filas, int columnas);
void mostrarEstadisticas(int filas, int columnas, int bytesReservados,
                         int eliminacionesUsuario, int fichasEliminadasTotal,
                         int combinacionesTotal, int cascadasActuales,
                         int puntuacion);

#endif // INTERFAZ_H
