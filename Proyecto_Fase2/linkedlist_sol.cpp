
#include "LinkedList_Sol.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QString>
#include <QMessageBox>

using namespace std;

LinkedList_Sol::LinkedList_Sol()
{
    head = nullptr;
}

bool LinkedList_Sol::append(Solicitud* value, QString email_User){
    if (value->getCorreoEmisor() == value->getCorreoReceptor()) {
        return false;
    }

    Node_Sol* newNode_Sol = new Node_Sol(value);
    if (head == nullptr) {
        head = newNode_Sol;
        return true;
    }
    else {
        Node_Sol* temp = head;
        while (temp->next != nullptr) {

            if( temp->solicitud->getCorreoEmisor() == email_User){ //Esta es una peticion en la que ya soy emisor

                if(temp->solicitud->getCorreoReceptor() == value->getCorreoReceptor()){

                    QString mensaje = "Solicitud enviada anteriormente (emisor): " + email_User + " (receptor)" + value->getCorreoReceptor();
                    QMessageBox::warning(nullptr, "Error de solicitud", mensaje);
                    delete newNode_Sol;
                    return false;
                }

            }else if( temp->solicitud->getCorreoReceptor() == email_User){ //Esta es una peticiion en la que ya soy receptor

                if ( temp->solicitud->getCorreoEmisor() == value->getCorreoEmisor() ){

                    QString mensaje = "Solicitud enviada anteriormente (emisor): " + email_User + " (receptor)" + value->getCorreoReceptor();
                    QMessageBox::warning(nullptr, "Error de solicitud", mensaje);
                    delete newNode_Sol;
                    return false;

                }

            }
            temp = temp->next;
        }
        // Verifica la última posición
        if( temp->solicitud->getCorreoEmisor() == email_User){ //Esta es una peticion en la que ya soy emisor

            if(temp->solicitud->getCorreoReceptor() == value->getCorreoReceptor()){

                QString mensaje = "Solicitud enviada anteriormente (emisor): " + email_User + " (receptor)" + value->getCorreoReceptor();
                QMessageBox::warning(nullptr, "Error de solicitud", mensaje);
                delete newNode_Sol;
                return false;
            }

        }else if( temp->solicitud->getCorreoReceptor() == email_User){ //Esta es una peticiion en la que ya soy receptor

            if ( temp->solicitud->getCorreoEmisor() == value->getCorreoEmisor() ){

                QString mensaje = "Solicitud enviada anteriormente (emisor): " + email_User + " (receptor)" + value->getCorreoReceptor();
                QMessageBox::warning(nullptr, "Error de solicitud", mensaje);
                delete newNode_Sol;
                return false;

            }

        }
        temp->next = newNode_Sol;
        return true;
    }
}

void LinkedList_Sol::print(int opcion, QString emailog)
{
    Node_Sol *temp = head;
    int id = 0;
    if( opcion == 0 ){
        cout << "\n || La lista de tus solicitudes son: " << endl;
    }else if(opcion == 1){
        cout << "\n || Estas personas quieren ser tus amigos: " << endl;
    }else{
        cout << "\n || Esta es tu lista de amigos: \n" << endl;
    }

    while (temp != nullptr)
    {
        QString correo = "";
        if( opcion == 0 ){
            correo = temp->solicitud->getCorreoReceptor();
        }else if( opcion == 1){
            correo = temp->solicitud->getCorreoEmisor();
        }else{
            if( emailog == temp->solicitud->getCorreoEmisor() ){
                correo = temp->solicitud->getCorreoReceptor();
            }else{
                correo = temp->solicitud->getCorreoEmisor();
            }

        }
        temp = temp->next;
        id++;
    }
    if (id == 0) {
        //cout << "No tienes solicitudes pendientes." << endl;
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

bool LinkedList_Sol::append_Friend(Solicitud* value){

    Node_Sol* newNode_Sol = new Node_Sol(value);
    if (head == nullptr) {
        head = newNode_Sol;
        return true;
    }
    else {
        Node_Sol* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode_Sol;
        return true;
    }

}

bool LinkedList_Sol::search(QString email, QString email_loged){

    Node_Sol *temp = head;

    while (temp != nullptr)
    {
        if (temp->solicitud->getCorreoEmisor() == email && temp->solicitud->getCorreoReceptor() == email_loged)
        {
            return true;
        }
        else if (temp->solicitud->getCorreoEmisor() == email_loged && temp->solicitud->getCorreoReceptor() == email){
            return true;
        }
        temp = temp->next;
    }
    return false;

}

// void LinkedList_Sol::generateDot(const QString& name)
// {
//     QString filename = "report/"+name +".dot";
//     ofstream file(filename);

//     if (file.is_open())
//     {
//         file << "digraph G {" << endl;
//         file << "node [shape=record];" << endl;
//         if(name == "pila"){
//             file << "rankdir=TB;" << endl;
//         }else{
//             file << "rankdir=LR;" << endl;
//         }

//         Node_Sol *current = head;
//         int id = 0;
//         while (current != nullptr)
//         {
//             cout << "id: "+ to_QString(id)<< endl;
//             QString body = "Emisor: " + current->solicitud->getCorreoEmisor() +
//                           "\\nReceptor: " + current->solicitud->getCorreoReceptor();
//             file << "node" << id << " [label=\"{" << body << "}\"];" << endl;
//             if (current->next != nullptr)
//             {
//                 file << "node" << id << " -> node" << (id + 1) << ";" << endl;
//             }
//             current = current->next;
//             id++;
//         }

//         file << "}" << endl;
//         file.close();
//     }
//     else
//     {
//         cout << "No se pudo abrir el archivo" << endl;
//     }
// }

// void LinkedList_Sol::renderGraphviz(const QString& name) {
//     QString dotFilename = "report/"+name +".dot";
//     QString imageFilename = "report/" + name + ".png";
//     QString command = "dot -Tpng " + dotFilename + " -o " + imageFilename;
//     system(command.c_str());
// }
