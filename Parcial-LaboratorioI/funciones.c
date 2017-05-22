#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "funciones.h"

void menu()
{
    printf("MENU\n----------------------------------\n\n");
    printf("1. Alta de programadores.\n");
    printf("2. Modificar datos de los programadores.\n");
    printf("3. Baja del programador.\n");
    printf("4. Asignar programador a proyecto.\n");
    printf("5. Listado de programadores.\n");
    printf("6. Listado de todos los proyectos.\n");
    printf("7. Listar proyectos de programador.\n");
    printf("8. Proyecto demandante.\n\n");
    printf("0. Salir.\n\n");

}

void inicializoEnCero(Programador arrayProgramador[], ProgramadorProyecto progProyecto[],int tam, int valor)
{
    int i,j;
    for(i=0; i<tam; i++)
    {
        arrayProgramador[i].estado = valor;
    }
    for(j=0; j<tam; j++)
    {
        progProyecto[j].estado = valor;
    }
}

void cargarCategorias(Categoria niveles[])
{
    int categorias[3] = {1, 2, 3};
    char detalle[3][21] = {"JUNIOR", "SEMISR", "SENIOR"};
    float pago[3] = {10, 20, 25};
    int i;
    for(i=0; i<3; i++)
    {
        niveles[i].idCategoria = categorias[i];
        strcpy(niveles[i].descripcion, detalle[i]);
        niveles[i].pagoPorHora = pago[i];
    }
}

void altaProgramador(Programador arrayProgramador[], int tam)
{
    int i, flag=0;
    for(i=0; i<tam; i++)
    {
        if(arrayProgramador[i].estado==0)
        {
            arrayProgramador[i].id = i+1;
            getValidString("Nombre: ", "No puede contener numeros y/o simbolos.", arrayProgramador[i].nombre);
            getValidString("Apellido: ", "No puede contener numeros y/o simbolos.", arrayProgramador[i].apellido);
            printf("\n1. JUNIOR\n2. SEMISR\n3. SENIOR\n");
            arrayProgramador[i].idCategoria = getValidInt("\n", "Debe ser numerico", 1, 3);
            arrayProgramador[i].estado = 1;
            flag = 1;
            system("@cls||clear");
            printf("El programador se cargo con exito.");
            getChar("\n\nENTER (para continuar)");
            break;
        }
    }
    if(flag==0)
    {
        printf("No hay espacio disponible.");
    }
    system("@cls||clear");
    menu();
}

void cargarProgramador(Programador arrayProgramador[])
{
    //Cargo algunos por defecto para test
    int id[3] = {1, 2, 3};
    char nombre[3][21] = {"Carlos", "Christian", "Juan"};
    char apellido[3][21] = {"Molina", "Miro", "Perez"};
    int categoria[3] = {1,2,3};
    int k;
    for(k=0; k<3; k++)
    {
        arrayProgramador[k].id = id[k];
        strcpy(arrayProgramador[k].nombre, nombre[k]);
        strcpy(arrayProgramador[k].apellido, apellido[k]);
        arrayProgramador[k].idCategoria = categoria[k];
        arrayProgramador[k].estado = 1;
    }
}

void ordenarProgramadores(Programador arrayProgramador[], int tamProg)
{
    int i,j;
    Programador auxiliarProgramador;

    for(i=0; i < tamProg-1; i++)
    {
        if (arrayProgramador[i].estado == 0)
        {
            continue;
        }

        for(j=i+1; j<tamProg; j++)
        {
            if(arrayProgramador[j].estado == 0)
            {
                continue;
            }
            if(arrayProgramador[i].id > arrayProgramador[j].id)
            {
                auxiliarProgramador = arrayProgramador[j];
                arrayProgramador[j] = arrayProgramador[i];
                arrayProgramador[i] = auxiliarProgramador;
            }

        }
    }
}

