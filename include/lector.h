#pragma once

#ifndef LECTOR_H
#define LECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../include/colores.h"

//struct para el grafo
typedef struct {
    int primera_columna;
    int *vecinos;
    int cantidad;
} Fila;

//prototipos de funciones
void leerarchivo(FILE *archivo);
bool tieneVecinoReciproco(Fila *filas, int n);
void imprimirGrafo(Fila *filas, int n);



#endif // LECTOR_H
