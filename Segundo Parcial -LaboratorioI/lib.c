#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "utn.h"
#include "lib.h"

/** \brief Asigna espacio en memoria para una nueva estructura. (Constructor)
 *
 * \param -
 * \param -
 * \return NULL=> Error || Puntero a estructura "Tarea".
 *
 */

Tarea* newTarea()
{
    Tarea* this;
    this = (Tarea*)malloc(sizeof(Tarea));
    return this;
}

/** \brief Imprime en pantalla el menu.
 *
 * \param -
 * \param -
 * \return void.
 *
 */
void menu()
{
    printf("1. Cargar lista de tareas.\n");
    printf("2. Particionar por prioridad.\n");
    printf("3. Ordenar.\n");
    printf("4. Resolver tareas.\n");
    printf("5. Generar.\n\n");
    printf("6. Salir.\n\n");
}

/** \brief Lee el .csv con el listado de tareas y carga dicha estructura.
 *
 * \param Lista donde se encuentra la estructura.
 * \param Estructura con datos a mostrar.
 * \return [-1]=> Error / NULL. || [0]=> Si se cargó el .csv satisfactoriamente.
 *
 */
int cargarTareas(ArrayList* this, Tarea* t)
{
    int retorno = 0;
    FILE* f;
    char descripcionAux[101], prioridadAux[3], tiempoAux[5];

    if((f = fopen("tar.csv", "r"))==NULL)
        retorno =-1;

    while(!(feof(f)))
    {
        t=newTarea();
        if(t!=NULL)
        {
            fscanf(f,"%[^,],%[^,],%[^\n]\n", descripcionAux, prioridadAux, tiempoAux);
            strcpy(t->descripcion, descripcionAux);
            t->prioridad = atoi(prioridadAux);
            t->tiempo = atof(tiempoAux);
            al_add(this, t);
        }
    }

    return retorno;
}

/** \brief Imprime en pantalla la lista seleccionada.
 *
 * \param Lista donde se encuentra la estructura.
 * \param Estructura con datos a mostrar.
 * \return void.
 *
 */

void printLista(ArrayList* this, Tarea* t)
{
    printf("%s---%d---%.2f\n",t->descripcion,t->prioridad, t->tiempo);

}

/** \brief Toma la lista iniciar y bajo el criterio de "prioridad" genera dos: una de p. Alta / p. Baja.
 *
 * \param Lista inicial.
 * \param Lista prioridad alta.
 * \param Lista prioridad baja.
 * \param Estructura con datos a cargar.
 * \return [-1]=> Error. || [0]=> Si se particiono satisfactoriamente.
 *
 */

int particionadoDeListas(ArrayList* listaInicial, ArrayList* lista_pAlta, ArrayList* lista_pBaja, Tarea* t)
{
    int i, retorno=0;

    for(i=0; i<al_len(listaInicial); i++)
    {
        t = (Tarea*) al_get(listaInicial,i);
        if(t->prioridad==0)
        {
            al_add(lista_pBaja,t);

        }
        if(t->prioridad==1)
        {
            al_add(lista_pAlta,t);
        }
    }

    return retorno;
}

/** \brief Clona una lista y nos permite realizar bajas retornando el indice eliminado.
 *
 * \param Lista inicial.
 * \param Lista clonada.
 * \param Estructura con datos a cargar.
 * \return [-1]=> Error. || [0]=> Si se particiono satisfactoriamente.
 *
 */
int resolverTareas(ArrayList* listaInicial, ArrayList* listaClonada, Tarea* t)
{

    int i, retorno=0, checkIndex;

    listaClonada = al_clone(listaInicial);

    for(i=0; i<al_len(listaClonada); i++)
    {
        t = (Tarea*)al_get(listaClonada,i);
        printf("(%d)--%s---%d---%.2f\n",al_indexOf(listaClonada, t),t->descripcion,t->prioridad, t->tiempo);
    }

    checkIndex = getValidInt("\nSeleccione el indice de la tarea a resolver: ", "Debe ser numerico", 0, al_len(listaClonada));
    if((al_pop(listaClonada, checkIndex-1))!=NULL)
    {
        t=al_get(listaClonada, checkIndex-1);
        printf("Se ha resuelto: \n");
        printf("%s---%d---%.2f\n",t->descripcion,t->prioridad, t->tiempo);
    }
    return retorno;


}

/** \brief Escribe en un archivo de texto los datos de la estructura Persona.
 *
 * \param Lista donde se encuentra la estructura.
 * \param Estructura con datos a mostrar.
 * \return [-1]=> Error / NULL. || [0]=> Si se escribio en el txt satisfactoriamente.
 *
 */
int generarArchivos(ArrayList* lista_pAlta, ArrayList* lista_pBaja, Tarea* t)
{
    int i, retorno=-1, j;
    FILE *fAlta;
    FILE *fBaja;

    fAlta=fopen("pAlta.csv", "w+");
    fBaja =fopen("pBaja.csv", "w+");

    if((fAlta == NULL) || (fBaja == NULL))
    {
        printf("No se pudo abrir el/los archivo\n");
    }
    else
    {
        for(i=0; i<al_len(lista_pAlta); i++)
        {
            t = (Tarea*)al_get(lista_pAlta,i);
            fflush(stdin);
            fprintf(fAlta,"%s,%d,%.2f\n",t->descripcion,t->prioridad, t->tiempo);
        }

        for(j=0; j<al_len(lista_pBaja); j++)
        {
            t = (Tarea*)al_get(lista_pBaja,j);
            fflush(stdin);
            fprintf(fBaja,"%s,%d,%.2f\n",t->descripcion,t->prioridad, t->tiempo);
        }

        retorno = 0;
    }

    fclose(fAlta);
    fclose(fBaja);
    return retorno;
}

/** \brief Compara tareas en funcion del tiempo.
 *
 * \param Puntero a estructura "Tarea"
 * \param Puntero a estructura "Tarea"
 * \return [-1]=> A<B  || [1]=> A>B || [0] No comparó.
 *
 */
int compararTareas(Tarea* listaA,Tarea* listaB)
{

    if( listaA->tiempo > listaB->tiempo)
    {
        return 1;
    }
    if( listaA->tiempo < listaB->tiempo)
    {
        return -1;
    }
    return 0;

}



