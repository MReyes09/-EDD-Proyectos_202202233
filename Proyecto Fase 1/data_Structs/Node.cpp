#include "../models/user.h"

struct Node
{
    User* user;
    Node* next;

    Node(User* user)
    {
        this->user = user;
        next = nullptr;
    }
};
