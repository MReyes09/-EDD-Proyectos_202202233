#include <iostream>
#include <locale>
#include <windows.h>
#include <fstream>
#include <limits>
#include "user_Controller.h"
#include "../models/user.h"
#include "../models/solicitud.h"
#include "../include/json.hpp"
#include "../data_Structs/matriz_struct/Matriz.h"

using json = nlohmann::json;
using namespace std;

User_Controller::User_Controller(){
    id_User = 0;
    admin_add();
    //Matriz matriz;
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
    //string name = "admin@gmail.com";
    //string password = "EDD2S2024";
    string name = "x";
    string password = "s";

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

void User_Controller::carga_Usuarios(){
    // Leer el archivo JSON
    string path = "data/usuarios.json";
    //cout << "Escribe la ruta del archivo\n ruta >> ";
    ifstream file(path);

    if (!file.is_open()) {
        cerr << " >> No se pudo abrir el archivo JSON" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    

    // Iterar sobre los elementos del JSON y crear objetos User
    for (auto& element : jsonData) {
        string name = element["nombres"];
        string lastname = element["apellidos"];
        string birthdate = element["fecha_De_Nacimiento"];
        string email = element["correo"];
        string password = element["contraseña"];
        string rol = "Usuario"; // Podrías agregar esto a tu JSON si es necesario

        User* newUser = new User(id_User, name, lastname, email, password, birthdate, rol);
        id_User++;
        list_Users.append(newUser);
    }
    system("cls");
    cout << "\n >> Los usuarios registrados en el sistema son:"<<endl;
    list_Users.print(User_Logued->getIdUser());
    cout << " La carga de usuarios en el sistema fue satisfactorio" << endl;
    cout << " Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter
    cin.get(); // Lee la tecla Enter
    system("cls");
}

void User_Controller::solicitud_Amistad() {

    cout << " *******************************************" << endl;
    cout << " Personas que quízas conozcas" << endl;

    list_Users.print_Desconocidos(User_Logued->getIdUser(), User_Logued->getListEnvios(), User_Logued->getListSol(), User_Logued->getListAmigos());
    cout << "\n Escribe el numero de a quien quieres enviar solicitud o -1 para salir" << endl;
    cout << " id >> ";

    int id;
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer
    if(id == -1){
        return;
    }
    User* user_Solicitud = list_Users.search_By_Id(id);

    if (user_Solicitud != nullptr) {
        Solicitud* newSolicitud = new Solicitud(User_Logued->getEmail(), user_Solicitud->getEmail());
        bool res = User_Logued->getListEnvios().append(newSolicitud);
        if( res ){            
            user_Solicitud->getListSol().push(newSolicitud);
            User_Logued->getListEnvios().print(0);            
            cout << " || Presiona Enter para continuar...";
        }        
    } else {
        cout << "Usuario no encontrado." << endl;
    }
}

void User_Controller::carga_Solicitudes(){
    // Leer el archivo JSON
    string path = "data/solicitudes.json";
    ifstream file(path);

    if (!file.is_open()) {
        cerr << " >> No se pudo abrir el archivo JSON" << endl;
        return;
    }

    json jsonData;
    file >> jsonData;


    // Iterar sobre los elementos del JSON y crear objetos User
    for (auto& element : jsonData) {
        string emisor = element["emisor"];
        string receptor = element["receptor"];
        string estado = element["estado"];

        if( estado == "PENDIENTE" ){
            User* userEM = list_Users.search_By_Id(-1, emisor);
            User* userRec = list_Users.search_By_Id(-1, receptor);

            if( userEM != nullptr && userRec != nullptr ){
                Solicitud* newSolicitud = new Solicitud(emisor, receptor);
                userEM->getListEnvios().append(newSolicitud);
                userRec->getListSol().push(newSolicitud);
            }else{
                if( userEM == nullptr ){
                    cout << " >> El usuario con correo: " + emisor << " no existe" << endl; 
                }else{
                    cout << " >> El usuario con correo: " + receptor << " no existe" << endl; 
                }
            }

        }else{
            //SI SON SOLICITUDES ACEPTADAS< DEBEMOS AGREGARLAS A LA MATRIZ DISPERSA!
            User* userEM = list_Users.search_By_Id(-1, emisor);
            User* userRec = list_Users.search_By_Id(-1, receptor);

            if( userEM != nullptr && userRec != nullptr ){
                Solicitud* newSolicitud = new Solicitud(emisor, receptor);
                userEM->getListAmigos().append(newSolicitud);
                userRec->getListAmigos().append(newSolicitud);
            }else{
                if( userEM == nullptr ){
                    cout << " >> El usuario con correo: " + emisor << " no existe" << endl; 
                }else{
                    cout << " >> El usuario con correo: " + receptor << " no existe" << endl; 
                }
            }
        }
    }
    system("cls");
    cout << " La carga de relaciones en el sistema fue satisfactorio" << endl;
    cout << " Presiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter
    cin.get(); // Lee la tecla Enter
    system("cls");

}

void User_Controller::solicitudes(int opcion){

    if( opcion == 1 ){ // Esta opcion es cuando el usuario acepta una solicitud
        
        Solicitud *solicitud = User_Logued->getListSol().head->solicitud;

        bool result = User_Logued->getListSol().remove(solicitud);
        if(result){
            cout << " >> Se acepto con exito la solicitud\n" <<endl;
        }else{
            cout << " >> A ocurrido un error, nunca se encontro la solicitud \n" << endl;
        }

        User* user_Emisor = list_Users.search_By_Id(-1, solicitud->getCorreoEmisor());
        result = user_Emisor->getListEnvios().remove(solicitud);

        if( !result ) {
            cout << " >> A ocurrido un error, nunca se encontro la solicitud\n" << endl;            
        }
        User_Logued->getListAmigos().append_Friend(solicitud);
        user_Emisor->getListAmigos().append_Friend(solicitud);
        User_Logued->getListAmigos().print(2, User_Logued->getEmail());
        int i = User_Logued->getIdUser();
        int j = user_Emisor->getIdUser();
        //add_Matriz(solicitud, i, j);

    }else{  // Esta opcion es cuando el usuario rechaza una solicitud

        Solicitud *solicitud = User_Logued->getListSol().head->solicitud;

        bool result = User_Logued->getListSol().remove(solicitud);
        if(result){
            cout << " >> Se rechazo con exito la solicitud \n" << endl;
        }else{
            cout << " >> A ocurrido un error, nunca se encontro la solicitud \n" << endl;
        }

        User* user_Emisor =  list_Users.search_By_Id(-1, solicitud->getCorreoEmisor());
        result = user_Emisor->getListEnvios().remove(solicitud);

        if( !result ) {
            cout << " >> A ocurrido un error, nunca se encontro la solicitud\n" << endl;            
        }

        delete solicitud;

    }

}
/*
void User_Controller::add_Matriz(Solicitud* solicitud, int i, int j){
    matriz.insert(i, j, solicitud);
}
*/