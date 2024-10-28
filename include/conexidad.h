#ifndef CONEXIDAD_H
#define CONEXIDAD_H

#include "../include/lector.h"
#include "../include/colores.h"

//prototipos de funciones
void dfs(int nodo, bool *visitado, Fila *filas, int n, bool *eliminados);
bool esConexo(Fila *filas, int n, bool *eliminados);
void eliminarGrupoYImprimir(Fila *filas, int n, int *grupo, int size);
void generarCombinaciones(Fila *filas, int n, int *grupo, int size, int start, int k);
void eliminarNodos(Fila *filas, int n);

#endif

