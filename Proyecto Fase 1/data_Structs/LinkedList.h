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
    
    void append(User* value);
    void print();
};

#endif 