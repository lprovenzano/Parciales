#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "ArrayList.h"
#include "utn.h"
#include "log.h"
#include "service.h"



/** \brief Muestra el menu en pantalla y recibe las opciones
 *
 * \param -
 * \return un char.
 *
 */

char menu()
{
    char c;
    printf("1. Leer log\n");
    printf("2. Procesar informacion\n");
    printf("3. Mostrar estadisticas\n");
    printf("\n4. Salir\n\n");
    c=getch();
    return c;
}


/** \brief Constructor estructura LogEntry
 *
 * \param -
 * \return Puntero a LogEntry si es OK - NULL si hay error.
 *
 */

LogEntry* new_Log()
{
    LogEntry* this;
    this = (LogEntry*)malloc(sizeof(LogEntry));
    return this;
}

/** \brief Lee el .txt con el listado de logs y carga dicha estructura.
 *
 * \param Lista donde se encuentra la estructura.
 * \return [-1]=> Error  || [0]=> Si se carg� el .txt satisfactoriamente.
 *
 */

int cargarLog(ArrayList* this)
{
    int retorno = 0;
    FILE* f;
    LogEntry* log;

    char dateAux[20];
    char timeAux[10];
    char serviceIdAux[5];
    char gravedadAux[5];
    char msgAux[140];

    if((f = fopen("files\\log.txt", "r"))==NULL)
    {
        retorno =-1;
    }

    else
    {
        rewind(f);
        while(!(feof(f)))
        {
            log=new_Log();
            if(log!=NULL)
            {
                fflush(stdin);
                fscanf(f,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", dateAux, timeAux, serviceIdAux, gravedadAux, msgAux);
                strcpy(log->date, dateAux);
                strcpy(log->time, timeAux);
                log->serviceId = atoi(serviceIdAux);
                log->gravedad = atoi(gravedadAux);
                strcpy(log->msg, msgAux);
                al_add(this, log);
                //printf("%s--%s--%d--%d--%s\n\n", log->date, log->time, log->serviceId, log->gravedad, log->msg);
            }
        }
    }
    fclose(f);
    free(log);
    return retorno;
}

/** \brief Evalua el campo gravedad bajo los criterios establecidos en el punto 2 del examen.
 *
 * \param Lista donde se encuentra la estructura de Logs
 * \param Lista donde se encuentra la estructura de Servicios
 * \return [-1]=> Error  || [0]=> Si se depuro correctamente.
 *
 */

int procesamientoDeInformacion(ArrayList* lista_logs, ArrayList* lista_service)
{
    int retorno = 0;
    LogEntry* log;
    Service* service;
    int i,j;

    printf("FECHA\t\tHORA\tNOM. SERVICIO\tMENSAJE ERROR\t\tGRAVEDAD\n");

    for(i=0; i<al_len(lista_logs); i++)
    {
        log=new_Log();
        if(log!=NULL)
        {
            log = (LogEntry*)al_get(lista_logs, i);
            if(log->gravedad<3)
            {
                continue;
            }
            for(j=0; j<al_len(lista_service); j++)
            {
                service=new_service();
                if(service!=NULL)
                {
                    service = al_get(lista_service, j);
                    if(log->gravedad>3 && log->gravedad<=7 && log->serviceId==service->id)
                    {
                        printf("%s\t%s\t%s\t%s\t\t %d\n", log->date, log->time, service->name, log->msg, log->gravedad);
                    }

                }
            }
        }
    }
    return retorno;
}

/** \brief Genera un .txt con warnings.
 *
 * \param Lista donde se encuentra la estructura de Logs
 * \param Lista donde se encuentra la estructura de Servicios
 * \return [-1]=> Error  || [0]=> Si se depuro correctamente.
 *
 */

int generarWarning(ArrayList* lista_logs, ArrayList* lista_service)
{
    int retorno = 0;
    LogEntry* log;
    Service* service;
    FILE* f;
    int i,j;

    f = fopen("files\\warnings.txt", "w+");

    if(f==NULL)
    {
        retorno = -1;
    }
    else
    {
        fprintf(f, "FECHA;HORA;NOMBRE SERVICIO;MENSAJE ERROR;EMAIL SOPORTE\n");
        for(i=0; i<al_len(lista_logs); i++)
        {
            log=new_Log();
            if(log!=NULL)
            {
                log = (LogEntry*)al_get(lista_logs, i);
                if(log->gravedad<3)
                {
                    continue;
                }
                for(j=0; j<al_len(lista_service); j++)
                {
                    service=new_service();
                    if(service!=NULL)
                    {
                        service = al_get(lista_service, j);
                        if(log->gravedad==3 && log->serviceId!=45)
                        {
                            fprintf(f,"%s;%s;%s;%s;%s\n", log->date, log->time, service->name, log->msg, service->email);
                        }

                    }
                }
            }
        }
        free(log);
        free(service);
        fclose(f);
    }
    return retorno;
}

/** \brief Genera un .txt con errores.
 *
 * \param Lista donde se encuentra la estructura de Logs
 * \param Lista donde se encuentra la estructura de Servicios
 * \return [-1]=> Error  || [0]=> Si se depuro correctamente.
 *
 */

int generarErrores(ArrayList* lista_logs, ArrayList* lista_service)
{
    int retorno = 0;
    LogEntry* log;
    Service* service;
    FILE* f;
    int i,j;

    f = fopen("files\\errors.txt", "w+");

    if(f==NULL)
    {
        retorno = -1;
    }
    else
    {
        fprintf(f, "FECHA;HORA;NOMBRE SERVICIO;MENSAJE ERROR;EMAIL SOPORTE\n");
        for(i=0; i<al_len(lista_logs); i++)
        {
            log=new_Log();
            if(log!=NULL)
            {
                log = (LogEntry*)al_get(lista_logs, i);
                if(log->gravedad<3)
                {
                    continue;
                }
                for(j=0; j<al_len(lista_service); j++)
                {
                    service=new_service();
                    if(service!=NULL)
                    {
                        service = al_get(lista_service, j);
                        if(log->gravedad>7)
                        {
                            fprintf(f,"%s;%s;%s;%s;%s\n", log->date, log->time, service->name, log->msg, service->email);
                        }

                    }
                }
            }
        }
        free(log);
        free(service);
        fclose(f);
    }
    return retorno;
}

int servicioConMasFallos(ArrayList* lista_logs, ArrayList* lista_service)
{
    int retorno = 0;
    LogEntry* log;
    Service* service;
    int i,j, k=0;

    printf("MENORES A 3: \n\n");

    for(i=0; i<al_len(lista_logs); i++)
    {
        log=new_Log();
        if(log!=NULL)
        {
            log = (LogEntry*)al_get(lista_logs, i);
            for(j=0; j<al_len(lista_service); j++)
            {
                service=new_service();
                if(service!=NULL)
                {
                    service = al_get(lista_service, j);
                    if(log->gravedad<3 && log->serviceId==service->id)
                    {
                        printf("%s\t%s\t%s\t%s\t\t %d\n", log->date, log->time, service->name, log->msg, log->gravedad);
                    }
                }
            }
        }
    }
    return retorno;
}
