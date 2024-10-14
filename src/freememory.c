// freememory.c
#include "freememory.h" // Asegúrate de incluir el encabezado correspondiente
#include <stdlib.h>

void liberarMemoria(Fila *filas, int n) {
    for (int i = 0; i < n; i++) {
        free(filas[i].vecinos); // Liberar la memoria de los vecinos
    }
    free(filas); // Liberar la memoria de las filas
}