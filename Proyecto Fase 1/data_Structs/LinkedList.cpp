#include <iostream>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
}

void LinkedList::append(User* value)
{
    Node* newNode = new Node(value);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->user->getEmail() == value->getEmail())
            {
                cout << "\n >> El correo electrónico " + value->getEmail() + " ¡Ya existe!\n" << endl;
                delete newNode;
                cout << " Presiona Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter
                cin.get(); // Lee la tecla Enter
                return; // Salir de la función para no añadir el nodo duplicado
            }
            if (temp->next == nullptr) // Verifica si es el último nodo
            {
                temp->next = newNode;
                cout << "\n >> Tu cuenta fue creada con éxito\n" << endl;
                return;
            }
            temp = temp->next;
        }
    }
}

void LinkedList::print(int id_UserLogin)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if(temp->user->getIdUser() == id_UserLogin){
            temp = temp->next;
            continue;
        }
        int id = temp->user->getIdUser();
        string correo = temp->user->getEmail();
        string mensaje = " " + to_string(id) + ") " + correo;
        cout << mensaje << endl;
        temp = temp->next;
    }
}

LinkedList::~LinkedList()
{
    Node* current = head;
    while(current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

User* LinkedList::search_LogIn(string email, string password)
{
    Node *temp = head;
    
    while (temp != nullptr)
    {
        if ( temp->user->getEmail() == email && temp->user->getPassword() == password )
        {
            cout << "\n >> Se ha iniciado sesión correctamente\n" << endl;
            return temp->user;
        }
        temp = temp->next;
    }
    cout << "\n >> El correo o la contraseña no corresponden a ningún usuario\n" << endl;
    return nullptr;
}

bool LinkedList::remove_User(User* user)
{
    if (head == nullptr)
        return false;

    if (head->user == user)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node *current = head;
    Node *previous = nullptr;

    while (current != nullptr && current->user != user)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
        return false;

    previous->next = current->next;
    delete current;
    return true;
}

User* LinkedList::search_By_Id(int id, string correo){

    Node *temp = head;

    while ( temp != nullptr )
    {
        if ( temp->user->getIdUser() == id || temp->user->getEmail() == correo){
            return temp->user;
        }
        temp = temp->next;
    }

    cout << "\n >> El id que has compartido no corresponde a ningún usuario\n" << endl;
    return nullptr;

}

void LinkedList::print_Desconocidos(int id_User, LinkedList_Sol& list_Env, LinkedList_Sol& list_Sol){
    Node *temp = head;

    while (temp != nullptr)
    {
        // Si el usuario actual es el que ha iniciado sesión, lo omitimos
        if (temp->user->getIdUser() == id_User){
            temp = temp->next;
            continue;
        }

        bool solicitud_enviada = false;
        bool solicitud_recibida = false;

        // Revisar si se ha enviado una solicitud a este usuario
        Node_Sol *temp2 = list_Env.head;
        while(temp2 != nullptr){
            if (temp2->solicitud->getCorreoReceptor() == temp->user->getEmail()) {
                solicitud_enviada = true;
                break;
            }
            temp2 = temp2->next;
        }

        // Revisar si se ha recibido una solicitud de este usuario
        Node_Sol *temp3 = list_Sol.head;
        while(temp3 != nullptr){
            if (temp3->solicitud->getCorreoEmisor() == temp->user->getEmail()) {
                solicitud_recibida = true;
                break;
            }
            temp3 = temp3->next;
        }

        // Si no se ha enviado ni recibido una solicitud, imprimir el usuario
        if (!solicitud_enviada && !solicitud_recibida) {
            int id = temp->user->getIdUser();
            string correo = temp->user->getEmail();
            string mensaje = " " + to_string(id) + ") " + correo;
            cout << mensaje << endl;
        }

        temp = temp->next;
    }
}


