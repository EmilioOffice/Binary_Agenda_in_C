#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define NOMBRE_ARCHIVO "c:\\Users\\USER\\Desktop\\Emilio Marquez\\ProgramasC\\agenda1.txt"

typedef struct{
    char nombre[10];
    int edad;
    int salario;
}Persona;

int CrearPersonas(Persona personas[], int n);
int EscribirArchivo(Persona personas[], int tam, const char *NombreArchivo);
int LeerArchivo(Persona personasEntrada[], int tam, const char *NombreArchivo);
Persona BuscarPersona(Persona personasEntrada[], int tam);
void NombrePersona(Persona *persona);
void EdadPersona(Persona *persona);
void SalarioPersona(Persona *persona);
void EliminarPersona(Persona personasEntrada[], int *tam);
void ActualizarInformacion(Persona personasEntrada[], int tam);

int main(){
    Persona personas[] = {"",0,0};
    int opcion = 0, tam1 = 0, n = 0, resp = 0, resp2 = 0;
    FILE *arch;
    arch = fopen(NOMBRE_ARCHIVO,"rb");
    fseek(arch,1,SEEK_END);
    tam1 = ftell(arch);
    fclose(arch);
    const int tam = tam1 / sizeof(Persona);
    Persona personasEntrada[tam];
    printf("Bienvenido a tu agenda...\n");
    printf("=====================================================\n");
    printf("¿Que deseas hacer hoy? \n");
    printf("1 = Agregar\n2 = Buscar\n");
    printf("3 = (Bajo Proceso de Actualizacion) \n4 = Terminar \n");
    scanf("%i", &opcion);
    printf("=====================================================\n");
    switch(opcion){
        case 1:
            while(resp == 0){
            resp = CrearPersonas(personas, n);
            if(resp == 1){
                EscribirArchivo(personas,tam,NOMBRE_ARCHIVO);
                break;
            }
            }
            break;
        case 2:
            LeerArchivo(personasEntrada, tam, NOMBRE_ARCHIVO);
            BuscarPersona(personasEntrada, tam);
            printf("¿Desea actualizar información de alguna persona? \n1 = Si\n2 = No\n");
            sacnf("%i",&resp2);
            if(resp2 == 1){
                ActualizarInformacion(personasEntrada, tam);
            }
            break;
        case 3:
            EliminarPersona(personasEntrada, &tam);
            printf("Gracias por visitar su Agenda \nTenga un buen dia!");
            break;
        case 4:
            printf("Gracias por visitar su Agenda \nTenga un buen dia!");
            break;
        default:
            printf("La opcion seleccionada no existe...\n Inicie el programa denuevo...");
            break;
    }
    return 0;
}

int CrearPersonas(Persona personas[], int n){
    int resp = 0, i = 1;
    printf("¿Cuantas personas se van a agregar? ");
    scanf("%i",&n);
    while(i <= n){
    printf("\nMuy bien, comienza con los datos de la persona...\n");
    printf("=====================================================\n");
    NombrePersona(&personas[i]);
    EdadPersona(&personas[i]);
    SalarioPersona(&personas[i]);
    printf("Datos guardados, verifique si son correctos...\n");
    printf("=====================================================\n");
    printf("Nombre: %s.\nEdad: %i.\nSalario: %i.\n", personas[i].nombre, personas[i].edad, personas[i].salario);
    printf("¿Los datos son correctos?\n1 = Si \n2 = No\n");
    scanf("%i", &resp);
    if(resp == 1){
        i++;
    }
    }
    if(i == (n + 1)){
        return 1;
    }else{
        return 0;
    }
}

int EscribirArchivo(Persona personas[], int tam, const char *NombreArchivo){
    FILE *arch;
    arch = fopen(NOMBRE_ARCHIVO, "wb");
    if(arch == NULL){
        printf("Hubo un error al abrir el archivo\n");
        return 0;
    }
    fwrite(personas, sizeof(Persona), tam, arch);
    fflush(arch);
    printf("Persona agregada exitosamente!\n");
    printf("=====================================================\n");
    return 1;
}

int LeerArchivo(Persona personasEntrada[], int tam, const char *NombreArchivo){
    FILE *arch;
    arch = fopen(NOMBRE_ARCHIVO,"rb");
    if(arch == NULL){
        printf("El archivo esta vacio\n");
        return 0;
    }
    fread(personasEntrada, sizeof(Persona), tam, arch);
    fclose(arch);
    printf("Archivo leido exitosamente...\n");
    printf("=====================================================\n");
    return 1;
}

