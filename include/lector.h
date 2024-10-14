#pragma once

#include <stdio.h>
#include <stdbool.h>  // Incluye este encabezado para usar el tipo bool

typedef struct {
    int primera_columna;  // El número antes de los dos puntos
    int *vecinos;         // Arreglo dinámico para los números después de los dos puntos
    int cantidad;         // Cantidad de números después de los dos puntos
} Fila;

// Declaración de funciones
void leerarchivo(FILE *archivo);
bool tieneVecinoReciproco(Fila *filas, int n);  // Declaración de la función
