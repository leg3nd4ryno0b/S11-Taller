#include <stdio.h>
#include "funciones.h"

int main (int argc, char *argv[]) {

    struct Libro libros[10];
    int opc=0;
    int cont=0;
    do {
        Menu();
        printf("Seleccione una opcion: ");
        opc = LeerEntero();
        
        if(!ValidarOpcionMenu(opc)){
            printf("\nError: Opcion invalida. Por favor ingrese un numero entre 1 y 6.\n\n");
            continue;
        }
        
        if(opc >= 2 && opc <= 5 && cont == 0){
            printf("\nError: No hay libros registrados. Primero debe agregar libros (Opcion 1).\n\n");
            continue;
        }

        switch(opc) {
            case 1:
                {
                    printf("\nCuantos libros desea agregar? ");
                    int cantidadAgregar = LeerEntero();
                    
                    if(cantidadAgregar <= 0){
                        printf("Error: Debe ingresar un numero positivo.\n\n");
                    } else if(cont + cantidadAgregar > 10){
                        printf("Error: No puede agregar %d libros. Solo hay espacio para %d libros mas.\n\n", cantidadAgregar, 10 - cont);
                    } else {
                        for(int i = 0; i < cantidadAgregar; i++){
                            printf("\n====== AGREGAR LIBRO %d de %d ======\n", i + 1, cantidadAgregar);
                            printf("Ingrese el ID del libro: ");
                            libros[cont].id = LeerEntero();
                            
                            printf("Ingrese el titulo del libro: ");
                            LeerCadena(libros[cont].titulo, 50);
                            
                            printf("Ingrese el autor del libro: ");
                            LeerCadena(libros[cont].autor, 50);
                            
                            printf("Ingrese el ano de publicacion del libro: ");
                            libros[cont].AnoPublicacion = LeerEntero();
                            while(!ValidarAno(libros[cont].AnoPublicacion)){
                                printf("Error: El ano debe ser entre 1 y 2025: ");
                                libros[cont].AnoPublicacion = LeerEntero();
                            }
                            
                            printf("Ingrese el estado del libro (Disponible o Prestado): ");
                            char estadoIngresado[20];
                            LeerCadena(estadoIngresado, 20);
                            while(!ValidarEstado(estadoIngresado, libros[cont].estado)){
                                printf("Error: Ingrese 'Disponible' o 'Prestado' (o similares: dis, disp, pres, prest): ");
                                LeerCadena(estadoIngresado, 20);
                            }

                            
                            cont++;
                            printf("==================================\n");
                            printf("Libro agregado exitosamente.\n");
                        }
                    }
                    printf("\n");
                }
                break;
            case 2:
                MostrarTablaLibros(&libros[0], cont);
                break;
            case 3:
                {
                    int buscarMas = 1;
                    while(buscarMas){
                        printf("\nBuscar por (1) Titulo o (2) ID: ");
                        int tipoBusqueda;
                        while(1){
                            tipoBusqueda = LeerEntero();
                            if(tipoBusqueda == 1 || tipoBusqueda == 2) break;
                            printf("Error: Ingrese 1 (Titulo) o 2 (ID): ");
                        }
                        
                        if(tipoBusqueda == 1){
                            char tituloBuscar[50];
                            printf("Ingrese el titulo del libro a buscar: ");
                            LeerCadena(tituloBuscar, 50);
                            ConvertirAMinusculas(tituloBuscar);
                            
                            int encontrado = 0;
                            printf("\n========== BUSCANDO LIBRO ==========\n");
                            for(int i = 0; i < cont; i++){
                                char tituloTemp[50];
                                strcpy(tituloTemp, (libros + i)->titulo);
                                ConvertirAMinusculas(tituloTemp);
                                
                                if(strcmp(tituloTemp, tituloBuscar) == 0){
                                    printf("Libro encontrado:\n");
                                    printf("ID: %d\nTitulo: %s\nAutor: %s\nAno de Publicacion: %d\nEstado: %s\n",
                                           (libros + i)->id, (libros + i)->titulo, (libros + i)->autor, (libros + i)->AnoPublicacion, (libros + i)->estado);
                                    encontrado = 1;
                                    break;
                                }
                            }
                            if(!encontrado){
                                printf("Libro no encontrado.\n");
                            }
                            printf("====================================\n");
                        } else {
                            int idBuscar;
                            printf("Ingrese el ID del libro a buscar: ");
                            idBuscar = LeerEntero();
                            BuscarLibro(&libros[0], cont, 2, idBuscar);
                        }
                        
                        printf("Desea realizar otra busqueda? (1=Si, 2=No): ");
                        int respuesta;
                        while(1){
                            respuesta = LeerEntero();
                            if(ValidarSiNo(respuesta)) break;
                            printf("Error: Ingrese 1 (Si) o 2 (No): ");
                        }
                        buscarMas = (respuesta == 1);
                    }
                    printf("\n");
                }
                break;
            case 4:
                {
                    int modificarMas = 1;
                    while(modificarMas){
                        MostrarTablaLibros(&libros[0], cont);
                        int idModificar;
                        printf("Ingrese el ID del libro a modificar: ");
                        idModificar = LeerEntero();
                        
                        int indice = -1;
                        for(int i = 0; i < cont; i++){
                            if((libros + i)->id == idModificar){
                                indice = i;
                                break;
                            }
                        }
                        
                        if(indice == -1){
                            printf("\n===== MODIFICAR LIBRO =====\n");
                            printf("Libro no encontrado.\n");
                            printf("===========================\n\n");
                        } else {
                            printf("\n===== MODIFICAR LIBRO =====\n");
                            printf("1. Modificar Estado\n");
                            printf("2. Modificar Titulo\n");
                            printf("3. Modificar ID\n");
                            printf("4. Modificar Ano\n");
                            printf("5. Modificar Autor\n");
                            printf("Seleccione que desea modificar: ");
                            int opcion;
                            while(1){
                                opcion = LeerEntero();
                                if(opcion >= 1 && opcion <= 5) break;
                                printf("Error: Ingrese un numero entre 1 y 5: ");
                            }
                            
                            switch(opcion){
                                case 1:
                                    {
                                        char nuevoEstado[20];
                                        char estadoValidado[20];
                                        printf("Ingrese el nuevo estado: ");
                                        LeerCadena(nuevoEstado, 20);
                                        while(!ValidarEstado(nuevoEstado, estadoValidado)){
                                            printf("Error: Ingrese 'Disponible' o 'Prestado' (o similares: dis, disp, pres, prest): ");
                                            LeerCadena(nuevoEstado, 20);
                                        }
                                        strcpy((libros + indice)->estado, estadoValidado);
                                        printf("Estado modificado exitosamente.\n");
                                    }
                                    break;
                                case 2:
                                    {
                                        char nuevoTitulo[50];
                                        printf("Ingrese el nuevo titulo: ");
                                        LeerCadena(nuevoTitulo, 50);
                                        strcpy((libros + indice)->titulo, nuevoTitulo);
                                        printf("Titulo modificado exitosamente.\n");
                                    }
                                    break;
                                case 3:
                                    {
                                        int nuevoID;
                                        printf("Ingrese el nuevo ID: ");
                                        nuevoID = LeerEntero();
                                        (libros + indice)->id = nuevoID;
                                        printf("ID modificado exitosamente.\n");
                                    }
                                    break;
                                case 4:
                                    {
                                        int nuevoAno;
                                        printf("Ingrese el nuevo ano: ");
                                        nuevoAno = LeerEntero();
                                        while(!ValidarAno(nuevoAno)){
                                            printf("Error: El ano debe ser entre 1 y 2025: ");
                                            nuevoAno = LeerEntero();
                                        }
                                        (libros + indice)->AnoPublicacion = nuevoAno;
                                        printf("Ano modificado exitosamente.\n");
                                    }
                                    break;
                                case 5:
                                    {
                                        char nuevoAutor[50];
                                        printf("Ingrese el nuevo autor: ");
                                        LeerCadena(nuevoAutor, 50);
                                        strcpy((libros + indice)->autor, nuevoAutor);
                                        printf("Autor modificado exitosamente.\n");
                                    }
                                    break;
                            }
                            printf("===========================\n");
                        }
                        
                        printf("\nDesea modificar otro libro? (1=Si, 2=No): ");
                        int respuesta;
                        while(1){
                            respuesta = LeerEntero();
                            if(ValidarSiNo(respuesta)) break;
                            printf("Error: Ingrese 1 (Si) o 2 (No): ");
                        }
                        modificarMas = (respuesta == 1);
                    }
                    printf("\n");
                }
                break;
            case 5:
                {
                    int eliminarMas = 1;
                    while(eliminarMas){
                        MostrarTablaLibros(&libros[0], cont);
                        int idEliminar;
                        printf("Ingrese el ID del libro a eliminar: ");
                        idEliminar = LeerEntero();
                        
                        int indiceEliminar = -1;
                        for(int i = 0; i < cont; i++){
                            if((libros + i)->id == idEliminar){
                                indiceEliminar = i;
                                break;
                            }
                        }
                        
                        if(indiceEliminar != -1){
                            printf("\n======== ELIMINAR LIBRO ========\n");
                            printf("Se eliminara el siguiente libro:\n");
                            printf("ID: %d | Titulo: %s | Autor: %s\n",
                                   (libros + indiceEliminar)->id, (libros + indiceEliminar)->titulo, (libros + indiceEliminar)->autor);
                            printf("Esta seguro que desea eliminarlo? (1=Si, 2=No): ");
                            int confirmacion;
                            while(1){
                                confirmacion = LeerEntero();
                                if(ValidarSiNo(confirmacion)) break;
                                printf("Error: Ingrese 1 (Si) o 2 (No): ");
                            }
                            
                            if(confirmacion == 1){
                                eliminarLibro(&libros[0], &cont, idEliminar);
                            } else {
                                printf("Eliminacion cancelada.\n");
                                printf("=================================\n\n");
                            }
                        } else {
                            printf("\n======== ELIMINAR LIBRO ========\n");
                            printf("Libro con ID %d no encontrado.\n", idEliminar);
                            printf("=================================\n\n");
                        }
                        
                        printf("Desea eliminar otro libro? (1=Si, 2=No): ");
                        int respuesta;
                        while(1){
                            respuesta = LeerEntero();
                            if(ValidarSiNo(respuesta)) break;
                            printf("Error: Ingrese 1 (Si) o 2 (No): ");
                        }
                        eliminarMas = (respuesta == 1);
                    }
                    printf("\n");
                }
                break;
            case 6:
                printf("\nSaliendo del programa.\n\n");
                break;
        }
    } while(opc != 6);
    

    return 0;

}
