#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//Dependencias
#include <QString>

//Archivos del proyecto
#include "Node.h"
#include "user.h"

class LinkedList
{
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList();
    bool append(User* value, int opcion = 0);
    User* search_LogIn(QString email, QString password);
    int size_List();
    User* at(int index);
    void print();

    //Funciones para solicitudes;
    User* search_By_Id(int id, QString correo = "");

};

#endif // LINKEDLIST_H
