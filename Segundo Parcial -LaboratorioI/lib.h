#include "ArrayList.h"

typedef struct{

    char descripcion[101];
    int prioridad;
    float tiempo;
} Tarea;

Tarea* newTarea();
void menu();
int cargarTareas(ArrayList* this, Tarea* t);
void printLista(ArrayList* this, Tarea* t);
int particionadoDeListas(ArrayList* listaInicial, ArrayList* lista_pAlta, ArrayList* lista_pBaja, Tarea* t);
int ordenarListas(ArrayList* lista_pAlta, ArrayList* lista_pBaja, Tarea* t);
int resolverTareas(ArrayList* listaClonada, Tarea* t);
int generarArchivos(ArrayList* lista_pAlta, ArrayList* lista_pBaja, Tarea* t);
int compararTareas(Tarea* listaA, Tarea* listaB);
