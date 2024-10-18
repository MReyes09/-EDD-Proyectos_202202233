#ifndef NODE_H
#define NODE_H

//user.cpp
#include "user.h"

struct Node
{
    User* user;
    Node* next;

    // Constructor
    Node(User* user)
    {
        this->user = user;
        next = nullptr;
    }
};

#endif // NODE_H
