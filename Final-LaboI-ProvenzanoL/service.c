#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "utn.h"
#include "log.h"
#include "service.h"


/** \brief Constructor estructura Service
 *
 * \param -
 * \return Puntero a Service si es OK - NULL si hay error.
 *
 */

Service* new_service()
{
    Service* this;
    this = (Service*)malloc(sizeof(Service));
    return this;
}

/** \brief Lee el .txt con el listado de servicios y carga dicha estructura.
 *
 * \param Lista donde se encuentra la estructura.
 * \return [-1]=> Error  || [0]=> Si se cargó el .txt satisfactoriamente.
 *
 */

int cargarService(ArrayList* this)
{
    int retorno = 0;
    FILE* f;
    Service* service;

    char idAux[5];
    char nameAux[40];
    char emailAux[80];

    if((f = fopen("files\\services.txt", "r"))==NULL)
    {
        retorno =-1;
    }

    else
    {
        rewind(f);
        while(!(feof(f)))
        {
            service=new_service();
            if(service!=NULL)
            {
                    fflush(stdin);
                    fscanf(f,"%[^;];%[^;];%[^\n]\n", idAux, nameAux, emailAux);
                    service->id = atoi(idAux);
                    strcpy(service->name, nameAux);
                    strcpy(service->email, emailAux);
                    al_add(this, service);
                    //printf("--%d--%s--%s\n", service->id, service->name, service->email);
            }
        }
    }
    fclose(f);
    free(service);
    return retorno;
}
