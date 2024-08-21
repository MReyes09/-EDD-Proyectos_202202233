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
        void print(int opcion, string emailLog = "");
        void push(Solicitud* value);
        bool remove(Solicitud* value);
        bool append_Friend(Solicitud* value);
        bool search(string email, string email_Loged);
        void generateDot(const string& name);
        void renderGraphviz(const string& name);
};

#endif