Persona BuscarPersona(Persona personasEntrada[],int tam){
    int opc = 0, edad = 0, salario = 0, r = 0;
    char nombre[20];
    printf("¿Como deseas buscar a la persona?\n");
    printf("1 = Nombre\n2 = Edad\n3 = Salario\n");
    scanf("%i", &opc);
    switch(opc){
        case 1:
            printf("¿Cual es el nombre? ");
            scanf("%s", nombre);
            for (int i = 0; i < tam; i++){
                if(strcmp(personasEntrada[i].nombre, nombre) == 0){
                    printf("Persona encontrada:\n");
                    printf("Nombre: %s\nEdad: %i\nSalario: %i\n", personasEntrada[i].nombre, personasEntrada[i].edad, personasEntrada[i].salario);
                    printf("\n¿Si es la persona correcta?\n1 = Si\n2 = No\n");
                    scanf("%i", &r);
                    if(r == 1){
                        printf("Busqueda exitosa!\n");
                        return personasEntrada[i];    
                    }
                }
            }
            printf("Persona no encontrada...\n");
            break;
        case 2:
            printf("¿Cual es la edad? ");
            scanf("%i",&edad);
            for(int i = 0; i < tam; i++){
                if(personasEntrada[i].edad == edad){
                    printf("Persona encontrada:\n");
                    printf("Nombre: %s\nEdad: %i\nSalario: %i\n", personasEntrada[i].nombre, personasEntrada[i].edad, personasEntrada[i].salario);
                    printf("\n¿Si es la persona correcta?\n1 = Si\n2 = No\n");
                    scanf("%i", &r);
                    if(r == 1){
                        printf("Busqueda exitosa!\n");
                        return personasEntrada[i];
                    break;    
                    }
                    }
                }
            printf("Persona no encontrada...\n");
            break;
        case 3:
            printf("¿Cual es el salario? ");
            scanf("%i",&salario);
            for(int i = 0; i < tam; i++){
                if (personasEntrada[i].salario == salario){
                    printf("Persona encontrada:\n");
                    printf("Nombre: %s\nEdad: %i\nSalario: %i\n", personasEntrada[i].nombre, personasEntrada[i].edad, personasEntrada[i].salario);
                    printf("\n¿Si es la persona correcta?\n1 = Si\n2 = No\n");
                    scanf("%i", &r);
                    if(r == 1){
                        printf("Busqueda exitosa!\n");
                        return personasEntrada[i];    
                    }
                    }
            }
            printf("Persona no encontrada...\n");
            break;
        default:
            printf("Opcion ingresada no existe...\n");
            break;
    }
    Persona personaVacia = {"",0,0};
    return personaVacia;
}

void NombrePersona(Persona *persona){
    printf("Escriba el nombre de la persona: ");
    scanf("%s", persona->nombre);
}

void EdadPersona(Persona *persona){
    printf("Escriba la edad de la persona: ");
    scanf("%i", &persona->edad);
}

void SalarioPersona(Persona *persona){
    printf("Escriba el salario de la persona: ");
    scanf("%i", &persona->salario);
}

void EliminarPersona(Persona personasEntrada[], int *tam){
    int resp = 0;
    printf("Personas en la agenda:\n");
    for(int i = 0; i < *tam; i++){
        printf("||===||==========|==========|=============||\n");
        printf("||%d ||Nombre: %s|Edad:   %d|Salario:   %d||\n", i + 1, personasEntrada[i].nombre, personasEntrada[i].edad, personasEntrada[i].salario);
        printf("||---||----------|----------|-------------||\n");
    }
    printf("=====================================================\n");
    printf("¿Desea eliminar a alguna persona?\n1 = Si\n2 = No\n");
    scanf("%d", &resp);
    if(resp == 1){
        int index;
        printf("Ingrese el número de la persona que desea eliminar: ");
        scanf("%d", &index);
        if(index >= 1 && index <= *tam){
            for(int i = index - 1; i < *tam - 1; i++){
                personasEntrada[i] = personasEntrada[i + 1];
            }
            (*tam)--;
            printf("Persona eliminada exitosamente.\n");
        }else{
            printf("Número de persona inválido.\n");
        }
    }
}

void ActualizarInformacion(Persona personasEntrada[], int tam){
    char nombre[20];
    int i, opcion, nuevaEdad, nuevoSalario;
    printf("Ingrese el nombre de la persona a actualizar: ");
    scanf("%s", nombre);
    for (i = 0; i < tam; i++){
        if(strcmp(personasEntrada[i].nombre, nombre) == 0){
            printf("Persona encontrada:\n");
            printf("Nombre: %s\nEdad: %i\nSalario: %i\n", personasEntrada[i].nombre, personasEntrada[i].edad, personasEntrada[i].salario);
            printf("\n¿Qué información desea actualizar?\n");
            printf("1 = Edad\n2 = Salario\n3 = Ambos\n4 = Ninguno\n");
            scanf("%i", &opcion);
            switch(opcion){
                case 1:
                    printf("Ingrese la nueva edad: ");
                    scanf("%i", &nuevaEdad);
                    personasEntrada[i].edad = nuevaEdad;
                    break;
                case 2:
                    printf("Ingrese el nuevo salario: ");
                    scanf("%i", &nuevoSalario);
                    personasEntrada[i].salario = nuevoSalario;
                    break;
                case 3:
                    printf("Ingrese la nueva edad: ");
                    scanf("%i", &nuevaEdad);
                    personasEntrada[i].edad = nuevaEdad;
                    printf("Ingrese el nuevo salario: ");
                    scanf("%i", &nuevoSalario);
                    personasEntrada[i].salario = nuevoSalario;
                    break;
                case 4:
                    printf("Muy bien entonces la información se quedará igual...\n");
                    break;
                default:
                    printf("Opción no válida.\n");
                    break;
            }
            printf("Información actualizada o conservada: \n");
            printf("Nombre: %s\nEdad: %i\nSalario: %i\n", personasEntrada[i].nombre, personasEntrada[i].edad, personasEntrada[i].salario);
            break;
        }
    }

    if (i == tam){
        printf("Persona no encontrada...\n");
    }
}
