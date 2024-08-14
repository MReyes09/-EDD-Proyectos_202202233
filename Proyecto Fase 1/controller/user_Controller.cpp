#include <iostream>
#include "user_Controller.h"
#include <locale>
#include <windows.h>
#include "../models/user.h"


using namespace std;

User_Controller::User_Controller(){
    id_User = 0;
    admin_add();
}

void User_Controller::sigIn()
{
    SetConsoleOutputCP(CP_UTF8);
    system("cls");
    // Variables para capturar la entrada del usuario
    string name, lastname, email, password, birthdate;

    // Función lambda para simplificar la entrada de datos
    auto solicitarDato = [](const string& mensaje) {
        string dato;
        cout << mensaje;
        getline(cin, dato);
        return dato;
    };
    cout << " ********************************************************************* " << endl;
    cout << " || (Opcion 2) Ingresa los siguientes datos para registrarte" << endl;

    // Solicitar datos al usuario
    name = solicitarDato(" || Nombre > ");
    lastname = solicitarDato(" || Apellido > ");
    email = solicitarDato(" || Correo > ");
    password = solicitarDato(" || Contraseña > ");
    birthdate = solicitarDato(" || Fecha de cumpleaños (dd/mm/yyyy) > ");

    User* newUser = new User(id_User, name, lastname, email, password, birthdate, "User");
    id_User += 1;
    list_Users.append(newUser);
}

void User_Controller::admin_add()
{
    string name = "admin@gmail.com";
    string password = "EDD2S2024";

    User *newUser = new User(id_User, name, "", name, password, "", "Admin");
    id_User += 1;
    list_Users.append(newUser);

}

User* User_Controller::logIn()
{

    string password, email;

    // Función lambda para simplificar la entrada de datos
    auto solicitarDato = [](const string& mensaje) {
        string dato;
        cout << mensaje;
        getline(cin, dato);
        return dato;
    };

    cout << " ********************************************************************* " << endl;
    cout << " || (Opcion 1) Ingresa los siguientes datos para iniciar sesión" << endl;

    // Solicitar datos al usuario
    email = solicitarDato(" || Correo > ");
    password = solicitarDato(" || Contraseña > ");

    User_Logued = list_Users.search_LogIn(email, password);
    if( User_Logued == nullptr )
    {
        return nullptr;
    }
    else
    { 
        return User_Logued;
    }

}

bool User_Controller::deleteUser()
{
    bool res = list_Users.remove_User(User_Logued);
    if(res)
    {
        cout << " >> La cuenta se ha borrado satisfactoriamente\n" << endl;
        return res;
    }
    else
    {
        cout << " >> Error al intentar eliminar tu cuenta\n" << endl;
        return res;
    }
}
