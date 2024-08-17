#ifndef LINKEDLIST_SOL_H
#define LINKEDLIST_SOL_H

#include "Node_Sol.h"
#include "../models/solicitud.h"

using namespace std;

class LinkedList_Sol{

    public:

        Node_Sol* head;
        LinkedList_Sol();
        ~LinkedList_Sol();
        bool append(Solicitud* value);
        void print(int opcion);
        void push(Solicitud* value);
        bool remove(Solicitud* value);
};

#endif