#include <stdio.h>
#include <string.h>

struct Libro {
    int id;
    char titulo[50];
    char autor[50];
    int AnoPublicacion;
    char estado[20];
};

void LeerCadena(char cadena[], int longitud);
void Menu();
int LeerEntero();
int ValidarOpcionMenu(int opcion);
int ValidarSiNo(int opcion);
void ConvertirAMinusculas(char *cadena);
void LimpiarBuffer();
int ValidarEstado(char *estado, char *estadoValidado);
int ValidarAno(int ano);
void MostrarTablaLibros(struct Libro *libros, int cantidad);
void BuscarLibro(struct Libro *libros, int cantidad, int criterioTipo, int criterio);
void ModificarEstadoLibro(struct Libro *libros, int cantidad, int id, const char *nuevoEstado);
void eliminarLibro(struct Libro *libros, int *cantidad, int id);
int IdExiste(struct Libro *libros, int cantidad, int id);




