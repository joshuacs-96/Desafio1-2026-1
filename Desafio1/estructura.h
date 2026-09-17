#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H


unsigned char* agregarFila(unsigned char* tablero, int* filas, int columnas, int filaPos, int* bytesReservados);
unsigned char* eliminarFila(unsigned char* tablero, int* filas, int columnas, int filaPos, int* bytesReservado);
unsigned char* agregarColumna(unsigned char* tablero, int filas, int columnas,int columnaNueva, int bytesReservadosActual, int* bytesReservadosNuevo);
unsigned char* eliminarColumna(unsigned char* tablero, int filas, int columnas,int columnaAEliminar, int bytesReservadosActual, int* bytesReservadosNuevo);

#endif // ESTRUCTURA_H
