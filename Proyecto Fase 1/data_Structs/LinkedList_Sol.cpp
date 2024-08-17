#include <iostream>
#include "LinkedList_Sol.h"

using namespace std;

LinkedList_Sol::LinkedList_Sol()
{
    head = nullptr;
}

bool LinkedList_Sol::append(Solicitud* value)
{   
    if (value->getCorreoEmisor() == value->getCorreoReceptor()) {
        cout << " >> Operacion invalida " << endl;
        return false;
    }

    Node_Sol* newNode_Sol = new Node_Sol(value);
    if (head == nullptr) {
        head = newNode_Sol;
        cout << "\n >> La solicitud ha sido enviada con exito!" << endl;
        return true;
    }
    else {
        Node_Sol* temp = head;
        while (temp->next != nullptr) {
            if (temp->solicitud->getCorreoReceptor() == value->getCorreoReceptor()) {
                cout << " >> Operacion invalida, solicitud anteriormente enviada" << endl;
                delete newNode_Sol;
                return false;
            }
            temp = temp->next;
        }
        // Verifica la última posición
        if (temp->solicitud->getCorreoReceptor() == value->getCorreoReceptor()) {
            cout << " >> Operacion invalida, solicitud anteriormente enviada" << endl;
            delete newNode_Sol;
            return false;
        }
        temp->next = newNode_Sol;
        cout << "\n >> La solicitud ha sido enviada con exito!" << endl;
        return true;
    }
}

void LinkedList_Sol::print(int opcion)
{
    Node_Sol *temp = head;
    int id = 0;
    if( opcion == 0 ){
        cout << "\n La lista de tus solicitudes son: " << endl;
    }else{
        cout << "\n || Estas personas quieren ser tus amigos: " << endl;
    }
    
    while (temp != nullptr)
    {
        string correo = "";
        if( opcion == 0 ){
            correo = temp->solicitud->getCorreoReceptor();
        }else{
            correo = temp->solicitud->getCorreoEmisor();
        }
        string mensaje = "  " + to_string(id) + ") " + correo;
        cout << mensaje << endl;
        temp = temp->next;
        id++;
    }
    if (id == 0) {
        cout << "No tienes solicitudes pendientes." << endl;
    }
}

LinkedList_Sol::~LinkedList_Sol()
{
    Node_Sol* current = head;
    while(current != nullptr)
    {
        Node_Sol* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList_Sol::push(Solicitud* value){
    Node_Sol *newNode = new Node_Sol(value);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

bool LinkedList_Sol::remove(Solicitud* value)
    {
        if (head == nullptr)
            return false;

        if (head->solicitud == value)
        {
            Node_Sol *temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        Node_Sol *current = head;
        Node_Sol *previous = nullptr;

        while (current != nullptr && current->solicitud != value)
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

