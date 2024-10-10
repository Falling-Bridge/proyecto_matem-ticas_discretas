#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estructura para manejar una fila con una cantidad variable de números
typedef struct {
    int primera_columna;  // El número antes de los dos puntos
    int *vecinos;         // Arreglo dinámico para los números después de los dos puntos
    int cantidad;         // Cantidad de números después de los dos puntos
} Fila;

void leerarchivo(FILE *archivo);
bool tieneVecinoReciproco(Fila *filas, int n);

int main() {
    char archivo[100];
    printf("Ingrese el nombre del archivo, con la extension del mismo: ");
    scanf("%s", archivo);

    FILE *lectura = fopen(archivo, "r");
    if (lectura == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    leerarchivo(lectura);
    fclose(lectura);
    return 0;
}

void leerarchivo(FILE *archivo) {
    int n;

    // Leer el número de nodos
    if (fscanf(archivo, "%d", &n) != 1) {
        printf("Error al leer la cantidad de nodos.\n");
        return;
    }
    printf("Cantidad de nodos: %d\n", n);

    // Asignar memoria para las filas
    Fila *filas = malloc(n * sizeof(Fila));
    if (filas == NULL) {
        printf("Error al asignar memoria para las filas.\n");
        return;
    }

    // Contador para verificar la cantidad de nodos leídos
    int contador_nodos = 0; 

    // Leer cada fila hasta n nodos
    for (int i = 0; i < n; ) {
        int primer_valor;

        char linea[4096];  // Buffer para leer la línea completa
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            // Ignorar líneas vacías
            if (linea[0] == '\n') {
                continue; // Saltar esta iteración
            }

            // Leer el 'nombre' del nodo
            if (sscanf(linea, "%d:", &primer_valor) != 1) {
                printf("Error al leer el nodo %d.\n", i + 1);
                free(filas);  // Liberar memoria antes de salir
                exit(EXIT_FAILURE);  // Terminar el programa
            }

            filas[i].primera_columna = primer_valor;
            filas[i].vecinos = NULL;
            filas[i].cantidad = 0;
            int valor_adyacente;

            // Procesar la línea después de los dos puntos
            char *ptr = linea;
            // Mover el puntero al primer número después de los dos puntos
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
                    free(filas);  // Liberar memoria antes de salir
                    exit(EXIT_FAILURE);  // Terminar el programa
                }

                // Verificar si ya existe el vecino (duplicado)
                bool esDuplicado = false;
                for (int j = 0; j < filas[i].cantidad; j++) {
                    if (filas[i].vecinos[j] == valor_adyacente) {
                        esDuplicado = true;
                        break;
                    }
                }

                if (esDuplicado) {
                    printf("Error: No puede haber vecinos repetidos para el nodo %d.\n", primer_valor);
                    free(filas);  // Liberar memoria antes de salir
                    exit(EXIT_FAILURE);  // Terminar el programa
                }

                // Agregar el vecino
                filas[i].vecinos = realloc(filas[i].vecinos, (filas[i].cantidad + 1) * sizeof(int));
                if (filas[i].vecinos == NULL) {
                    printf("Error al asignar memoria para los vecinos.\n");
                    free(filas);
                    exit(EXIT_FAILURE);  // Terminar el programa
                }
                filas[i].vecinos[filas[i].cantidad] = valor_adyacente;
                filas[i].cantidad++;

                // Avanzar el puntero para saltar al siguiente número o al final de la línea
                while (*ptr != ',' && *ptr != '\0') {
                    ptr++;
                }
                if (*ptr == ',') {
                    ptr++;  // Saltar la coma
                }
            }

            contador_nodos++; // Incrementar el contador de nodos leídos
            i++; // Incrementar solo si se ha leído correctamente un nodo
        }
    }

    // Verificar si se leyeron exactamente n nodos
    if (contador_nodos != n) {
        printf("Error: Se esperaban %d nodos, pero se leyeron %d.\n", n, contador_nodos);
        free(filas);  // Liberar memoria antes de salir
        exit(EXIT_FAILURE);  // Terminar el programa
    }

    // Verificar si hay más nodos después de los n leídos
    if (fgetc(archivo) != EOF && '\0') {
        printf("Error: Se encontraron nodos adicionales después de los %d nodos especificados.\n", n);
        free(filas);  // Liberar memoria antes de salir
        exit(EXIT_FAILURE);  // Terminar el programa
    }

    // Verificar la reciprocidad de los vecinos
    if (!tieneVecinoReciproco(filas, n)) {
        free(filas);  // Liberar memoria antes de salir
        exit(EXIT_FAILURE);  // Terminar el programa
    }

    // Imprimir las filas leídas
    for (int i = 0; i < n; i++) {
        printf("%d (%d): ", filas[i].primera_columna, filas[i].cantidad);
        for (int j = 0; j < filas[i].cantidad; j++) {
            printf("%d ", filas[i].vecinos[j]);
        }
        printf("\n");
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(filas[i].vecinos);
    }
    free(filas);
}

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