void listarProgramador(Programador arrayProgramador[], Categoria niveles[],int tam, ProgramadorProyecto progProyecto[], Proyecto arrayProyecto[], int tamProy)
{
    int i,j,k,l, auxiliarID;
    char auxCategoria[21], titulo[51];
    float montoACobrar, precioHoras;
    //Carga secuencial por opcion
    system("@cls||clear");
    printf("LISTADO DE PROGRAMADORES\n");
    printf("-------------------------------------------------------\n\n");
    printf("|ID|  NOMBRE  |  APELLIDO  |  CAT. |        PROYECTO         |    MONTO   |\n\n");
    for(i=0; i<tam; i++)
    {
        if(arrayProgramador[i].estado!=0)
        {
            auxiliarID = arrayProgramador[i].id;

            for(l=0; l<15; l++)
            {
                if(arrayProgramador[i].idCategoria == niveles[l].idCategoria)
                {
                    strcpy(auxCategoria, niveles[l].descripcion);
                    precioHoras = niveles[l].pagoPorHora;
                    break;
                }
            }

            for(j=0; j<15; j++)
            {
                if(auxiliarID == progProyecto[j].idProgramador && progProyecto[j].estado==1)
                {
                    for(k=0; k<tamProy; k++)
                    {
                        if(progProyecto[j].idProyecto == arrayProyecto[k].id && progProyecto[j].estado==1)
                        {
                            strcpy(titulo, arrayProyecto[k].titulo);
                            montoACobrar = progProyecto[j].cantHoras;
                            break;
                        }
                    }
                    printf(" %d   %-s\t%-s\t    %-s\t%-5s        $ %-.2f\n", arrayProgramador[i].id,arrayProgramador[i].nombre, arrayProgramador[i].apellido, auxCategoria, titulo, montoACobrar*precioHoras);
                }
            }
        }
    }
}

int buscarProgramadorId(Programador arrayProgramador[], int busqueda, int tam)
{
    int i, flag=0;
    for(i=0; i<tam; i++)
    {
        if(busqueda == arrayProgramador[i].id)
        {
            flag=1;
            break;
        }
    }
    return flag;
}

int buscarPosicionProgramador(Programador arrayProgramador[], int tamProg)
{
    int i;
    for(i=0; i < tamProg; i++)
    {
        if(arrayProgramador[i].estado == 0)
        {
            return i;
        }
    }
    return -1;
}

int buscarIndiceProgramador(Programador arrayProgramador[], int idBusqueda, int tamProg)
{
    int i;
    for(i=0; i < tamProg; i++)
    {
        if(idBusqueda == arrayProgramador[i].id)
        {
            return i;
        }
    }
    return -1;
}

void modificarProgramador(Programador arrayProgramador[], Categoria niveles[],int tam, ProgramadorProyecto progProyecto[], Proyecto arrayProyecto[], int tamProy)
{
    //listarProgramador(arrayProgramador, niveles, tam, progProyecto, arrayProyecto, tamProy);
    system("@cls||clear");
    int i,j, idAuxiliar, validoBusqueda,flag=0, opcion;
    printf("LISTADO DE PROGRAMADORES\n");
    printf("-------------------------------------------------------\n\n");
    printf("|ID|  NOMBRE  |  APELLIDO  |  CATEGORIA\n\n");
    for(j=0; j<tam; j++)
    {
        if(arrayProgramador[j].estado!=0)
        {
            printf(" %d   %-s\t%-s\t        %-d\n", arrayProgramador[j].id,arrayProgramador[j].nombre, arrayProgramador[j].apellido, arrayProgramador[j].idCategoria);
        }
    }
    printf("\n--------------------------------------------------------------------------------\n\n");
    idAuxiliar = getValidInt("ID de Programador a modificar: ", "Error! solo numerico.", 1,50);
    validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliar, tam);
    while(validoBusqueda!=1)
    {
        printf("Ese ID no existe.");
        getChar("\n\nENTER (para continuar)");
        system("@cls||clear");
        //listarProgramador(arrayProgramador, niveles, tam, progProyecto, arrayProyecto, tamProy);
        printf("LISTADO DE PROGRAMADORES\n");
        printf("-------------------------------------------------------\n\n");
        printf("|ID|  NOMBRE  |  APELLIDO  |  CATEGORIA\n\n");
        for(j=0; j<tam; j++)
        {
            if(arrayProgramador[j].estado!=0)
            {
                printf(" %d   %-s\t%-s\t        %-d\n", arrayProgramador[j].id,arrayProgramador[j].nombre, arrayProgramador[j].apellido, arrayProgramador[j].idCategoria);
            }
        }
        printf("\n--------------------------------------------------------------------------------\n\n");
        idAuxiliar = getValidInt("ID de Programador a modificar: ", "Error! solo numerico.", 1,50);
        validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliar, tam);
    }
    system("@CLS||clear");
    printf("LISTADO DE PROGRAMADORES\n");
    printf("-------------------------------------------------------\n\n");
    printf("|ID|  NOMBRE  |  APELLIDO  |  CATEGORIA\n\n");
    for(j=0; j<tam; j++)
    {
        if(arrayProgramador[j].estado!=0)
        {
            printf(" %d   %-s\t%-s\t        %-d\n", arrayProgramador[j].id,arrayProgramador[j].nombre, arrayProgramador[j].apellido, arrayProgramador[j].idCategoria);
        }
    }
    opcion = getValidInt("\nParametro a modificar: \n\n 1. Nombre \n 2. Apellido \n 3. Categoria\n\n", "Solo numerico", 1,3);
    for(i=0; i<tam; i++)
    {
        if(idAuxiliar==arrayProgramador[i].id)
        {
            switch(opcion)
            {
            case 1:
                getValidString("\nNombre: ", "Solo letras.", arrayProgramador[i].nombre);
                flag=1;
                break;
            case 2:
                getValidString("\nApellido: ", "Solo letras.", arrayProgramador[i].apellido);
                flag=1;
                break;
            case 3:
                printf("\nCategoria\n1. JUNIOR\n2. SEMISR\n3. SENIOR\n");
                arrayProgramador[i].idCategoria= getValidInt("", "Solo numerico.", 1,3);
                flag=1;
                break;
            }
            printf("\n\nSe ha modificado con exito");
            getChar("\n\nENTER (para continuar)");
            break;
        }
    }
    if(flag==0)
    {
        printf("No se ha podido modificar, ya que ese ID no existe.");
    }
    system("@cls||clear");
    menu();

}

