#include "linkedlistpost.h"

#include <QMessageBox>
#include <QDebug>

LinkedListPost::LinkedListPost()
{
    head = nullptr;
    size = 0;
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
        size++;
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
        size++;
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

void LinkedListPost::ordenList()
{
    if (head == nullptr) {
        // La lista está vacía, no hay nada que ordenar
        return;
    }

    bool swapped;
    do {
        swapped = false;
        NodePost *current = head;

        while (current->next != nullptr) {
            // Comparamos la cantidad de comentarios de las publicaciones
            if (current->post->No_Comentarios < current->next->post->No_Comentarios) {
                // Intercambiamos las publicaciones
                Publicacion* temp = current->post;
                current->post = current->next->post;
                current->next->post = temp;
                swapped = true; // Indicamos que se realizó un intercambio
            }
            current = current->next;
        }
    } while (swapped); // Repetir hasta que no haya intercambios
}
