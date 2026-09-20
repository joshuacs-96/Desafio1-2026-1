#ifndef COMBINACIONES_H
#define COMBINACIONES_H


void detectarHorizontales(unsigned char* tablero, int filas, int columnas,
                          bool* marcarEliminar,
                          int* combinacionesDetectadas);
void detectarVerticales(unsigned char* tablero, int filas, int columnas,
                        bool* marcarEliminar,
                        int* combinacionesDetectadas);
int eliminarMarcadas(unsigned char* tablero, const bool* marcarEliminar,
                     int totalFichas);


#endif // COMBINACIONES_H
