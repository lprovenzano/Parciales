#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "utn.h"
#include "lib.h"

int main()
{
    int opcion;

    //ArrayList
    ArrayList* listaDeTareas = al_newArrayList();
    ArrayList* TareasResueltas = al_newArrayList();
    ArrayList* listaDeTareas_pAlta = al_newArrayList();
    ArrayList* listaDeTareas_pBaja = al_newArrayList();

    Tarea* miTarea;

    do
    {
        menu();
        opcion = getValidInt("", "Debe ser numerica", 1,6);
        switch(opcion)
        {
        case 1:
            system("CLS");

            if((cargarTareas(listaDeTareas, miTarea))!=-1)
            {
                printf("Se cargo la lista de tareas con exito.\n\n");
                TareasResueltas = al_clone(listaDeTareas);
            }
            else
            {
                printf("Ocurrio un error, no se pudo cargar.\n\n");
            }
            break;
        case 2:
            system("CLS");

            if((al_isEmpty(listaDeTareas))==0)
            {
                if((particionadoDeListas(listaDeTareas, listaDeTareas_pAlta, listaDeTareas_pBaja, miTarea))!=-1)
                {
                    printf("Se particiono por priodad Alta[1] - Baja[0] con exito.\n\n");
                }
                else
                {
                    printf("Ocurrio un error, no se pudo particionar.\n\n");
                }

            }
            else
            {
                printf("ERROR! Primero debe cargar la lista de tareas.\n\n");
            }

            break;
        case 3:
            system("CLS");

            if((al_isEmpty(listaDeTareas_pAlta))==0 && (al_isEmpty(listaDeTareas_pBaja))==0 && (al_isEmpty(listaDeTareas))==0)
            {
                if(((al_sort(listaDeTareas_pAlta, compararTareas,0))!=-1) && ((al_sort(listaDeTareas_pBaja, compararTareas,0))!=-1))
                {
                    printf("Listas ordenadas correctamente.\n\n");
                }
                else
                {
                    printf("No se ha podido ordenar las listas.\n\n");
                }
            }
            else
            {
                printf("ERROR!!! Debe cargar la lista de tareas y particionar antes de ordenar.\n\n");
            }
            break;
        case 4:
            system("CLS");
            if((al_isEmpty(listaDeTareas))==0)
            {
                resolverTareas(TareasResueltas, miTarea);
            }
            else
            {
                printf("ERROR! Primero debe cargar la lista de tareas.\n\n");
            }
            break;
        case 5:
            system("CLS");
            if((generarArchivos(listaDeTareas_pAlta, listaDeTareas_pBaja, miTarea))!=-1)
            {
                printf("Se generaron los archivos correctamente.\n\n");
            }
            else
            {
                printf("Ocurrio un error. No se generaron los archivos.\n\n");
            }
            break;

        }

    }
    while(opcion!=6);

    free(miTarea);
    free(listaDeTareas);
    free(TareasResueltas);
    free(listaDeTareas_pAlta);
    free(listaDeTareas_pBaja);

    return 0;
}
