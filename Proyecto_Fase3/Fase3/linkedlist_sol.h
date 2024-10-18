#ifndef LINKEDLIST_SOL_H
#define LINKEDLIST_SOL_H

#include "Node_Sol.h"
#include "Solicitud.h"

#include <QString>

using namespace std;

class LinkedList_Sol{

public:
    int contador;
    Node_Sol* head;
    LinkedList_Sol();
    ~LinkedList_Sol();
    bool append(Solicitud* value, QString email_user);
    void print(int opcion, QString emailLog = "");
    void push(Solicitud* value);
    bool remove(Solicitud* value);
    bool append_Friend(Solicitud* value);
    bool search(QString email, QString email_Loged);
    Solicitud* search_Find(QString email, QString email_Logued);
    // void generateDot(const QString& name);
    // void renderGraphviz(const QString& name);
};

#endif
