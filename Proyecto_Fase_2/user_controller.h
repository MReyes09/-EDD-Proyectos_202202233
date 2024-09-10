#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

//Archivos del proyecto
#include "user.h"
#include "linkedlist.h"

class User_Controller
{
private:
    static User_Controller* instance; // Instancia única
    int id_User;
    User* User_Logued;
    LinkedList list_Users;
    // Constructor privado para que no pueda ser instanciado directamente
    User_Controller();

public:
    // Método estático para obtener la instancia única
    static User_Controller* getInstance();

    // Métodos relacionados con el manejo de usuarios
    void sigIn(QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_);
    void admin_add();
    User* logIn(QString gmai, QString password);
    User* addUserTable(int index);
    int sizeList();
    LinkedList& getListaUsers();
    void printUsers();

};

#endif // USER_CONTROLLER_H