void borrarProgramador(Programador arrayProgramador[], Categoria niveles[],int tam, ProgramadorProyecto progProyecto[], Proyecto arrayProyecto[], int tamProy)
{
    system("@cls||clear");
    int i,j, idAuxiliar, validoBusqueda,flag=0;
    printf("LISTADO DE PROGRAMADORES\n");
    printf("-------------------------------------------------------\n\n");
    printf("|ID|  NOMBRE  |  APELLIDO  |  CATEGORIA\n\n");
    for(j=0; j<tam; j++)
    {
        if(arrayProgramador[j].estado!=0)
        {
            printf(" %d   %-s\t%-s\t        %-d\n", arrayProgramador[j].id,arrayProgramador[j].nombre, arrayProgramador[j].apellido, arrayProgramador[j].idCategoria);
        }
    }
    printf("\n--------------------------------------------------------------------------------\n\n");
    idAuxiliar = getValidInt("ID de Programador a borrar: ", "Error! solo numerico.", 1,50);
    validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliar, tam);
    while(validoBusqueda!=1)
    {
        printf("Ese ID no existe.");
        getChar("\n\nENTER (para continuar)");
        system("@cls||clear");
        printf("LISTADO DE PROGRAMADORES\n");
        printf("-------------------------------------------------------\n\n");
        printf("|ID|  NOMBRE  |  APELLIDO  |  CATEGORIA\n\n");
        for(j=0; j<tam; j++)
        {
            if(arrayProgramador[j].estado!=0)
            {
                printf(" %d   %-s\t%-s\t        %-d\n", arrayProgramador[j].id,arrayProgramador[j].nombre, arrayProgramador[j].apellido, arrayProgramador[j].idCategoria);
            }
        }
        printf("\n--------------------------------------------------------------------------------\n\n");
        idAuxiliar = getValidInt("ID de Programador a borrar: ", "Error! solo numerico.", 1,50);
        validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliar, tam);
    }
    system("@CLS||clear");
    for(i=0; i<tam; i++)
    {
        if(idAuxiliar==arrayProgramador[i].id && arrayProgramador[i].estado==1)
        {
            arrayProgramador[i].estado=0;
            flag=1;
            printf("Se ha borrado con exito.");
            getChar("\n\nENTER (para continuar)");
            system("@cls||clear");
            break;
        }
    }
    if(flag==0)
    {
        printf("No se ha podido borrar, el ID de programador no existe.");
        getChar("\n\nENTER (para continuar)");
        system("@cls||clear");
        menu();
    }
    menu();
}

void cargarProyecto(Proyecto arrayProyecto[])
{
    int i;
    int idProyecto[3] = {5,6,7};
    char descripcion [3][51] = {"Programador Android","Programador COBOL","Programador JAVA"};
    int cantidad[3] = {0};

    for(i=0; i<3; i++)
    {
        arrayProyecto[i].id = idProyecto[i];
        strcpy(arrayProyecto[i].titulo, descripcion[i]);
        arrayProyecto[i].cantProgramadores = cantidad[i];
    }
}

