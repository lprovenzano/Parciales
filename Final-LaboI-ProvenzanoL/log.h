typedef struct{

    char date[11];
    char time[6];
    int serviceId;
    int gravedad;
    char msg[65];
} LogEntry;

char menu();

LogEntry* new_Log();
int cargarLog(ArrayList* this);
int procesamientoDeInformacion(ArrayList* lista_logs, ArrayList* lista_service);
int generarWarning(ArrayList* lista_logs, ArrayList* lista_service);
int generarErrores(ArrayList* lista_logs, ArrayList* lista_service);
int servicioConMasFallos(ArrayList* lista_logs, ArrayList* lista_service);
