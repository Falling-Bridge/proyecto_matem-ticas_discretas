Integrantes del grupo:

    Vicente Ramírez Torrealba
    Lucas Morales Oyanedel
    Diego Matus Salas

El propósito de este archivo es explicar cómo compilar e ingresar un grafo correctamente para que sea analizado por el código. 
Teniendo en cuenta que este programa fue diseñado específicamente para sistemas operativos Windows; por lo tanto, 
el funcionamiento en Linux o Mac no ha sido probado ni garantizado.

Pasos para ejecutar el código:

1)Tener un editor de código Visual Studio, CLion, o cualquier otro IDE que soporte desarrollo en C.

2)Tener un compilador instalado:
  si el editor escogido no viene con un compilador, es necesario instalar uno. Para Visual Studio, es necesario haber seleccionado el "C++ Development Workload" 
  durante la instalación, ya que incluye el compilador de C. En caso de usar otro editor, como Visual Studio Code, se debe instalar MinGW o GCC.
  
3)Configurar tu entorno de compilación:
  Clonar el repositortio y abrirlo en el editor de código escogido (tener instalado git es necesario para este paso)
  Se puede clonar el repositorio con el comando (en terminal cmd o powershell): 
  
  git clone https://github.com/Falling-Bridge/proyecto_mates_discretas.git

4)Compilar el código
  Se debe presionar el icono que parece un triangulo en la parte superior del editor, si no se encuentra, puede abrir una terminal cmd o powershell
    En la misma debe colocarse en el directorio donde instaló el repositorio, luego de haber llegado a la dirección de instalación para compilar se ocupa:
      -Si posee mingw32 o mingw64 (y ha configurado las variables de entorno), puede ocupar el comando en la terminal:
          
      mingw32-make run
     
      si no posee mingw32 o mingw63, se puede usar el siguiente comando:
          
      gcc -g -Wall -I include -O2 -o juanito.out src/Lector.c src/main.c src/freememory.c src/conexidad.c
         
      para poder ejecutar el proyecto se ocupa:
          
      ./juanito.exe

5) una vez que se haya logrado compilar y ejecutar el código, aparecerá un mensaje que dice:
  "Ingrese la ruta del archivo, debe seguir el formato: './pruebas/'nombre del archivo'

  los nombres de archivo que puede escoger son ("grafo1", "k7", "k5", "prueba")
  quedando las rutas de la forma:
    
    ./pruebas/grafo1
    ./pruebas/k7
    ./pruebas/k5
    ./pruebas/prueba

  Si desea ingresar un grafo que no ha sido contemplado (y el código sige en ejecución), debe ingresar un caracter cualquiera y presionar enter
  una vez que se haya detenido la ejecución usar el comando: 'cd pruebas' (desde terminal), o en su defecto como se está trabajando en windows, y al  lugar donde instaló
  repositorio y abrir la carpeta de pruebas, y crear un nuevo archivo.

Aclaraciones:

El formato que deben seguir los archivos de grafos, es el siguiente:

    "número" (cantidad de nodos que se ingresaron)
    "nodo" : "vecino del nodo", "vecino del nodo", ....... (el 'nombre' del nodo: y los vecinos del mismo separados por comas)

dando un ejemplo, debería verse de esta manera: 
        
      5
      1:2,3,4
      2:1,3
      3:1,2,5
      4:1
      5:3

otro ejemplo es:
        
      6
      1:
      2:3,4
      3:2,5,4
      4:2,3,5,6
      5:3,4
      6:4

una vez establecido el formato explicado, guardar y volver al paso 4.

6) aparecerá un menú en donde le pedirá ingresar números del 1 al 7, el número 0 o el número 10; para realizar las acciones descritas a continuación:

  Ingrese el numero de la opcion que desea ver:
  
    [0]  para dejar de correr el programa
    [1]  para ver el grafo (el archivo que se tuvo que ingresar como ruta)
    [2]  para ver la conexidad del grafo (indica si el grafo ingresado es conexo)
    [3]  para ver las combinatorias del grafo (elimina todas las combinaciones de vértices desde un tamaño 1 a n-2)
    [4]  para ver los vertices de corte (los vértices que al eliminarlos, vuelven el grafo disconexo)
    [5]  para ver los grados minimos y maximos del grafo (cuantos vecinos tiene un vértice)
    [6]  para ver los vertices 'hoja' (los vértices que tienen un solo vecino)
    [7]  para ver la k conexidad del grafo (cuantos vértices se pueden eliminar de manera aleatoria y el grafo resultante seguir siendo conexo)
    [10] para limpiar la pantalla (elimina las impresiones de los casos anteriores)

si no se ingresa un número de los mencionados anteriormente, solo se eliminan todos las impresiones anteriores y se vuelven a mostrar las opciones
  
