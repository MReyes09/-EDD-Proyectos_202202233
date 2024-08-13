#include <iostream>
#include <locale>
#include <windows.h>
#include <limits>
#include "../controller/user_Controller.cpp"

using namespace std;

class Menu
{
private:
    int opcion;
    User_Controller* userControl;

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
                cout << " || Opción 1" << endl;
                break;
            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                userControl->sigIn();
                break;
            case 3:
                cout << "\n || Matthew Emmanuel Reyes Melgar\n ||202202233\n ||Lab Estructura de datos\n ||Sección \"C\"\n" << endl;
                cout << "Presiona enter para continuar";                
                break;
            case 4:
                cout << "-> Adiós" << endl;
                break;
            default:
                system("cls");
                cout << "|| Opción no valida" << endl;
            }

        }while(opcion != 4);
    }
};