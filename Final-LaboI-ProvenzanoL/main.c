#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "utn.h"
#include "log.h"
#include "service.h"

int main()
{
    ArrayList* lista_log = al_newArrayList();
    ArrayList* lista_service = al_newArrayList();

    char salir='s';
    do
    {
        switch(menu())
        {
        case '1':
            if((cargarLog(lista_log))!=-1 && (cargarService(lista_service))!=-1)
            {
                pause("Se leyeron los logs correctamente.");
            }
            else
            {
                pause("Se produjo un error, no se leyeron los logs.");
            }

            break;
        case '2':
            system("cls");
            if((al_isEmpty(lista_log))==0 && (al_isEmpty(lista_service))==0)
            {
                if((procesamientoDeInformacion(lista_log, lista_service))!=-1)
                {
                    if((generarWarning(lista_log, lista_service))!=-1 && (generarErrores(lista_log, lista_service))!=-1)
                    {
                        pause("\n(ENTER) para continuar...");
                    }
                    else
                    {
                        pause("No se generaron los txt");
                    }

                }
                else
                {
                    pause("Ocurrio un error al mostrar. (ENTER)");
                }
            }
            else
            {
                pause("Primero debe ejecutar el punto 1. (ENTER)");
            }
            break;
        case '3':
            servicioConMasFallos(lista_log, lista_service);
            break;
        case '4':
            salir = 'n';
            break;
        }

    }while(salir == 's');
    return 0;
}