void listarProyecto(Proyecto arrayProyecto[], int tamProy, Programador arrayProgramador[], int tamProg, ProgramadorProyecto progProyecto[])
{
    int j,i,k, junior, semisr, senior, totalPersonas=0;
    junior = 0;
    semisr = 0;
    senior = 0;
    printf("LISTADO DE PROYECTOS\n");
    printf("-------------------------------------------------------\n\n");
    printf("| ID |          NOMBRE          | JUNIOR | SEMISR | SENIOR |  CANT. PROG\n\n");
    for(i=0; i<3; i++)
    {
        for(j=0; j<tamProg; j++)
        {
            if(progProyecto[j].estado!=0 && arrayProyecto[i].id == progProyecto[j].idProyecto)
            {
                for(k=0; k<tamProg; k++)
                {
                    if(arrayProgramador[k].estado!=0 && arrayProgramador[k].id == progProyecto[j].idProgramador)
                    {
                        if(arrayProgramador[k].idCategoria == 1)
                        {
                            junior++;
                            break;
                        }

                        if(arrayProgramador[k].idCategoria == 2)
                        {
                            semisr++;
                            break;
                        }

                        else
                        {
                            senior++;
                            break;
                        }
                    }
                }
            }
        }
        totalPersonas = junior+semisr+senior;
        arrayProyecto[i].cantProgramadores = totalPersonas;
        printf("  %d\t%-25s\t%d\t%d\t%d      %d\n", arrayProyecto[i].id,arrayProyecto[i].titulo, junior, semisr, senior, totalPersonas);
        junior = 0;
        semisr = 0;
        senior = 0;
    }
}

void asignarProgramador(Programador arrayProgramador[], int tamProg, Proyecto arrayProyecto[], int tamProy, ProgramadorProyecto progProyecto[], Categoria niveles[])
{
    int idAuxiliarProgramador,idAuxiliarProyecto,validoBusqueda, i,j,k, flag=0;
    float horas;
    system("@cls||clear");
    printf("LISTADO DE PROGRAMADORES\n");
    printf("-------------------------------------------------------\n\n");
    printf("|ID|  NOMBRE  |  APELLIDO  |  CATEGORIA\n\n");
    for(j=0; j<tamProg; j++)
    {
        if(arrayProgramador[j].estado!=0)
        {
            printf(" %d   %-s\t%-s\t        %-d\n", arrayProgramador[j].id,arrayProgramador[j].nombre, arrayProgramador[j].apellido, arrayProgramador[j].idCategoria);
        }
    }

    idAuxiliarProgramador = getValidInt("\n\nID de Programador: ", "Error! solo numerico.", 1,50);
    validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliarProgramador, tamProg);

    while(validoBusqueda!=1)
    {
        printf("Ese ID no existe.");
        getChar("\n\nENTER (para continuar)");
        system("@cls||clear");
        listarProgramador(arrayProgramador, niveles, tamProg, progProyecto, arrayProyecto, tamProy);
        idAuxiliarProgramador = getValidInt("\n\nID de Programador: ", "Error! solo numerico.", 1,50);
        validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliarProgramador, tamProg);
    }

    system("@cls||clear");
    printf("\nLISTADO DE PROYECTOS\n");
    printf("-------------------------------------------------------\n\n");
    printf("| ID |          NOMBRE          | CANT. PROG \n\n");
    for(i=0; i<3; i++)
    {
        printf("  %d\t%-23s\t     %-d\t\n", arrayProyecto[i].id,arrayProyecto[i].titulo, arrayProyecto[i].cantProgramadores);
    }
    idAuxiliarProyecto = getValidInt("\n\nID de Proyecto: ", "Error! solo numerico.", 5,7);
    horas = getFloat("Cantidad de horas: ");
    while(horas<0)
    {
        horas = getFloat("Debe ser mayor a 0 (cero)\nCantidad de horas: ");
    }

    //RELACION
    for(i=0; i<tamProg; i++)
    {
        if(arrayProgramador[i].id == idAuxiliarProgramador && arrayProgramador[i].estado == 1)
        {
            flag = 1;
            for(j=0; j<tamProy; j++)
            {
                if(progProyecto[j].estado  == 1 && progProyecto[j].idProgramador == idAuxiliarProgramador && progProyecto[j].idProyecto == idAuxiliarProyecto)
                {
                    printf("\nYa existe ese programador en este proyecto.");
                    break;
                }
                if(progProyecto[j].estado == 0)
                {
                    progProyecto[j].idProgramador = idAuxiliarProgramador;
                    progProyecto[j].idProyecto = idAuxiliarProyecto;
                    progProyecto[j].cantHoras = horas;
                    progProyecto[j].estado = 1;
                    printf("\nEl programador ha sido cargado exitosamente");
                    getChar("\n\nENTER (para continuar)");
                    system("@cls||clear");
                    break;
                }
            }
        }
    }
    if(flag == 0)
    {
        printf("\nEl ID de Programador no existe");
        getChar("\n\nENTER (para continuar)");
        system("@cls||clear");
        menu();
    }

    printf("ESTRUCTURA RELACIONAL\n\n");
    for(k=0; k<10; k++)
    {
        if(progProyecto[k].estado != 0)
        {
            printf("\n id programdor %d, id proyecto %d, estado %d, horas %.02f", progProyecto[k].idProgramador, progProyecto[k].idProyecto, progProyecto[k].estado, progProyecto[k].cantHoras);
        }
    }
    getChar("\n\nENTER (para continuar)");
    system("@cls||clear");
    menu();

}

