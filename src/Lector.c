#include "../include/lector.h"
#include "../include/freememory.h"

void leerarchivo(FILE *archivo) {
    int n;
    bool seguir_ejecutando_programa = true;

    // Leer el número de nodos
    if (fscanf(archivo, "%d", &n) != 1) {
        if (!isdigit(n)){
            printf("Error al leer la cantidad de nodos.\n");
            goto error_de_nodos;
        }
    }

    // Asignar memoria para las filas
    Fila *filas = malloc(n * sizeof(Fila));
    if (filas == NULL) {
        printf("Error al asignar memoria para las filas.\n");
        goto error;
    }

    // Inicializar el arreglo para los nodos eliminados
    bool *eliminados = calloc(n, sizeof(bool)); // Inicializar en falso
    if (eliminados == NULL) {
        printf("Error al asignar memoria para el arreglo de nodos eliminados.\n");
        goto error;
    }

    int contador_nodos = 0;

    // Leer cada fila hasta n nodos
    while (contador_nodos < n) {
        int primer_valor;
        char linea[1024]; // Buffer para leer la línea completa
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            // Ignorar líneas vacías
            if (linea[0] == '\n') continue;

            // Leer el 'nombre' del nodo
            if (sscanf(linea, "%d:", &primer_valor) != 1) {
                printf("Error al leer el nodo %d.\n", contador_nodos + 1);
                goto error_de_nodos;
            }

            filas[contador_nodos].primera_columna = primer_valor;
            filas[contador_nodos].vecinos = NULL;
            filas[contador_nodos].cantidad = 0;
            int valor_adyacente;

            // Procesar la línea después de los dos puntos
            char *ptr = linea;
            // Mover el puntero al primer número después de los dos puntos
            while (*ptr != ':' && *ptr != '\0') {
                ptr++;
            }
            if (*ptr == ':' || *ptr == ',') ptr++; // Saltar el ':' para comenzar a leer los vecinos

            // Leer los vecinos, ignorando comas y caracteres no numéricos
            while (*ptr != '\0') {
                // Ignorar comas o espacios
                if (*ptr == ',' || isspace((unsigned char)*ptr)) {
                    ptr++;
                    continue;
                }

                // Verificar si es un número
                if (isdigit((unsigned char)*ptr) && sscanf(ptr, "%d", &valor_adyacente) == 1) {
                    // Verificar que el vecino no sea el mismo nodo
                    if (valor_adyacente == primer_valor) {
                        printf("Error: El nodo %d no puede ser vecino de si mismo.\n", primer_valor);
                        goto error_de_nodos;
                    }

                    // Verificar si ya existe el vecino (duplicado)
                    bool esDuplicado = false;
                    for (int j = 0; j < filas[contador_nodos].cantidad; j++) {
                        if (filas[contador_nodos].vecinos[j] == valor_adyacente) {
                            esDuplicado = true;
                            break;
                        }
                    }

                    if (!esDuplicado) {
                        // Agregar el vecino
                        filas[contador_nodos].vecinos = realloc(filas[contador_nodos].vecinos, (filas[contador_nodos].cantidad + 1) * sizeof(int));
                        if (filas[contador_nodos].vecinos == NULL) {
                            printf("Error al asignar memoria para los vecinos.\n");
                            goto error;
                        }
                        filas[contador_nodos].vecinos[filas[contador_nodos].cantidad] = valor_adyacente;
                        filas[contador_nodos].cantidad++;
                    }

                    // Avanzar el puntero después del número leído
                    while (isdigit((unsigned char)*ptr)) ptr++;
                } else {
                    // Saltar cualquier carácter que no sea número o coma
                    ptr++;
                }
            }

            contador_nodos++; // Incrementar el contador de nodos leídos
        } else {
            // Si se llega al final del archivo y aún no se han leído n nodos
            break;
        }
    }

    // Verificar si se leyeron exactamente n nodos
    if (contador_nodos != n) {
        printf("Error: Se esperaban %d nodos, pero se leyeron %d.\n", n, contador_nodos);
        goto error;
    }

    // Verificar si hay más nodos después de los n leídos
    char siguiente_char = fgetc(archivo);
    if (siguiente_char != EOF && siguiente_char != '\n') {
        printf("Error: Se encontraron nodos adicionales despues de los %d nodos especificados.\n", n);
        goto error;
    }

    fclose(archivo);
    if (!tieneVecinoReciproco(filas, n)) goto error;
    int k_conexidad;

    while (seguir_ejecutando_programa){
        printf(""CIAN"Ingrese el numero de la opcion que desea ver:"RESET_COLOR"\n");
        printf("[0]  para dejar de correr el programa\n");
        printf("[1]  para ver el grafo\n");
        printf("[2]  para ver la conexidad del grafo\n");
        printf("[3]  para ver las combinatorias del grafo\n");
        printf("[4]  para ver los vertices de corte\n");
        printf("[5]  para ver los grados minimos y maximos del grafo\n");
        printf("[6]  para ver los vertices 'hoja'\n");
        printf("[7]  para ver la k conexidad del grafo\n");
        printf("[10] para limpiar la pantalla\n");

        int opcion;
        char c;
        if (scanf("%d", &opcion) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
        }
        printf("\n");

        switch (opcion) {

            case 0:
                system("cls");
                seguir_ejecutando_programa = false;
                break;

            case 1:
                system("cls");
                imprimirGrafo(filas, n);
                break;
            
            case 2:
                system("cls");
                if (esConexo(filas, n, eliminados)) printf("El grafo "CIAN"es conexo"RESET_COLOR"\n\n");
                else printf("El grafo "CIAN" no es conexo"RESET_COLOR"\n\n");
                break;

            case 3:
                system("cls");
                eliminarNodos(filas, n, 3);
                break;
            
            case 4:
                system("cls");
                eliminarNodos(filas, n, 4);
                imprimirVerticesDeCorte(esConexo(filas, n, eliminados));
                break;
            
            case 5:
                system("cls");
                gradosdelgrafo(filas, n);
                break;
            
            case 6:
                system("cls");
                nodos_hoja(filas, n);
                break;

            case 7:
                system("cls");
                detectarTotalConexidad(filas, n);
                retornakconexidad(filas, n, eliminados);
                break;

            case 10:
                system("cls");
                break;

            default:
                system("cls");
                break;
        }
    }

    liberarMemoria(filas, n);
    free(eliminados);
    return;

