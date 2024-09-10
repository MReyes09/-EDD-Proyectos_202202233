#include "user_controller.h"
#include <iostream>
#include <locale>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <limits>
#include <QString>
using namespace std;

// Inicializar el puntero a la instancia como nullptr
User_Controller* User_Controller::instance = nullptr;

// Constructor privado (no se puede instanciar fuera de la clase)
User_Controller::User_Controller()
{
    id_User = 0;
    admin_add();
}

// Método para obtener la instancia única de la clase
User_Controller* User_Controller::getInstance() {
    if (instance == nullptr) {
        instance = new User_Controller();
    }
    return instance;
}

void User_Controller::sigIn(QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_)
{
    User* newUser = new User(id_User, name_, lastname_, email_, password_, birthdate_, "User");
    id_User += 1;
    list_Users.append(newUser);
}

void User_Controller::admin_add()
{
    QString name = "admin@gmail.com";
    QString password = "EDD2S2024";

    User *newUser = new User(id_User, name, "", name, password, "", "Admin");
    id_User += 1;
    list_Users.append(newUser);

}

User* User_Controller::logIn(QString gmail, QString password)
{

    User_Logued = list_Users.search_LogIn(gmail, password);
    if( User_Logued != nullptr )
    {
        return nullptr;
    }
    else
    {
        return User_Logued;
    }

}

LinkedList& User_Controller::getListUsers()
{
    return list_Users;
}