void listarProyectosProgramador(Programador arrayProgramador[], int tamProg, Proyecto arrayProyecto[], int tamProy, ProgramadorProyecto progProyecto[], Categoria niveles[])
{
    int idAuxiliarProgramador,validoBusqueda, i,j, indice, flag=0;
    char titulo[51];
    system("@cls||clear");
    printf("LISTADO DE PROGRAMADORES\n");
    printf("-------------------------------------------------------\n\n");
    printf("|ID|  NOMBRE  |  APELLIDO  |  CATEGORIA\n\n");
    for(j=0; j<tamProg; j++)
    {
        if(arrayProgramador[j].estado!=0)
        {
            printf(" %d   %-s\t%-s\t        %-d\n", arrayProgramador[j].id,arrayProgramador[j].nombre, arrayProgramador[j].apellido, arrayProgramador[j].idCategoria);
        }
    }

    idAuxiliarProgramador = getValidInt("\n\nID de Programador: ", "Error! solo numerico.", 1,50);
    validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliarProgramador, tamProg);

    while(validoBusqueda!=1)
    {
        printf("Ese ID no existe.");
        getChar("\n\nENTER (para continuar)");
        system("@cls||clear");
        listarProgramador(arrayProgramador, niveles, tamProg, progProyecto, arrayProyecto, tamProy);
        idAuxiliarProgramador = getValidInt("\n\nID de Programador: ", "Error! solo numerico.", 1,50);
        validoBusqueda = buscarProgramadorId(arrayProgramador, idAuxiliarProgramador, tamProg);
    }
    indice = buscarIndiceProgramador(arrayProgramador, idAuxiliarProgramador, tamProg);
    for(i=0; i<tamProy; i++)
    {
        if(progProyecto[i].estado!=0 && progProyecto[i].idProgramador == idAuxiliarProgramador)
        {
            for(j=0; j<tamProy; j++)
            {
                if(arrayProyecto[j].id == progProyecto[i].idProyecto)
                {
                    strcpy(titulo, arrayProyecto[j].titulo);
                }
            }
            system("@cls||clear");
            printf("%-s %-s \n \t%-d %-s", arrayProgramador[indice].nombre,arrayProgramador[indice].apellido, progProyecto[i].idProyecto,titulo);
            flag=1;
        }
    }
    if(flag==0)
    {
        system("@cls||clear");
        printf("No existen proyectos para ese programador");
    }
    getChar("\n\nENTER (para continuar)");
    system("@cls||clear");
    menu();

}

void proyectoMasDemandado(Proyecto arrayProyecto[], int tamProy, ProgramadorProyecto progProyecto[])
{
    int i,j;
    Proyecto auxiliar;
    for(i=0;i<3-1;i++)
    {
        for(j=i+1;j<3;j++)
        {
            if(arrayProyecto[i].cantProgramadores<arrayProyecto[j].cantProgramadores)
            {
                auxiliar = arrayProyecto[i];
                arrayProyecto[i] = arrayProyecto[j];
                arrayProyecto[j] = auxiliar;
            }
        }
    }
    system("@cls||clear");
    for(i=0;i<3;i++)
    {
        printf("\n%s es el mas demandado, tiene %d programadores.\n", arrayProyecto[i].titulo,arrayProyecto[i].cantProgramadores);
        break;
    }

    getChar("\n\nENTER (para continuar)");
    system("@cls||clear");
    menu();

}