error:
    liberarMemoria(filas, n);
    free(eliminados);
    exit(EXIT_FAILURE);

error_de_nodos:
    exit(EXIT_FAILURE);
}

bool tieneVecinoReciproco(Fila *filas, int n){

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < filas[i].cantidad; j++) {
            int vecino = filas[i].vecinos[j];
            bool encontrado = false;
            // Buscar el nodo actual en los vecinos del vecino
            for (int k = 0; k < n; k++) {
                if (filas[k].primera_columna == vecino) {
                    for (int l = 0; l < filas[k].cantidad; l++) {
                        if (filas[k].vecinos[l] == filas[i].primera_columna) {
                            encontrado = true;
                            break;
                        }
                    }
                    break;
                }
            } if (!encontrado) {
                printf("Error: Existe la arista %d-%d, pero no existe la arista %d-%d.\n",
                       filas[i].primera_columna, vecino, vecino, filas[i].primera_columna);
                return false; // No hay reciprocidad
            }
        }
    }
    return true; // Todos los nodos tienen reciprocidad
}

void imprimirGrafo(Fila *filas, int n) {
    printf("Cantidad de vertices: %d\n\n", n);
    printf("Grafo:\n");
    for (int i = 0; i < n; i++) {
        printf("%d:", filas[i].primera_columna);
        for (int j = 0; j < filas[i].cantidad; j++) {
            printf(" %d", filas[i].vecinos[j]);
            if (j < filas[i].cantidad - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
    printf("\n");
}