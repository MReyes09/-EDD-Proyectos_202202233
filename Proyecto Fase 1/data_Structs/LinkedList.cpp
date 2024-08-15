#include <iostream>
#include "LinkedList.h"
#include "../models/user.h"

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

User* LinkedList::search_By_Id(int id){

    Node *temp = head;

    while ( temp != nullptr )
    {
        if ( temp->user->getIdUser() == id ){
            return temp->user;
        }
        temp = temp->next;
    }

    cout << "\n >> El id que has compartido no corresponde a ningún usuario\n" << endl;
    return nullptr;

}