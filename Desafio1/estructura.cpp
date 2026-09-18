#include "estructura.h"
#include "bits.h"
#include "memoria.h"
#include "tablero.h"

#include "estructura.h"
#include "bits.h"
#include "memoria.h"
#include "tablero.h"

unsigned char* agregarFila(
    unsigned char* tablero,
    int* filas,
    int columnas,
    int filaPos,
    int* bytesReservados
    )
{
    // 1. Validar los parámetros.

    if (tablero == nullptr ||
        filas == nullptr ||
        bytesReservados == nullptr)
    {
        return tablero;
    }

    if (*filas <= 0 || columnas <= 0 ||
        *bytesReservados <= 0)
    {
        return tablero;
    }

    // Se permite insertar al inicio, en medio o al final.
    if (filaPos < 0 || filaPos > *filas)
    {
        return tablero;
    }

    // 2. Calcular las nuevas dimensiones.

    int filasViejas = *filas;
    int filasNuevas = filasViejas + 1;

    int bytesNuevos =
        bytesNecesarios(filasNuevas, columnas);

    int nuevaCapacidad = *bytesReservados;

    bool reemplazarBloque = false;

    unsigned char* nuevo = nullptr;

    // 3. Comprobar si necesitamos más memoria.

    if (bytesNuevos > *bytesReservados)
    {
        nuevo = RedimensionarMemoria(
            *bytesReservados,
            bytesNuevos,
            false,
            &nuevaCapacidad,
            &reemplazarBloque
            );
    }
    else
    {
        // La capacidad actual es suficiente.
        // Reservamos un bloque temporal del mismo tamaño.
        nuevo = ReservarMemoria(*bytesReservados);
    }

    // Si falló la reserva, conservamos el tablero anterior.

    if (nuevo == nullptr)
    {
        return tablero;
    }

    // 4. Inicializar el nuevo bloque en cero.

    for (int i = 0; i < nuevaCapacidad; i++)
    {
        nuevo[i] = 0;
    }

    // 5. Reconstruir el tablero con la nueva fila.

    for (int fila = 0; fila < filasNuevas; fila++)
    {
        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            // Si es la fila insertada,
            // generamos una ficha nueva.

            if (fila == filaPos)
            {
                generarFicha(
                    nuevo,
                    fila,
                    columna,
                    columnas
                    );
            }
            else
            {
                // Determinamos de dónde viene
                // la ficha original.

                int filaOrigen = fila;

                if (fila > filaPos)
                {
                    filaOrigen = fila - 1;
                }

                int indiceOrigen =
                    calcularIndice(
                        filaOrigen,
                        columna,
                        columnas
                        );

                int indiceDestino =
                    calcularIndice(
                        fila,
                        columna,
                        columnas
                        );

                // Extraemos los 3 bits del tablero viejo.

                unsigned char ficha =
                    obtenerFicha(
                        tablero,
                        indiceOrigen
                        );

                // Escribimos los mismos 3 bits
                // en el tablero nuevo.

                escribirFicha(
                    nuevo,
                    indiceDestino,
                    ficha
                    );
            }
        }
    }

    // 6. Liberar la memoria anterior.

    LiberarMemoria(tablero);

    // 7. Actualizar dimensiones y capacidad.

    *filas = filasNuevas;

    *bytesReservados = nuevaCapacidad;

    return nuevo;
}

