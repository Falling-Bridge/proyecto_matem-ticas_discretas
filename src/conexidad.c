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

// Función para eliminar un grupo de nodos y sus aristas correspondientes del grafo
void eliminarGrupoYImprimir(Fila *filas, int n, int *grupo, int size) {
    // Crear una nueva lista de filas para el nuevo grafo
    Fila *nuevoGrafo = malloc((n - size) * sizeof(Fila));
    if (nuevoGrafo == NULL) {
        printf("Error al asignar memoria para el nuevo grafo.\n");
        return;
    }

    int nuevoIndice = 0;
    for (int i = 0; i < n; i++) {
        bool eliminar = false;
        for (int k = 0; k < size; k++) {
            if (filas[i].primera_columna == grupo[k]) {
                eliminar = true;
                break;
            }
        }
        if (!eliminar) {
            nuevoGrafo[nuevoIndice].primera_columna = filas[i].primera_columna;
            nuevoGrafo[nuevoIndice].cantidad = 0;
            nuevoGrafo[nuevoIndice].vecinos = malloc((filas[i].cantidad) * sizeof(int)); // Reservar memoria para los vecinos
            if (nuevoGrafo[nuevoIndice].vecinos == NULL) {
                printf("Error al asignar memoria para los vecinos del nuevo grafo.\n");
                free(nuevoGrafo);
                return;
            }

            // Copiar los vecinos, omitiendo los nodos a eliminar
            for (int j = 0; j < filas[i].cantidad; j++) {
                bool esVecino = false;
                for (int k = 0; k < size; k++) {
                    if (filas[i].vecinos[j] == grupo[k]) {
                        esVecino = true;
                        break;
                    }
                }
                if (!esVecino) {
                    nuevoGrafo[nuevoIndice].vecinos[nuevoGrafo[nuevoIndice].cantidad++] = filas[i].vecinos[j];
                }
            }
            nuevoIndice++;
        }
    }

    // Imprimir el nuevo grafo
    printf("Nuevo grafo (sin nodos: ");
    for (int k = 0; k < size; k++) {
        printf("%d ", grupo[k]);
    }
    printf("):\n");
    for (int i = 0; i < nuevoIndice; i++) {
        printf("Nodo %d:", nuevoGrafo[i].primera_columna);
        for (int j = 0; j < nuevoGrafo[i].cantidad; j++) {
            printf(" %d", nuevoGrafo[i].vecinos[j]);
        }
        printf("\n");
    }
    printf("\n"); // Añadir una línea en blanco para separar grafos

    // Liberar memoria
    for (int i = 0; i < nuevoIndice; i++) {
        free(nuevoGrafo[i].vecinos);
    }
    free(nuevoGrafo);
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
        generarCombinaciones(filas, n, grupo, 0, 0, k);
        free(grupo);
    }
}