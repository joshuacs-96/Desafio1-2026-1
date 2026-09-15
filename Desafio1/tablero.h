#ifndef TABLERO_H
#define TABLERO_H


void generarFicha(unsigned char* tablero, int fila, int columna, int columnas);
bool posicionValida(int fila, int columna, int filas, int columnas);
void eliminarFicha(unsigned char* tablero, int fila, int columna, int columnas);
char simboloDeFicha(unsigned char ficha);
void mostrarTablero(const unsigned char* tablero, int filas, int columnas);
void mostrarBinario(const unsigned char* tablero, int bytesUsados);


#endif // TABLERO_H