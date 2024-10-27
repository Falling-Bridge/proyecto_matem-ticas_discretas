#include "../include/conexidad.h"

// Función para realizar el algoritmo DFS
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
bool esConexo(Fila *filas, int n, bool *eliminados) {
    bool *visitado = calloc(n, sizeof(bool));
    if (visitado == NULL) {
        printf("Error al asignar memoria para el arreglo de visitados.\n");
        return false;
    }

    // Comienza la DFS desde el primer nodo no eliminado
    int inicio = 0;
    while (inicio < n && eliminados[inicio]) {
        inicio++;
    }

    if (inicio == n) {
        free(visitado);
        return false; // Todos los nodos han sido eliminados
    }

    dfs(inicio, visitado, filas, n);
    bool conexo = true;
    for (int i = 0; i < n; i++) {
        if (!visitado[i] && !eliminados[i]) {
            conexo = false;
            break;
        }
    }
    free(visitado);
    return conexo;
}

// Función para eliminar un grupo de nodos y sus aristas correspondientes del grafo
void eliminarGrupoYImprimir(Fila *filas, int n, int *grupo, int size) {
    bool *eliminados = calloc(n, sizeof(bool));
    if (eliminados == NULL) {
        printf("Error al asignar memoria para el arreglo de eliminados.\n");
        return;
    }

    // Marcar los nodos a eliminar
    for (int j = 0; j < size; j++) {
        eliminados[grupo[j] - 1] = true; // Suponiendo que los vértices empiezan desde 1
    }

    // Verificar si el nuevo grafo es conexo
    bool conexo = esConexo(filas, n, eliminados);

    // Limpiar el string del grupo
    char *grupo_str = malloc(100); // Suponiendo un tamaño máximo de cambio, ///esto va a cambiar, pero después
    if (grupo_str == NULL) {
        printf("Error al asignar memoria para el string del grupo.\n");
        free(eliminados);
        return;
    }

    // Formar la cadena de nodos eliminados
    strcpy(grupo_str, "");
    for (int j = 0; j < size; j++) {
        char temp[10];
        sprintf(temp, "%d", grupo[j]);
        strcat(grupo_str, temp);
        if (j < size - 1) {
            strcat(grupo_str, ",");
        }
    }

    // Comprobar si el grafo es conexo y mostrar el resultado
    if (conexo) printf("El grafo es conexo al eliminar el(los) vertice(s): %s\n", grupo_str);
    else printf("El grafo no es conexo al eliminar el(los) vertice(s): %s\n", grupo_str);
    free(grupo_str);
    free(eliminados);
}

// Función para generar todas las combinaciones de nodos a eliminar
void generarCombinaciones(Fila *filas, int n, int *grupo, int size, int start, int k) {
    if (k == 0) {
        eliminarGrupoYImprimir(filas, n, grupo, size);
        return;
    }

    for (int i = start; i < n; i++) {
        grupo[size] = filas[i].primera_columna;
        generarCombinaciones(filas, n, grupo, size + 1, i + 1, k - 1);
    }
}

// Función principal que llama a la generación de combinaciones
void eliminarNodos(Fila *filas, int n) {
    for (int k = 1; k <= n - 2; k++) { // Eliminamos grupos de 1 hasta n-2 nodos
        int *grupo = malloc(k * sizeof(int));
        if (grupo == NULL) {
            printf("Error al asignar memoria para el grupo de nodos.\n");
            return;
        }

        printf("Conexidad al eliminar %d vertice(s):\n", k);

        generarCombinaciones(filas, n, grupo, 0, 0, k);
        free(grupo);
    }
}