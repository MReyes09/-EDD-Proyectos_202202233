#ifndef LINKEDLISTPOST_H
#define LINKEDLISTPOST_H

#include "NodePost.h"
#include "publicacion.h"

class LinkedListPost
{
public:
    NodePost* head;
    LinkedListPost();
    bool append(Publicacion* value);
    void print();
    ~LinkedListPost();
};

#endif // LINKEDLISTPOST_H
