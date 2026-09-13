#ifndef MEMORIA_H
#define MEMORIA_H


unsigned char* ReservarMemoria(int bytes);
void LiberarMemoria(unsigned char*& tablero);
void CopiarBytes(unsigned char* destino, const unsigned char* origen, int cantidad);
unsigned char* RedimensionarMemoria(unsigned char* actual, int bytesActuales, int bytesNuevos);


#endif // MEMORIA_H
