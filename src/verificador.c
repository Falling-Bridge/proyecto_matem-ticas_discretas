#include "verificador.h"
#include <stdio.h>

bool tieneVecinoReciproco(Fila *filas, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < filas[i].cantidad; j++) {
            int vecino = filas[i].vecinos[j];
            bool encontrado = false;
            // Buscar el nodo actual en los vecinos del vecino
            for (int k = 0; k < n; k++) {
                if (filas[k].primera_columna == vecino) {
                    for (int l = 0; l < filas[k].cantidad; l++) {
                        if (filas[k].vecinos[l] == filas[i].primera_columna) {
                            encontrado = true;
                            break;
                        }
                    }
                    break;
                }
            }
            if (!encontrado) {
                printf("Error: Existe la arista %d-%d, pero no existe la arista %d-%d.\n",
                    filas[i].primera_columna, vecino, vecino, filas[i].primera_columna);
                return false; // No hay reciprocidad
            }
        }
    }
    return true; // Todos los nodos tienen reciprocidad
}