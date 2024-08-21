#include <iostream>
#include <locale>
#include <windows.h>
#include <limits>
#include "../controller/user_Controller.cpp"
#include "../models/user.h"

using namespace std;

class Menu
{
private:

    int opcion;
    User_Controller* userControl;
    User* user_LogIn;

public:

    Menu()
    {
        userControl = new User_Controller();
        opcion = 0;
    }

    void menu_Principal(){
        SetConsoleOutputCP(CP_UTF8);
        system("cls");
        do
        {
            cout << " ************************************ " << endl;
			cout << " || Bienvenido a Social Structure" << endl;
			cout << " || " << endl;
			cout << " || 1. Iniciar Sesión" << endl;
            cout << " || 2. Registrarse" << endl;
            cout << " || 3. Información" << endl;
            cout << " || 4. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");

            switch(opcion)
            {
            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                user_LogIn = userControl->logIn();
                if(user_LogIn != nullptr)
                {
                    if( user_LogIn->getRol() == "Admin" )
                    {
                        menu_Administrador();
                    }
                    else
                    {
                       menu_Usuario();
                    }
                }
                break;
            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userControl->sigIn();
                break;
            case 3:
                cout << "\n || Matthew Emmanuel Reyes Melgar\n ||202202233\n ||Lab Estructura de datos\n ||Sección \"C\"\n" << endl;                
                break;
            case 4:
                cout << ">> Adiós" << endl;
                break;
            default:
                system("cls");
                cout << ">> Opción no valida" << endl;
            }

        }while(opcion != 4);
    }

    void menu_Usuario(){

        system("cls");
        do
        {
            cout << " ************************************ " << endl;
			cout << " || Bienvenido " << user_LogIn->getName() << endl;
			cout << " || " << endl;
			cout << " || 1. Perfil" << endl;
            cout << " || 2. Solicitudes" << endl;
            cout << " || 3. Publicaciones" << endl;
            cout << " || 4. Reportes de Usuario" << endl;
            cout << " || 5. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");
            bool res = false;
            switch (opcion)
            {
            case 1:
                res = Menu_Perfil();
                if( res == 1){ return; }
                break;
            
            case 2:
                Menu_Solicitudes();
                break;
            
            case 3:
                menu_Post();
                break;
            
            case 4:
                reportes_User();
                break;
            
            case 5:
                
                break;
            
            default:
                system("cls");
                cout << ">> Opción no valida" << endl;
                break;
            }

        }while(opcion != 5);

    }

    int Menu_Perfil(){
        system("cls");

        do
        {
            cout << " ************************************ " << endl;
			cout << " || Opciones de Perfil" << endl;
			cout << " || " << endl;
			cout << " || 1. Ver Perfil" << endl;
            cout << " || 2. Eliminar Cuenta" << endl;
            cout << " || 3. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");
            bool res = false;
            switch (opcion)
            {
            case 1:
                system("cls");
                cout << " ************************************" << endl;
                cout << " || Perfil de Usuario" << endl;
                cout << " ************************************" << endl;
                cout << " || ID: " << user_LogIn->getIdUser() << endl;
                cout << " || Nombre: " << user_LogIn->getName() << endl;
                cout << " || Apellido: " << user_LogIn->getLastname() << endl;
                cout << " || Email: " << user_LogIn->getEmail() << endl;
                cout << " || Fecha de Nacimiento: " << user_LogIn->getBirthdate() << endl;
                cout << " || Rol: " << user_LogIn->getRol() << endl;
                cout << " ************************************" << endl;
                cout << " Presiona Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter
                cin.get(); // Lee la tecla Enter
                system("cls");
                break;
            
            case 2:
                
                res = userControl->deleteUser();
                if(res){return 1;}
                break;
            
            case 3:
                
                break;
            
            default:
                system("cls");
                cout << ">> Opción no valida" << endl;
                break;
            }

        }while(opcion != 3);
        return 0;
    }

    void Menu_Solicitudes(){
        do
        {
            system("cls");
            cout << " ************************************ " << endl;
			cout << " || Opciones de Solicitud" << endl;
			cout << " || " << endl;
			cout << " || 1. Ver Solicitudes De Amistad" << endl;
            cout << " || 2. Enviar Solicitudes De Amistad" << endl;
            cout << " || 3. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter

            switch (opcion)
            {
            case 1:
                menu_Aceptar_Solicitudes();
                opcion = 0;
                break;
            
            case 2:
                
                userControl->solicitud_Amistad();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter
                break;

            case 3:
                break;

            default:
                break;
            }
        }while(opcion != 3);

    }

    void menu_Administrador(){
        system("cls");
        do
        {
            cout << " ************************************ " << endl;
			cout << " || Bienvenido " << user_LogIn->getName() << endl;
			cout << " || " << endl;
			cout << " || 1. Carga De Usuarios" << endl;
            cout << " || 2. Carga De Relaciones" << endl;
            cout << " || 3. Carga De Publicaciones" << endl;
            cout << " || 4. Gestionar usuarios" << endl;
            cout << " || 5. Reportes" << endl;
            cout << " || 6. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");
            bool res = false;
            switch (opcion)
            {
            case 1:
                userControl->carga_Usuarios();
                break;
            
            case 2:
                userControl->carga_Solicitudes();
                break;
            
            case 3:
                userControl->carga_Post();
                break;
            
            case 4:
                userControl->gestionar_Usuarios(user_LogIn);
                break;
            
            case 5:
                reportes_Admin();
                break;
                
            case 6:
                
                break;
            
            default:
                system("cls");
                cout << ">> Opción no valida" << endl;
                break;
            }

        }while(opcion != 6);
    }

    void menu_Aceptar_Solicitudes(){
        
        system("cls");
        do
        {
            if( user_LogIn->getListSol().head == nullptr ){
                cout << " *******************************************" << endl;
                cout << " || No tienes solicitudes pendientes por aceptar" << endl;
                user_LogIn->getListAmigos().print(2, user_LogIn->getEmail());
                cout << " || Presiona Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter
                cin.get(); // Lee la tecla Enter
                break;
            }

            cout << " *******************************************" << endl;

            user_LogIn->getListSol().print(1);

            cout << "\n || Deseas aceptar la solicitud de: " << user_LogIn->getListSol().head->solicitud->getCorreoEmisor() << endl;
            cout << " || 1. Aceptar" << endl;
            cout << " || 2. Rechazar" << endl;
            cout << " || 3. Salir" << endl;
            cout << " Tu respuesta >> ";
            cin >> opcion;            
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter

            switch (opcion)
            {
            case 1:
                userControl->solicitudes(1);
                cout << " || Presiona Enter para continuar...";
                cin.get(); // Lee la tecla Enter
                system("cls");
                opcion = 0;
                break;
            case 2:
                userControl->solicitudes(0);                
                cout << " || Presiona Enter para continuar...";
                cin.get(); // Lee la tecla Enter
                system("cls");
                break;
            case 3:
                
                break;

            default:
                cout << " >> Tu respuesta no es valida" << endl;
                break;
            }
        }while(opcion != 3);
    }

    void menu_Post(){
        system("cls");
        do
        {
            cout << " ************************************ " << endl;
			cout << " || Opciones de publicacion"<< endl;
			cout << " || " << endl;
			cout << " || 1. Ver Todas" << endl;
            cout << " || 2. Crear " << endl;
            cout << " || 3. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");
            bool res = false;
            switch (opcion)
            {
            case 1:
                userControl->mostrar_Post();
                break;
            
            case 2:
                userControl->add_Post();
                break;
            
            case 3:
                
                break;
            
            default:
                system("cls");
                cout << ">> Opción no valida" << endl;
                break;
            }

        }while(opcion != 4);
    }

    void reportes_Admin(){
        system("cls");
        do
        {
            cout << " ************************************ " << endl;
			cout << " || Escoge el reporte a generar"<< endl;
			cout << " || " << endl;
			cout << " || 1. Grafico lista de usuarios" << endl;
            cout << " || 2. Grafico matriz dispersa" << endl;
            cout << " || 3. Grafico lista publicaciones" << endl;
            cout << " || 4. Top 5 usuarios con más publicaciones" << endl;
            cout << " || 5. Top 5 usuarios con menos amigos" << endl;
            cout << " || 6. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");
            bool res = false;
            switch (opcion)
            {
            case 1:
                userControl->report_Usuarios();
                break;
            
            case 2:
                userControl->report_Matriz();
                break;
            
            case 3:
                userControl->report_Posts();
                break;
            
            case 4:
                userControl->top5_Usuarios_Posts();
                break;
            
            case 5:
                userControl->top5_Mas_Amigos();
                break;
                
            case 6:
                
                break;
            
            default:
                system("cls");
                cout << ">> Opción no valida" << endl;
                break;
            }

        }while(opcion != 6);
    }

    void reportes_User(){
        system("cls");
        do
        {
            cout << " ************************************ " << endl;
			cout << " || Escoge el reporte a generar"<< endl;
			cout << " || " << endl;
			cout << " || 1. Grafico solicitudes y pila de solicitudes" << endl;
            cout << " || 2. Grafico matriz dispersa" << endl;
            cout << " || 3. Grafico lista circular de publicaciones" << endl;
            cout << " || 4. Mostrar amigos" << endl;
            cout << " || 5. Salir" << endl;
			cout << " || " << endl;
			cout << " || Ingrese el numero > ";
            cin >> opcion;
            
            system("cls");
            bool res = false;
            switch (opcion)
            {
            case 1:
                userControl->reporte_Sol();
                break;
            
            case 2:
                userControl->report_Matriz();
                break;
            
            case 3:
                userControl->report_Posts();
                break;
            
            case 4:
                userControl->top5_Usuarios_Posts();
                break;
            
            case 5:
                break;
            default:
                system("cls");
                cout << ">> Opción no valida" << endl;
                break;
            }

        }while(opcion != 5);
    }

};