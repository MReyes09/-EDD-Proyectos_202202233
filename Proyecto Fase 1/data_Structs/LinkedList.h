#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.cpp"
#include "../models/user.h"

using namespace std;

class LinkedList
{
private:

    Node* head;

public:

    LinkedList();
    ~LinkedList();
    void append(User* value);
    void print();
    User* search_LogIn(string email, string password);
    bool remove_User(User* user);

};

#endif 