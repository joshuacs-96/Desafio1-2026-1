Sweet Crush es un juego de consola que usa un tablero dinámico de fichas.
Cada ficha se almacena con solo 3 bits dentro de un arreglo de unsigned char.
Los códigos 0 a 5 representan las seis fichas posibles y el código 6 un espacio vacío.
El módulo bits calcula el índice, el byte y el desplazamiento para leer o escribir cada ficha.
El programa solicita al usuario un mínimo de tres filas y tres columnas.
Después reserva la cantidad exacta de bytes, genera fichas aleatorias y muestra el tablero.
El menú permite eliminar una ficha, agregar o eliminar filas y agregar o eliminar columnas.
Al modificar una dimensión, el tablero se reconstruye conservando las fichas existentes.
La memoria se redimensiona y, al reducirse, se aplica una regla de uso mínimo del 65 %.
Las combinaciones horizontales y verticales de tres o más fichas iguales se detectan por separado.
Las fichas encontradas se marcan primero y luego se eliminan simultáneamente.
Tras una eliminación, la gravedad baja las fichas de cada columna y se llenan los vacíos.
Este proceso se repite como cascada hasta que no aparezcan nuevas combinaciones.
El programa registra eliminaciones, fichas eliminadas, combinaciones, cascadas y puntuación.
Finalmente, al seleccionar salir, libera la memoria dinámica y termina la partida.
Filtrar archivos