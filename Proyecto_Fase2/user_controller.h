#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

//Archivos del proyecto
#include "user.h"
#include "linkedlist.h"
#include "Matriz.h"
#include "Solicitud.h"
#include "dobleList.h"
#include "Abb.h"

class User_Controller
{
private:
    static User_Controller* instance; // Instancia única
    int id_User;
    User* User_Logued;
    LinkedList list_Users;
    // Constructor privado para que no pueda ser instanciado directamente
    User_Controller();
    DoublyLinkedList posts;
    Matriz m;

public:
    // Método estático para obtener la instancia única
    static User_Controller* getInstance();

    // Métodos relacionados con el manejo de usuarios
    bool sigIn(QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_);
    void admin_add();
    User* logIn(QString gmai, QString password);
    User* addUserTable(int index);
    int sizeList();
    LinkedList& getListaUsers();
    bool carga_Usuarios(QString path);
    bool carga_Solicitudes(QString path);
    void add_Matriz(Solicitud* solicitud, int i, int j);

    bool carga_Post(QString path);
    ABB* arbolAbb();
    void report_Posts();

};

#endif // USER_CONTROLLER_H
