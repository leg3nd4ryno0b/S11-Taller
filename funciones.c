#include <stdio.h>
#include <string.h>

struct Libro {
    int id;
    char titulo[50];
    char autor[50];
    int AnoPublicacion;
    char estado[20];
};

void LeerCadena(char cadena[], int longitud){
    fgets(cadena, longitud, stdin);
    size_t len = strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

void Menu(){
    printf("----- Menu de Opciones -----\n");
    printf("1. Agregar Libro\n");
    printf("2. Mostrar Libros\n");
    printf("3. Buscar Libro por titulo o ID\n");
    printf("4. Modificar Libro\n");
    printf("5. Eliminar Libro\n");
    printf("6. Salir\n");
}

int LeerEntero(){
    int numero;
    int resultado;
    while(1){
        resultado = scanf("%d", &numero);
        if(resultado != 1){

            int c;
            while((c = getchar()) != '\n' && c != EOF);
            printf("Error: Ingrese un numero valido: ");
        } else if(numero < 0){

            while(getchar() != '\n');
            printf("Error: No se permiten numeros negativos. Ingrese un numero positivo: ");
        } else {

            while(getchar() != '\n');
            break;
        }
    }
    return numero;
};

int ValidarOpcionMenu(int opcion){
    return (opcion >= 1 && opcion <= 6);
}

int ValidarSiNo(int opcion){
    return (opcion == 1 || opcion == 2);
}

void ConvertirAMinusculas(char *cadena){
    for(int i = 0; cadena[i]; i++){
        if(cadena[i] >= 'A' && cadena[i] <= 'Z'){
            cadena[i] = cadena[i] + 32;
        }
    }
}

void LimpiarBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int ValidarEstado(char *estado, char *estadoValidado){
    ConvertirAMinusculas(estado);
    
    if(strncmp(estado, "disponible", strlen(estado)) == 0 && strlen(estado) >= 3){
        strcpy(estadoValidado, "Disponible");
        return 1;
    }
    else if(strncmp(estado, "prestado", strlen(estado)) == 0 && strlen(estado) >= 3){
        strcpy(estadoValidado, "Prestado");
        return 1;
    }
    return 0;
}

int ValidarAno(int ano){
    return (ano > 0 && ano <= 2025);
}

void MostrarTablaLibros(struct Libro *libros, int cantidad){
    if(cantidad == 0){
        printf("No hay libros registrados.\n");
        return;
    }
    printf("+-----+----------------------+----------------------+------+--------------+\n");
    printf("| ID  | Titulo               | Autor                | Ano  | Estado       |\n");
    printf("+-----+----------------------+----------------------+------+--------------+\n");
    for(int i = 0; i < cantidad; i++){
        printf("| %3d | %-20s | %-20s | %4d | %-12s |\n", 
               (libros + i)->id, (libros + i)->titulo, (libros + i)->autor, (libros + i)->AnoPublicacion, (libros + i)->estado);
    }
    printf("+-----+----------------------+----------------------+------+--------------+\n");
}

void BuscarLibro(struct Libro *libros, int cantidad, int criterioTipo, int criterio){
    int encontrado = 0;
    printf("\n========== BUSCANDO LIBRO ==========");
    for(int i = 0; i < cantidad; i++){
        int coincide = 0;
        if(criterioTipo == 2){ 
            coincide = (libros + i)->id == criterio;
        }
        
        if(coincide){
            printf("\nLibro encontrado:\n");
            printf("ID: %d\nTitulo: %s\nAutor: %s\nAno de Publicacion: %d\nEstado: %s\n",
                   (libros + i)->id, (libros + i)->titulo, (libros + i)->autor, (libros + i)->AnoPublicacion, (libros + i)->estado);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado){
        printf("\nLibro no encontrado.\n");
    }
    printf("====================================\n\n");
}

void ModificarEstadoLibro(struct Libro *libros, int cantidad, int id, const char *nuevoEstado){
    printf("\n===== MODIFICAR ESTADO DEL LIBRO =====");
    for(int i = 0; i < cantidad; i++){
        if((libros + i)->id == id){
            strcpy((libros + i)->estado, nuevoEstado);
            printf("\nEstado del libro con ID %d modificado a %s.\n", id, nuevoEstado);
            printf("========================================\n\n");
            return;
        }
    }
    printf("\nLibro con ID %d no encontrado.\n", id);
    printf("========================================\n\n");
}

void eliminarLibro(struct Libro *libros, int *cantidad, int id){
    printf("\n======== ELIMINAR LIBRO ========");
    for(int i = 0; i < *cantidad; i++){
        if((libros + i)->id == id){
            for(int j = i; j < *cantidad - 1; j++){
                libros[j] = libros[j + 1];
            }
            (*cantidad)--;
            printf("\nLibro con ID %d eliminado.\n", id);
            printf("=================================\n\n");
            return;
        }
    }
    printf("\nLibro con ID %d no encontrado.\n", id);
    printf("=================================\n\n");

}
