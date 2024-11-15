# Variables
TARGET = juanito.exe
CC = gcc
CFLAGS = -g -Wall -I include -O2

SRCDIR = src
OBJDIR = obj
INCDIR = include

# Archivos fuente y objetos
codigo = $(SRCDIR)/Lector.c $(SRCDIR)/main.c $(SRCDIR)/freememory.c $(SRCDIR)/conexidad.c
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(codigo))

# Aseguramos que no se consideren estas como archivos
.PHONY: all run debug clean memoria

# Regla principal
all: $(TARGET)

# Regla para generar el ejecutable
$(TARGET): $(OBJECTS)
	@echo "Compilando el Programa..."
	@$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

# Regla para generar los archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "Compilando $<..."
	@$(CC) -c $< -o $@ $(CFLAGS)

# Crear el directorio de objetos si no existe
$(OBJDIR):
	@if not exist $(OBJDIR) mkdir $(OBJDIR)

# Ejecutar el programa
run: $(TARGET)
	@echo "Ejecutando el Programa"
	@./$(TARGET)

# Depurar con GDB
debug: $(TARGET)
	@gdb $(TARGET)

# Chequeo de memoria con Valgrind
memoria: $(TARGET)
	@valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# Limpiar archivos objeto y el ejecutable
clean:
	@if exist $(OBJDIR) rmdir /S /Q $(OBJDIR)
	@if exist $(TARGET) del $(TARGET)

#comandos para correr el makefile mingw32-make run/debug/clean

#en caso de no tener instalado el mingw, puede compilar y correr el programa con los siguientes comandos
#gcc -g -Wall -I include -O2 src/Lector.c src/main.c src/freememory.c src/conexidad.c -o juanito.exe
#./juanito.exe