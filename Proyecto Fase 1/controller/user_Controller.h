#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H
#include "../data_Structs/LinkedList.cpp"

class User_Controller
{
private:

    int id_User;
    User* User_Logued;
    LinkedList list_Users;

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
};

#endif