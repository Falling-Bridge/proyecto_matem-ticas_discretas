#include <stdio.h>
#include <stdlib.h>
#include "lector.h"

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