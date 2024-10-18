#ifndef LINKEDLISTPOST_H
#define LINKEDLISTPOST_H

#include "NodePost.h"
#include "publicacion.h"

class LinkedListPost
{
public:
    int size;
    NodePost* head;
    LinkedListPost();
    bool append(Publicacion* value);
    void print();
    ~LinkedListPost();
    void ordenList();
};

#endif // LINKEDLISTPOST_H
