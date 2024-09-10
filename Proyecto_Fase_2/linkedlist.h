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
    void append(User* value);
    User* search_LogIn(QString email, QString password);
    int size_List();
    User* at(int index);
    void print();

};

#endif // LINKEDLIST_H
