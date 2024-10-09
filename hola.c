#include <stdio.h>
#include <stdlib.h>

// Estructura para manejar una fila con una cantidad variable de números
typedef struct {
    int primera_columna;  // El número antes de los dos puntos
    int *adyacentes;      // Arreglo dinámico para los números después de los dos puntos
    int cantidad;         // Cantidad de números después de los dos puntos
} Fila;

void leerarchivo(FILE *archivo);

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

    // Leer el número de filas
    if (fscanf(archivo, "%d", &n) != 1) {
        printf("Error al leer el número de filas.\n");
        return;
    }
    printf("Número de filas: %d\n", n);

    // Asignar memoria para las filas
    Fila *filas = malloc(n * sizeof(Fila));
    if (filas == NULL) {
        printf("Error al asignar memoria para las filas.\n");
        return;
    }

    // Leer cada fila
    for (int i = 0; i < n; i++) {
        int primer_valor;

        // Leer el número antes de los dos puntos
        if (fscanf(archivo, "%d:", &primer_valor) != 1) {
            continue;
        }

        filas[i].primera_columna = primer_valor;
        filas[i].adyacentes = NULL;
        filas[i].cantidad = 0;
        int valor_adyacente;

        // Leer los números adyacentes
        char linea[4096];  // Buffer para leer la línea completa
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            char *ptr = linea;
            while (sscanf(ptr, "%d", &valor_adyacente) == 1) {
                filas[i].adyacentes = realloc(filas[i].adyacentes, (filas[i].cantidad + 1) * sizeof(int));
                if (filas[i].adyacentes == NULL) {
                    printf("Error al asignar memoria para los números adyacentes.\n");
                    break;
                }
                filas[i].adyacentes[filas[i].cantidad] = valor_adyacente;
                filas[i].cantidad++;
                // Avanzar el puntero para saltar al siguiente número o al final de la línea
                while (*ptr != ',' && *ptr != '\0') {
                    ptr++;
                }
                if (*ptr == ',') {
                    ptr++;  // Saltar la coma
                }
            }
        }
    }

    // Imprimir las filas leídas
    for (int i = 0; i < n; i++) {
        printf("%d (%d): ", filas[i].primera_columna, filas[i].cantidad);
        for (int j = 0; j < filas[i].cantidad; j++) {
            printf("%d ", filas[i].adyacentes[j]);
        }
        printf("\n");
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(filas[i].adyacentes);
    }
    free(filas);
}