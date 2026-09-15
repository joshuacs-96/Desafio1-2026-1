#include "combinaciones.h"
#include "bits.h"

bool detectarHorizontales(
    const unsigned char* tablero,
    int filas,
    int columnas,
    bool* marcado
    )
{
    bool encontrado = false;

    for (int fila = 0; fila < filas; fila++)
    {
        int columna = 0;

        while (columna < columnas)
        {
            int indiceInicial =
                calcularIndice(fila, columna, columnas);

            unsigned char ficha =
                obtenerFicha(tablero, indiceInicial);

            // Una posición vacía no puede formar combinación.
            if (ficha == codigo_vacio)
            {
                columna++;
                continue;
            }

            int inicio = columna;
            int cantidad = 1;

            columna++;

            // Contamos cuántas fichas iguales
            // aparecen consecutivamente.
            while (columna < columnas)
            {
                int indice =
                    calcularIndice(fila, columna, columnas);

                unsigned char siguiente =
                    obtenerFicha(tablero, indice);

                if (siguiente != ficha)
                {
                    break;
                }

                cantidad++;
                columna++;
            }

            // Tres o más forman una combinación.
            if (cantidad >= 3)
            {
                encontrado = true;

                for (int c = inicio;
                     c < inicio + cantidad;
                     c++)
                {
                    int indice =
                        calcularIndice(fila, c, columnas);

                    marcado[indice] = true;
                }
            }
        }
    }

    return encontrado;
}

bool detectarVerticales(
    const unsigned char* tablero,
    int filas,
    int columnas,
    bool* marcado
    )
{
    bool encontrado = false;

    for (int columna = 0;
         columna < columnas;
         columna++)
    {
        int fila = 0;

        while (fila < filas)
        {
            int indiceInicial =
                calcularIndice(fila, columna, columnas);

            unsigned char ficha =
                obtenerFicha(tablero, indiceInicial);

            if (ficha == codigo_vacio)
            {
                fila++;
                continue;
            }

            int inicio = fila;
            int cantidad = 1;

            fila++;

            while (fila < filas)
            {
                int indice =
                    calcularIndice(fila, columna, columnas);

                unsigned char siguiente =
                    obtenerFicha(tablero, indice);

                if (siguiente != ficha)
                {
                    break;
                }

                cantidad++;
                fila++;
            }

            if (cantidad >= 3)
            {
                encontrado = true;

                for (int f = inicio;
                     f < inicio + cantidad;
                     f++)
                {
                    int indice =
                        calcularIndice(f, columna, columnas);

                    marcado[indice] = true;
                }
            }
        }
    }

    return encontrado;
}

int eliminarMarcadas(
    unsigned char* tablero,
    int filas,
    int columnas,
    const bool* marcado
    )
{
    int eliminadas = 0;

    int total = filas * columnas;

    for (int indice = 0; indice < total; indice++)
    {
        if (marcado[indice])
        {
            escribirFicha(
                tablero,
                indice,
                codigo_vacio
                );

            eliminadas++;
        }
    }

    return eliminadas;
}