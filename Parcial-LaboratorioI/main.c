/*******************************************************************
    *   Programa: Parcial Laboratorio I - Recuperatorio.
    *
    *
    *   Version:0.1 - 22/05/2017.
    *   Autor: Luca Provenzano | 1F.
    *
********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "funciones.h"


int main()
{
    //VARIABLES
    int opcion;
    //_________________________________________________________________

    //Defino los array de estructuras.
    Categoria niveles[4];
    Programador arrayProgramador[MAXPROGRAMADOR];
    Proyecto arrayProyecto[MAXPROYECTO];
    ProgramadorProyecto progProyecto[10];
    //__________________________________________________________________

    inicializoEnCero(arrayProgramador, progProyecto, MAXPROGRAMADOR, 0); //Estados en Cero
    //__________________________________________________________________
    //Cargo a mano arrays de estructuras
    cargarCategorias(niveles);
    cargarProgramador(arrayProgramador);
    cargarProyecto(arrayProyecto);
    //__________________________________________________________________

    //Ordenamientos
    ordenarProgramadores(arrayProgramador, MAXPROGRAMADOR);
    //__________________________________________________________________

    menu();
    do
    {
       opcion = getValidInt("", "Debe ser un numero valido.",0,9);
       switch(opcion)
       {
       case 1:
           altaProgramador(arrayProgramador, MAXPROGRAMADOR);
        break;
        case 2:
            modificarProgramador(arrayProgramador, niveles, MAXPROGRAMADOR, progProyecto, arrayProyecto, MAXPROYECTO);
        break;
        case 3:
            borrarProgramador(arrayProgramador, niveles, MAXPROGRAMADOR, progProyecto, arrayProyecto, MAXPROYECTO);
        break;
        case 4:
            asignarProgramador(arrayProgramador, MAXPROGRAMADOR, arrayProyecto, MAXPROYECTO, progProyecto, niveles);
        break;
        case 5:
            listarProgramador(arrayProgramador, niveles, MAXPROGRAMADOR, progProyecto, arrayProyecto, MAXPROYECTO);
            getChar("\n\nENTER (para continuar)");
            system("@cls||clear");
            menu();
        break;
        case 6:
            system("@cls||clear");
            listarProyecto(arrayProyecto, MAXPROYECTO, arrayProgramador, MAXPROGRAMADOR, progProyecto);
            getChar("\n\nENTER (para continuar)");
            system("@cls||clear");
            menu();
        break;
        case 7:
            listarProyectosProgramador(arrayProgramador, MAXPROGRAMADOR, arrayProyecto, MAXPROYECTO, progProyecto, niveles);
        break;
        case 8:
            proyectoMasDemandado(arrayProyecto, MAXPROYECTO, progProyecto);
        break;
       }
    }while(opcion!=0);
    return 0;
}
