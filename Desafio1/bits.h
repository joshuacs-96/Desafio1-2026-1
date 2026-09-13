#ifndef BITS_H
#define BITS_H


const unsigned char FICHA_0 = 0;
const unsigned char FICHA_1 = 1;
const unsigned char FICHA_2 = 2;
const unsigned char FICHA_3 = 3;
const unsigned char FICHA_4 = 4;
const unsigned char FICHA_5 = 5;
const unsigned char codigo_vacio = 6;

int calcularIndice(int fila, int columna, int columnas);
int calcularBitInicial(int indice);
int cacularByte(int bitInical);
int calcularOffset(int bitInical);
int bytesNecesarios(int filas, int columnas);
unsigned char obtenerFicha(const unsigned char* tablero, int indice);
void escribirFicha(unsigned char* tablero, int indice, unsigned char valor);

#endif // BITS_H
