#ifndef NODE_SOL_H
#define NODE_SOL_H

#include "Solicitud.h"

struct Node_Sol
{
    Solicitud* solicitud;
    Node_Sol* next;

    // Constructor
    Node_Sol(Solicitud* solicitud)
    {
        this->solicitud = solicitud;
        next = nullptr;
    }
};

#endif // NODE_H
