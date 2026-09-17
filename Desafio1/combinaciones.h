#ifndef COMBINACIONES_H
#define COMBINACIONES_H


bool yaEstaEnLista(int fila, int columna, int* filasEliminar, int* columnasEliminar, int cantidad);
void detectarHorizontales(unsigned char* tablero, int filas, int columnas, int* filasEliminar, int* columnasEliminar, int* cantidad);
void detectarVerticales(unsigned char* tablero, int filas, int columnas,int* filasEliminar, int* columnasEliminar, int* cantidad);
int eliminarPorCoordenadas(unsigned char* tablero, int* filasEliminar, int* columnasEliminar, int cantidad, int columnas);


#endif // COMBINACIONES_H
