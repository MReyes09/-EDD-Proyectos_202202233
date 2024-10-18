#include "linkedlist.h"
#include <iostream>
#include <cstdlib>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <string>

LinkedList::LinkedList() {
    head = nullptr;
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

bool LinkedList::append(User* value, int opcion)
{
    Node* newNode = new Node(value);
    if (head == nullptr)
    {
        head = newNode;
        return true;
    }
    else
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->user->getEmail() == value->getEmail())
            {
                // Mostrar mensaje de advertencia
                QMessageBox::warning(nullptr, "Error", "El correo electrónico " + value->getEmail() + " ¡Ya existe!");
                delete newNode;
                return false;
            }
            if (temp->next == nullptr) // Verifica si es el último nodo
            {
                temp->next = newNode;
                // Mostrar mensaje de éxito
                if ( opcion == 0 )
                {
                    //QMessageBox::information(nullptr, "Éxito", "Tu cuenta fue creada con éxito");
                }
                return true;
            }
            temp = temp->next;
        }
    }

    return false;
}

User* LinkedList::search_LogIn(QString email, QString password)
{
    Node *temp = head;

    while (temp != nullptr)
    {
        if ( temp->user->getEmail() == email && temp->user->getPassword() == password )
        {
            QMessageBox::information(nullptr, "Éxito", "Se ha iniciado sesión correctamente");
            return temp->user;
        }
        temp = temp->next;
    }
    QMessageBox::warning(nullptr, "Error", "El correo o la contraseña no corresponden a ningún usuario");
    return nullptr;
}

int LinkedList::size_List()
{
    int count = 0;
    Node* current = head;
    //qDebug() << head->user->getIdUser();
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Método para acceder a un usuario por índice
User* LinkedList::at(int index){

    int count = 0;
    Node* current = head;
    while (current) {
        if (count == index) {
            return current->user;
        }
        count++;
        current = current->next;
    }
    return nullptr;
}

void LinkedList::print()
{
    Node *temp = head;
    if( head == nullptr ){
        std::cout << "La lista esta vacia";
    }
    while (temp != nullptr)
    {
        int id = temp->user->getIdUser();
        string correo = temp->user->getEmail().toStdString();
        string mensaje = " || " + to_string(id) + ") " + correo;
        std::cout << correo + " " + mensaje;
        temp = temp->next;
    }

    QMessageBox::information(nullptr, "Éxito", "Estamos en el print!");
}

User* LinkedList::search_By_Id(int id, QString correo){

    Node *temp = head;

    while ( temp != nullptr )
    {
        if ( temp->user->getIdUser() == id || temp->user->getEmail() == correo){
            return temp->user;
        }
        temp = temp->next;
    }
    return nullptr;

}
