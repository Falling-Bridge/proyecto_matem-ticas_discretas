#include <stdio.h>
#include <stdlib.h>
#include "../include/lector.h"
#define archivo "./pruebas/grafo1"

int main() {

    FILE *lectura = fopen(archivo, "r");
    if (lectura == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    leerarchivo(lectura);
    return 0;
}