#include "../include/conexidad.h"

// Función para realizar la DFS
void dfs(int nodo, bool *visitado, Fila *filas, int n) {
    visitado[nodo] = true;
    for (int i = 0; i < filas[nodo].cantidad; i++) {
        int vecino = filas[nodo].vecinos[i];
        int indice_vecino = -1;
        for (int j = 0; j < n; j++) {
            if (filas[j].primera_columna == vecino) {
                indice_vecino = j;
                break;
            }
        }
        if (indice_vecino != -1 && !visitado[indice_vecino]) {
            dfs(indice_vecino, visitado, filas, n);
        }
    }
}

// Función para verificar si el grafo es conexo
bool esConexo(Fila *filas, int n) {
    bool *visitado = calloc(n, sizeof(bool));
    if (visitado == NULL) {
        printf("Error al asignar memoria para el arreglo de visitados.\n");
        return false;
    }

    dfs(0, visitado, filas, n);
    bool conexo = true;
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            conexo = false;
            break;
        }
    }
    free(visitado);
    return conexo;
}
