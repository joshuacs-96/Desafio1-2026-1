#ifndef BITS_H
#define BITS_H


const unsigned char FICHA_0 = 0b000; // ficha 0
const unsigned char FICHA_1 = 0b001; // ficha 1
const unsigned char FICHA_2 = 0b010; // ficha 2
const unsigned char FICHA_3 = 0b011; // ficha 3
const unsigned char FICHA_4 = 0b100; // ficha 4
const unsigned char FICHA_5 = 0b101; // ficha 5
const unsigned char codigo_vacio = 0b110; // ficha 6
//comodin ficha 7 = 0b111

int calcularIndice(int fila, int columna, int columnas);
int calcularBitInicial(int indice);
int cacularByte(int bitInical);
int calcularOffset(int bitInical);
int bytesNecesarios(int filas, int columnas);
unsigned char obtenerFicha(const unsigned char* tablero, int indice);
void escribirFicha(unsigned char* tablero, int indice, unsigned char valor);


#endif // BITS_H
