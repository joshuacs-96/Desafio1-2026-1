#ifndef ORGANIZACION_H
#define ORGANIZACION_H


void aplicarGravedad(unsigned char* tablero, int filas, int columnas);
void rellenarVacios(unsigned char* tablero, int filas, int columnas);
int procesarCascadas(unsigned char* tablero, int filas, int columnas, int* fichasEliminadasTotal, int* combinacionesTotal);


#endif // ORGANIZACION_H
