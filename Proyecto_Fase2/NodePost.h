#ifndef NODEPOST_H
#define NODEPOST_H

#include "publicacion.h"

struct NodePost
{
    Publicacion* post;
    NodePost* next;

    // Constructor
    NodePost(Publicacion* post)
    {
        this->post = post;
        next = nullptr;
    }
};

#endif // NODEPOST_H
