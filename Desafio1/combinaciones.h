#ifndef COMBINACIONES_H
#define COMBINACIONES_H


bool detectarHorizontales(const unsigned char* tablero, int filas, int columnas, bool* marcado);
bool detectarVerticales(const unsigned char* tablero, int filas, int columnas, bool* marcado);
int eliminarMarcadas(unsigned char* tablero, int filas, int columnas, const bool* marcado);


#endif // COMBINACIONES_H
