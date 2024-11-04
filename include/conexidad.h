#ifndef CONEXIDAD_H
#define CONEXIDAD_H

#include "../include/lector.h"
#include "../include/colores.h"

//prototipos de funciones

void dfs(int nodo, bool *visitado, Fila *filas, int n, bool *eliminados);
bool esConexo(Fila *filas, int n, bool *eliminados);
void verticesdecorte(int vertice);
void imprimirVerticesDeCorte(bool conexidad);
void eliminarGrupoYImprimir(Fila *filas, int n, int *grupo, int size, int caso);
void generarCombinaciones(Fila *filas, int n, int *grupo, int size, int start, int k, int caso);
void eliminarNodos(Fila *filas, int n, int caso);

#endif

