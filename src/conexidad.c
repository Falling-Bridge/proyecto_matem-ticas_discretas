#include "../include/conexidad.h"

// Variables globales
int vertices_de_corte[MAX_VERTICES_DE_CORTE];
int count_vertices_de_corte = 0;
int k_conexidad = 0;
bool estotalmenteconexo = false;

// Función para almacenar el vértice de corte
void verticesdecorte(int vertice) {
    for (int i = 0; i < count_vertices_de_corte; i++) {
        if (vertices_de_corte[i] == vertice) {
            return;
        }
    }

    if (count_vertices_de_corte < MAX_VERTICES_DE_CORTE) {
        vertices_de_corte[count_vertices_de_corte++] = vertice;
    }
}

// Función para imprimir los vértices de corte
void imprimirVerticesDeCorte(bool conexidad) {
    if (conexidad && count_vertices_de_corte == 0) {
        printf("El grafo "ROJO"no tiene "RESET_COLOR" vertices de corte"RESET_COLOR"\n\n");
    } else if (conexidad && count_vertices_de_corte != 0) {
        printf(""AZUL"%s"RESET_COLOR"", count_vertices_de_corte == 1 ? "El vertice de corte es el: " : "Los vertices de corte son: ");
        for (int i = 0; i < count_vertices_de_corte; i++) {
            printf("%d", vertices_de_corte[i]);
            if (i < count_vertices_de_corte - 1) {
                printf(", ");
            }
        }
        printf("\n\n");
    } else {
        printf(""AZUL"No tiene sentido hablar de vertices de corte, dado a que el grafo no es conexo"RESET_COLOR"\n\n");
    }
}

