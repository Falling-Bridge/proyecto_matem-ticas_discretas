#include <stdio.h>
#include <stdlib.h>
#include "../include/lector.h"

int main() {
    char *archivo = "prueba.txt";

    FILE *lectura = fopen(archivo, "r");
    if (lectura == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    leerarchivo(lectura);
    return 0;
}