unsigned char* eliminarFila(
    unsigned char* tablero,
    int* filas,
    int columnas,
    int filaPos,
    int* bytesReservados
    )
{
    // 1. Validar los parámetros.
    if (tablero == nullptr ||
        filas == nullptr ||
        bytesReservados == nullptr)
    {
        return tablero;
    }

    // No permitir eliminar la última fila.
    if (*filas <= 1 || columnas <= 0 ||
        *bytesReservados <= 0)
    {
        return tablero;
    }

    // Comprobar que la fila exista.
    if (filaPos < 0 || filaPos >= *filas)
    {
        return tablero;
    }

    // 2. Calcular las nuevas dimensiones.
    int filasNuevas = *filas - 1;

    int bytesNuevos =
        bytesNecesarios(filasNuevas, columnas);

    int nuevaCapacidad = *bytesReservados;

    bool reemplazarBloque = false;

    // 3. Solicitar memoria aplicando la regla del 65 %.
    unsigned char* nuevo =
        RedimensionarMemoria(
            *bytesReservados,
            bytesNuevos,
            true,
            &nuevaCapacidad,
            &reemplazarBloque
            );

    // Si falla la reserva, conservamos el tablero anterior.
    if (nuevo == nullptr)
    {
        return tablero;
    }

    // 4. Inicializar el bloque nuevo.
    for (int i = 0; i < nuevaCapacidad; i++)
    {
        nuevo[i] = 0;
    }

    // 5. Reconstruir el tablero sin la fila eliminada.
    for (int fila = 0; fila < filasNuevas; fila++)
    {
        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            // Las filas anteriores a la eliminada
            // conservan su posición original.
            int filaOrigen = fila;

            // Las posteriores se desplazan una fila
            // hacia arriba.
            if (fila >= filaPos)
            {
                filaOrigen = fila + 1;
            }

            int indiceOrigen =
                calcularIndice(
                    filaOrigen,
                    columna,
                    columnas
                    );

            int indiceDestino =
                calcularIndice(
                    fila,
                    columna,
                    columnas
                    );

            // Leer los 3 bits de la ficha original.
            unsigned char ficha =
                obtenerFicha(tablero, indiceOrigen);

            // Escribirlos en su nueva posición compacta.
            escribirFicha(nuevo, indiceDestino, ficha);
        }
    }

    // 6. Liberar el bloque anterior.
    LiberarMemoria(tablero);

    // 7. Actualizar las dimensiones y capacidad.
    *filas = filasNuevas;
    *bytesReservados = nuevaCapacidad;

    return nuevo;
}
unsigned char* agregarColumna(unsigned char* tablero, int filas, int columnas,
                              int columnaNueva, int bytesReservadosActual, int* bytesReservadosNuevo) {
    int columnasNuevasTotal = columnas + 1;
    int bytesNecesariosNuevo = bytesNecesarios(filas, columnasNuevasTotal);

    bool reemplazarBloque;
    unsigned char* destino = RedimensionarMemoria(bytesReservadosActual, bytesNecesariosNuevo,
                                                  false, bytesReservadosNuevo, &reemplazarBloque);
    if (destino == nullptr) {
        return nullptr;
    }
    // Reconstruccion
    int indiceDestino = 0;
    for (int f = 0; f < filas; f++) {
        int columnaOrigen = 0;
        for (int c = 0; c < columnasNuevasTotal; c++) {
            if (c == columnaNueva) {
                generarFicha(destino, f, c, columnasNuevasTotal);
            } else {
                int indiceOrigen = calcularIndice(f, columnaOrigen, columnas);
                unsigned char ficha = obtenerFicha(tablero, indiceOrigen);
                escribirFicha(destino, indiceDestino, ficha);
                columnaOrigen++;
            }
            indiceDestino++;
        }
    }

    LiberarMemoria(tablero);
    return destino;
}

unsigned char* eliminarColumna(unsigned char* tablero, int filas, int columnas,
                               int columnaAEliminar, int bytesReservadosActual, int* bytesReservadosNuevo) {
    int columnasNuevasTotal = columnas - 1;
    int bytesNecesariosNuevo = bytesNecesarios(filas, columnasNuevasTotal);

    bool reemplazarBloque;
    unsigned char* destino = RedimensionarMemoria(bytesReservadosActual, bytesNecesariosNuevo,
                                                  true, bytesReservadosNuevo, &reemplazarBloque);
    if (destino == nullptr) {
        return nullptr;
    }
    // Reconstruccion
    int indiceDestino = 0;
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (c == columnaAEliminar) continue;
            int indiceOrigen = calcularIndice(f, c, columnas);
            unsigned char ficha = obtenerFicha(tablero, indiceOrigen);
            escribirFicha(destino, indiceDestino, ficha);
            indiceDestino++;
        }
    }

    if (reemplazarBloque) {
        LiberarMemoria(tablero);
        return destino;
    } else {
        CopiarBytes(tablero, destino, bytesReservadosActual);
        LiberarMemoria(destino);
        return tablero;
    }
}
