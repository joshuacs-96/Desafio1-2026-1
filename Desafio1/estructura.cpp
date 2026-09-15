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
    // Validar posición.
    // Permitimos insertar desde 0 hasta *filas.
    if (filaPos < 0 || filaPos > *filas)
        return tablero;

    int filasViejas = *filas;
    int filasNuevas = filasViejas + 1;

    // Bytes realmente necesarios después de agregar.
    int bytesNuevos =
        bytesNecesarios(filasNuevas, columnas);

    // Si la capacidad actual no alcanza,
    // aumentamos físicamente la memoria.
    if (bytesNuevos > *bytesReservados)
    {
        tablero = RedimensionarMemoria(
            tablero,
            *bytesReservados,
            bytesNuevos
            );

        *bytesReservados = bytesNuevos;
    }

    /*
       IMPORTANTE:

       Las fichas que están después de la nueva fila
       se mueven de ABAJO HACIA ARRIBA.

       Así evitamos sobrescribir una ficha antes
       de haberla copiado.
    */

    for (int fila = filasViejas - 1;
         fila >= filaPos;
         fila--)
    {
        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            int indiceViejo =
                calcularIndice(
                    fila,
                    columna,
                    columnas
                    );

            int indiceNuevo =
                calcularIndice(
                    fila + 1,
                    columna,
                    columnas
                    );

            unsigned char ficha =
                obtenerFicha(
                    tablero,
                    indiceViejo
                    );

            escribirFicha(
                tablero,
                indiceNuevo,
                ficha
                );
        }
    }

    // Actualizamos el número de filas.
    *filas = filasNuevas;

    // La nueva fila se llena con fichas aleatorias.
    for (int columna = 0;
         columna < columnas;
         columna++)
    {
        generarFicha(
            tablero,
            filaPos,
            columna,
            columnas
            );
    }

    return tablero;
}

unsigned char* eliminarFila(
    unsigned char* tablero,
    int* filas,
    int columnas,
    int filaPos,
    int* bytesReservados
    )
{
    if (filaPos < 0 || filaPos >= *filas)
        return tablero;

    if (*filas <= 1)
        return tablero;

    int filasNuevas = *filas - 1;

    // Compactar las filas.
    for (int fila = filaPos;
         fila < filasNuevas;
         fila++)
    {
        for (int columna = 0;
             columna < columnas;
             columna++)
        {
            int origen =
                calcularIndice(
                    fila + 1,
                    columna,
                    columnas
                    );

            int destino =
                calcularIndice(
                    fila,
                    columna,
                    columnas
                    );

            unsigned char ficha =
                obtenerFicha(
                    tablero,
                    origen
                    );

            escribirFicha(
                tablero,
                destino,
                ficha
                );
        }
    }

    // Actualizar dimensión lógica.
    *filas = filasNuevas;

    // Calcular utilización REAL en bits.
    int bitsValidos =
        (*filas) * columnas * 3;

    int bitsReservados =
        (*bytesReservados) * 8;

    double utilizacion =
        (static_cast<double>(bitsValidos)
         / static_cast<double>(bitsReservados))
        * 100.0;

    // Aplicar regla del 65 %.
    if (utilizacion < 65.0)
    {
        int bytesNuevos =
            bytesNecesarios(
                *filas,
                columnas
                );

        tablero =
            RedimensionarMemoria(
                tablero,
                *bytesReservados,
                bytesNuevos
                );

        *bytesReservados =
            bytesNuevos;
    }

    return tablero;
}

