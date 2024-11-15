#include <stdio.h>
#include <stdlib.h>
#include "../include/lector.h"

int main() {

    char *archivo[100];
    printf("Ingrese la ruta del archivo, debe seguir el formato: './pruebas/'nombre del archivo'\n\n");
    scanf("%s", &archivo);
    FILE *lectura = fopen(archivo, "r");
    if (lectura == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    leerarchivo(lectura);
    return 0;
}