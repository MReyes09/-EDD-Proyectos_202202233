#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include "../models/user.h"
#include "LinkedList_Sol.h"

using namespace std;

class LinkedList
{
private:

    Node* head;

public:

    LinkedList();
    ~LinkedList();
    void append(User* value);
    void print(int id_UserLogin);
    User* search_LogIn(string email, string password);
    bool remove_User(User* user);
    User* search_By_Id(int id, string correo = "");
    void print_Desconocidos(int id_User, LinkedList_Sol& lista_Env, LinkedList_Sol& lista_Sol, LinkedList_Sol& amigos);
    void remove_All_Solicitudes(User* user);
    void generateDot();
    void renderGraphviz();
    void sortListByPosts();
    void printList(int op);
    void sortListByFriends();

};

#endif 