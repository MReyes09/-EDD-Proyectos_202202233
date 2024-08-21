#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H
#include "../data_Structs/LinkedList.cpp"
#include "../models/solicitud.h"
#include "../data_Structs/matriz_struct/Matriz.h"
#include "../data_Structs/doubleLit/dobleList.h"

class User_Controller
{
private:

    int id_User;
    User* User_Logued;
    LinkedList list_Users;
    DoublyLinkedList posts;
    Matriz m;

public:

    User_Controller();
    void sigIn();
    void admin_add();
    User* logIn();
    bool deleteUser();
    void carga_Usuarios();
    void solicitud_Amistad();
    void carga_Solicitudes();
    void solicitudes(int opcion);
    void add_Matriz(Solicitud* solicitud, int i, int j);
    void add_Post();
    void carga_Post();
    void mostrar_Post();
    void gestionar_Usuarios(User* userAd);
    void report_Usuarios();
    void report_Matriz();
    void report_Posts();
    void top5_Usuarios_Posts();
    void top5_Mas_Amigos();
    void reporte_Sol();

};

#endif