// Función para realizar el algoritmo DFS
void dfs(int nodo, bool *visitado, Fila *filas, int n, bool *eliminados) {
    visitado[nodo] = true;
    for (int i = 0; i < filas[nodo].cantidad; i++) {
        int vecino = filas[nodo].vecinos[i];
        int indice_vecino = -1;
        for (int j = 0; j < n; j++) {
            if (filas[j].primera_columna == vecino && !eliminados[j]) {
                indice_vecino = j;
                break;
            }
        }
        if (indice_vecino != -1 && !visitado[indice_vecino] && !eliminados[indice_vecino]) {
            dfs(indice_vecino, visitado, filas, n, eliminados);
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

    int inicio = 0;
    while (inicio < n && eliminados[inicio]) {
        inicio++;
    }

    if (inicio == n) {
        free(visitado);
        return false;
    }

    dfs(inicio, visitado, filas, n, eliminados);

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

// Modifica la función eliminarGrupoYImprimir para aceptar k_conexidad como parámetro
void eliminarGrupoYImprimir(Fila *filas, int n, int *grupo, int size, int caso, int *k_conexidad) {
    bool *eliminados = calloc(n, sizeof(bool));
    if (eliminados == NULL) {
        printf("Error al asignar memoria para el arreglo de eliminados.\n");
        return;
    }

    for (int j = 0; j < size; j++) {
        eliminados[grupo[j] - 1] = true;
    }

    bool conexo = esConexo(filas, n, eliminados);

    char *grupo_str = malloc(100);
    if (grupo_str == NULL) {
        printf("Error al asignar memoria para el string del grupo.\n");
        free(eliminados);
        return;
    }

    strcpy(grupo_str, "");
    for (int j = 0; j < size; j++) {
        char temp[10];
        sprintf(temp, "%d", grupo[j]);
        strcat(grupo_str, temp);
        if (j < size - 1) {
            strcat(grupo_str, ",");
        }
    }

    if (caso == 3) {
        printf("El grafo %ses conexo%s al eliminar %s %s: %s\n",
               conexo ? VERDE : ROJO "no ", RESET_COLOR,
               size == 1 ? "el" : "los",
               size == 1 ? "vertice" : "vertices", grupo_str);
    }

    if (size == 1 && !conexo) {
        verticesdecorte(grupo[0]);
    }

    free(grupo_str);
    free(eliminados);
}

// Modifica la función generarCombinaciones para aceptar k_conexidad como parámetro
void generarCombinaciones(Fila *filas, int n, int *grupo, int size, int start, int k, int caso, int *k_conexidad) {
    if (k == 0) {
        eliminarGrupoYImprimir(filas, n, grupo, size, caso, k_conexidad);
        return;
    }

    for (int i = start; i < n; i++) {
        grupo[size] = filas[i].primera_columna;
        generarCombinaciones(filas, n, grupo, size + 1, i + 1, k - 1, caso, k_conexidad);
    }
}

// Actualiza la función eliminarNodos para pasar el puntero a k_conexidad
void eliminarNodos(Fila *filas, int n, int caso) {
    k_conexidad = 0;
    for (int k = 1; k <= 4; k++) {
        int *grupo = malloc(k * sizeof(int));
        if (grupo == NULL) {
            printf("Error al asignar memoria para el grupo de nodos.\n");
            return;
        }

        if (caso == 3) {
            printf("" MAGENTA "Conexidad al eliminar %d %s:\n"RESET_COLOR"", k, k == 1 ? "vertice" : "vertices");
        }

        generarCombinaciones(filas, n, grupo, 0, 0, k, caso, &k_conexidad);
        free(grupo);
    }
    if (caso == 3 && n > 4) printf("\nNo tiene caso evaluar mas alla de 4 vertices, por la definicion provista en el enunciado\n\n");
}

//Función para ver los grados del grafo
void gradosdelgrafo(Fila *filas, int n) {

    int min_grado = filas[0].cantidad;
    int max_grado = filas[0].cantidad;

    // Encontrar el mínimo y máximo grado
    for (int i = 1; i < n; i++) {
        if (filas[i].cantidad < min_grado) {
            min_grado = filas[i].cantidad;
        }
        if (filas[i].cantidad > max_grado) {
            max_grado = filas[i].cantidad;
        }
    }

    // Imprimir los nodos con grado mínimo
    printf("Nodos con grado minimo (%d):\n", min_grado);
    for (int i = 0; i < n; i++) {
        if (filas[i].cantidad == min_grado) {
            printf("Nodo: %d, Grado: %d\n", filas[i].primera_columna, filas[i].cantidad);
        }
    }

    // Imprimir los nodos con grado máximo
    printf("\nNodos con grado maximo (%d):\n", max_grado);
    for (int i = 0; i < n; i++) {
        if (filas[i].cantidad == max_grado) {
            printf("Nodo: %d, Grado: %d\n", filas[i].primera_columna, filas[i].cantidad);
        }
    }
    printf("\n");
}

//Función para ver los nodos que tienen un solo vecino
void nodos_hoja(Fila *filas, int n) {
    int contador = 0;
    for (int i = 0; i < n; i++){
        if (filas[i].cantidad == 1){
            printf("El nodo %d, es un nodo ""hoja\n", filas[i].primera_columna);
        }else {
            contador++;
        }
    }
    if (contador == n) printf("El grafo "ROJO"no tiene"RESET_COLOR" nodos hoja\n");
    printf("\n");
}

// Función para verificar la total conexidad al eliminar todas las combinaciones posibles de vértices
void detectarTotalConexidad(Fila *filas, int n) {
    bool *eliminados = calloc(n, sizeof(bool));
    if (eliminados == NULL) {
        printf("Error al asignar memoria para el arreglo de eliminados.\n");
        return;
    }

    estotalmenteconexo = true; // Asumimos que es totalmente conexo al inicio

    for (int k = 1; k <= 4; k++) {
        int *grupo = malloc(k * sizeof(int));
        if (grupo == NULL) {
            printf("Error al asignar memoria para el grupo de nodos.\n");
            free(eliminados);
            return;
        }

        // Generar todas las combinaciones posibles y verificar la conexidad
        generarCombinacionesParaConexidad(filas, n, grupo, 0, 0, k, &estotalmenteconexo);

        if (!estotalmenteconexo) {
            // Si encontramos un tamaño de grupo k que no es totalmente conexo, detenemos el algoritmo
            free(grupo);
            break;
        }

        // Incrementamos k_conexidad si el grupo es totalmente conexo
        if(k_conexidad == 0 || k_conexidad < 4) k_conexidad++;
        free(grupo);
    }

    free(eliminados);
}

void generarCombinacionesParaConexidad(Fila *filas, int n, int *grupo, int size, int start, int k, bool *esTotalmenteConexo) {
    if (k == 0) {
        // Crear un arreglo de eliminados basado en el grupo actual
        bool *eliminados = calloc(n, sizeof(bool));
        if (eliminados == NULL) {
            printf("Error al asignar memoria para el arreglo de eliminados.\n");
            return;
        }
        for (int j = 0; j < size; j++) {
            eliminados[grupo[j] - 1] = true;
        }

        // Verificar si el grafo es conexo al eliminar el grupo actual
        bool conexo = esConexo(filas, n, eliminados);

        if (!conexo) {
            *esTotalmenteConexo = false; // Si no es conexo, actualizamos el flag
        }
        free(eliminados);
        return;
    }

    for (int i = start; i < n; i++) {
        grupo[size] = filas[i].primera_columna;
        generarCombinacionesParaConexidad(filas, n, grupo, size + 1, i + 1, k - 1, esTotalmenteConexo);
        if (!*esTotalmenteConexo) {
            return; // Salimos temprano si encontramos un grupo no conexo
        }
    }
}


void retornakconexidad(Fila *filas, int n, bool *eliminados) {
    // Evaluar si el grafo es totalmente conexo
    bool estotalmenteconexo = esConexo(filas, n, eliminados);

    // Caso cuando el grafo no es conexo o la k-conexidad es 0
    if (estotalmenteconexo && k_conexidad == 0) {

        if (n > 1) {
            printf("La k_conexidad del grafo es: 1\n\n");
            return;
        }

        if (!estotalmenteconexo) {
            printf("El grafo original no es conexo, por lo tanto no tiene sentido hablar de k conexidad\n\n");
            return;
        }
        if (n == 1) {
            printf("Por la definicion de conexidad proporcionada, la k conexidad es 1\n\n");
            return;
        }
    }

    // Caso cuando el número de vértices es mayor que k_conexidad
    if (n > k_conexidad) {
        if (n != 1 && k_conexidad >= 4 || n > 4) {
            printf("La k_conexidad del grafo es: 4\n\n");
            return;
        }
    }

    if (k_conexidad < 4){
        printf("La k_conexidad del grafo es: %d\n\n", k_conexidad + 1);
    } 
}
