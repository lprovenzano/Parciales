typedef struct{
    int id;
    char name[33];
    char email[65];
} Service;


Service* new_service();
int cargarService(ArrayList* this);
