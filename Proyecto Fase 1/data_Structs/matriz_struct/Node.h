#ifndef NODE_H
#define NODE_H

#include "../../models/solicitud.h"

struct Node
{
    int i = -1, j = -1;
    Solicitud* sol = nullptr;
    Node* up = nullptr;
    Node* down = nullptr;
    Node* right = nullptr;
    Node* left = nullptr;

    Node(int i = -1, int j = -1, Solicitud* sol = nullptr) : i(i), j(j), sol(sol) {}
};

#endif // NODE_H
