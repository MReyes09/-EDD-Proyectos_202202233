#include "linkedlist.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QMessageBox>
#include <QString>

using namespace std;

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
                // Mostrar mensaje de advertencia
                QMessageBox::warning(nullptr, "Error", "El correo electrónico " + value->getEmail() + " ¡Ya existe!");
                delete newNode;
                return;
            }
            if (temp->next == nullptr) // Verifica si es el último nodo
            {
                temp->next = newNode;
                // Mostrar mensaje de éxito
                QMessageBox::information(nullptr, "Éxito", "Tu cuenta fue creada con éxito");
                return;
            }
            temp = temp->next;
        }
    }
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
