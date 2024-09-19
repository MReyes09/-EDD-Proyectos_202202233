#include "linkedlistpost.h"

#include <QMessageBox>
#include <QDebug>

LinkedListPost::LinkedListPost()
{
    head = nullptr;
}

LinkedListPost::~LinkedListPost()
{
    NodePost* current = head;
    while(current != nullptr)
    {
        NodePost* next = current->next;
        delete current;
        current = next;
    }
}

bool LinkedListPost::append(Publicacion* value)
{
    NodePost* newNode = new NodePost(value);
    if (head == nullptr)
    {
        head = newNode;
        return true;
    }
    else
    {
        NodePost* temp = head;
        // Recorre hasta el último nodo
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        // Enlaza el nuevo nodo al final de la lista
        temp->next = newNode;
        return true;
    }

    return false;
}

void LinkedListPost::print()
{
    qDebug("print");
    NodePost *temp = head;
    while (temp != nullptr)
    {
        QString message = "fecha: " + temp->post->fecha.toString("d/MM/yyyy");
        qDebug() << message;
        temp = temp->next;
    }
}

