#ifndef CONEXIDAD_H
#define CONEXIDAD_H

#include "../include/lector.h"

//prototipos de funciones
void dfs(int nodo, bool *visitado, Fila *filas, int n);
bool esConexo(Fila *filas, int n);

#endif

