#include "bits.h"


int calcularIndice(int fila, int columna, int columnas)
{
    return fila * columnas + columna;
}

int calcularBitInicial(int indice)
{
    return indice * 3;
}

int calcularByte(int bitInicial)
{
    return bitInicial / 8;
}

int calcularOffset(int bitInicial)
{
    return bitInicial % 8;
}

int bytesNecesarios(int filas, int columnas)
{
    int totalBits = filas * columnas * 3;

    return (totalBits + 7) / 8;
}

unsigned char obtenerFicha(const unsigned char* tablero,int indice)
{
    int bitInicial = calcularBitInicial(indice);
    int byteInicial = calcularByte(bitInicial);
    int offset = calcularOffset(bitInicial);

    unsigned int bloque;

    // Caso 1:
    // Los 3 bits caben completamente dentro del mismo byte.
    if (offset <= 5)
    {
        bloque = tablero[byteInicial];

        bloque = bloque >> offset;

        return static_cast<unsigned char>(bloque & 0b00000111);
    }

    // Caso 2:
    // La ficha está dividida entre dos bytes.
    bloque = tablero[byteInicial];

    bloque = bloque |
             (static_cast<unsigned int>(tablero[byteInicial + 1]) << 8);

    bloque = bloque >> offset;

    return static_cast<unsigned char>(bloque & 0b00000111);
}

void escribirFicha(unsigned char* tablero,int indice,unsigned char valor)
{
    // Nos aseguramos de utilizar únicamente los 3 bits
    // menos significativos del valor recibido.
    valor = valor & 0b00000111;

    int bitInicial = calcularBitInicial(indice);
    int byteInicial = calcularByte(bitInicial);
    int offset = calcularOffset(bitInicial);

    // Caso 1:
    // La ficha cabe completamente en un solo byte.
    if (offset <= 5)
    {
        unsigned char mascara =
            static_cast<unsigned char>(0b00000111 << offset);

        // limpiamos los 3 bits donde irá la ficha.
        tablero[byteInicial] =
            tablero[byteInicial] &
            static_cast<unsigned char>(~mascara);

        // Luego escribimos el valor nuevo.
        tablero[byteInicial] =
            tablero[byteInicial] |
            static_cast<unsigned char>(valor << offset);

        return;
    }

    // Caso 2:
    // La ficha cruza entre dos bytes.
    unsigned int bloque =
        static_cast<unsigned int>(tablero[byteInicial]) |
        (static_cast<unsigned int>(tablero[byteInicial + 1]) << 8);

    unsigned int mascara =
        0b00000111u << offset;

    // Limpia únicamente los 3 bits correspondientes
    // a la ficha.
    bloque = bloque & ~mascara;

    // Inserta el nuevo valor.
    bloque = bloque |
             (static_cast<unsigned int>(valor) << offset);

    // Se vuelven a guardar los dos bytes por separado.
    tablero[byteInicial] =
        static_cast<unsigned char>(bloque & 0xFF);

    tablero[byteInicial + 1] =
        static_cast<unsigned char>((bloque >> 8) & 0xFF);
}