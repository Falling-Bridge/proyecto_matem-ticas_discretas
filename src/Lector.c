#include "lector.h"
#include "freememory.h"
#include <stdlib.h>
#include <stdbool.h>

void leerarchivo(FILE *archivo) {
    int n;

    // Leer el numero de nodos
    if (fscanf(archivo, "%d", &n) != 1) {
        printf("Error al leer la cantidad de nodos.\n");
        goto error; 
    }
    printf("Cantidad de nodos: %d\n", n);

    // Asignar memoria para las filas
    Fila *filas = malloc(n * sizeof(Fila));
    if (filas == NULL) {
        printf("Error al asignar memoria para las filas.\n");
        goto error; 
    }

    int contador_nodos = 0;

    // Leer cada fila hasta n nodos
    while (contador_nodos < n) {
        int primer_valor;
        char linea[1024];  // Buffer para leer la linea completa, 
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            // Ignorar lineas vacias
            if (linea[0] == '\n') {
                continue; // Saltar esta iteracion
            }

            // Leer el 'nombre' del nodo
            if (sscanf(linea, "%d:", &primer_valor) != 1) {
                printf("Error al leer el nodo %d.\n", contador_nodos + 1);
                goto error; 
            }

            filas[contador_nodos].primera_columna = primer_valor;
            filas[contador_nodos].vecinos = NULL;
            filas[contador_nodos].cantidad = 0;
            int valor_adyacente;

            // Procesar la linea despues de los dos puntos
            char *ptr = linea;
            // Mover el puntero al primer numero despues de los dos puntos
            while (*ptr != ':' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == ':') {
                ptr++;  // Saltar el ':' para comenzar a leer los vecinos
            }

            // Leer los vecinos
            while (sscanf(ptr, "%d", &valor_adyacente) == 1) {
                // Verificar que el vecino no sea el mismo nodo
                if (valor_adyacente == primer_valor) {
                    printf("Error: El nodo %d no puede ser vecino de si mismo.\n", primer_valor);
                    goto error; 
                }

                // Verificar si ya existe el vecino (duplicado)
                bool esDuplicado = false;
                for (int j = 0; j < filas[contador_nodos].cantidad; j++) {
                    if (filas[contador_nodos].vecinos[j] == valor_adyacente) {
                        esDuplicado = true;
                        break;
                    }
                }

                if (esDuplicado) {
                    printf("Error: No puede haber vecinos repetidos, vecino repetido en el nodo %d.\n", primer_valor);
                    goto error; 
                }

                // Agregar el vecino
                filas[contador_nodos].vecinos = realloc(filas[contador_nodos].vecinos, (filas[contador_nodos].cantidad + 1) * sizeof(int));
                if (filas[contador_nodos].vecinos == NULL) {
                    printf("Error al asignar memoria para los vecinos.\n");
                    goto error; 
                }
                filas[contador_nodos].vecinos[filas[contador_nodos].cantidad] = valor_adyacente;
                filas[contador_nodos].cantidad++;

                // Avanzar el puntero para saltar al siguiente numero o al final de la linea
                while (*ptr != ',' && *ptr != '\0') {
                    ptr++;
                }
                if (*ptr == ',') {
                    ptr++;  // Saltar la coma
                }
            }

            contador_nodos++; // Incrementar el contador de nodos leidos
        } else {
            // Si se llega al final del archivo y aun no se han leido n nodos
            break;
        }
    }

    // Verificar si se leyeron exactamente n nodos
    if (contador_nodos != n) {
        printf("Error: Se esperaban %d nodos, pero se leyeron %d.\n", n, contador_nodos);
        goto error; 
    }

    // Verificar si hay mas nodos despues de los n leidos
    char siguiente_char = fgetc(archivo);
    if (siguiente_char != EOF && siguiente_char != '\n') {
        printf("Error: Se encontraron nodos adicionales despues de los %d nodos especificados.\n", n);
        goto error; 
    }

    // Verificar la reciprocidad de los vecinos
    if (!tieneVecinoReciproco(filas, n)) {
        goto error; 
    }

    // Imprimir las filas leidas
    for (int i = 0; i < n; i++) {
        printf("%d (%d): ", filas[i].primera_columna, filas[i].cantidad);
        for (int j = 0; j < filas[i].cantidad; j++) {
            printf("%d ", filas[i].vecinos[j]);
        }
        printf("\n");
    }

    // Liberar memoria al final de la funcion
    liberarMemoria(filas, n); // Usar la nueva funcion para liberar memoria
    return; // Salir de la funcion normalmente

error:
    liberarMemoria(filas, contador_nodos); // Liberar memoria antes de salir
    exit(EXIT_FAILURE);  // Terminar el programa
}