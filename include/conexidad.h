#ifndef CONEXIDAD_H
#define CONEXIDAD_H

#include "../include/lector.h"
#include "../include/colores.h"

#define MAX_VERTICES_DE_CORTE 100

//prototipos de funciones
void verticesdecorte(int vertice);
void imprimirVerticesDeCorte(bool conexidad);
void dfs(int nodo, bool *visitado, Fila *filas, int n, bool *eliminados);
bool esConexo(Fila *filas, int n, bool *eliminados);
void eliminarGrupoYImprimir(Fila *filas, int n, int *grupo, int size, int caso, int *k_conexidad);
void generarCombinaciones(Fila *filas, int n, int *grupo, int size, int start, int k, int caso, int *k_conexidad);
void eliminarNodos(Fila *filas, int n, int caso);
void gradosdelgrafo(Fila *filas, int n);
void nodos_hoja(Fila *filas, int n);
void detectarTotalConexidad(Fila *filas, int n);
void generarCombinacionesParaConexidad(Fila *filas, int n, int *grupo, int size, int start, int k, bool *esTotalmenteConexo);
void retornakconexidad(Fila *filas, int n, bool *eliminados);

#endif // CONEXIDAD_H


