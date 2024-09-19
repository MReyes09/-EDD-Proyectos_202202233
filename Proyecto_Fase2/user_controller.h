#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

//Archivos del proyecto
#include "user.h"
//#include "linkedlist.h"
#include "Matriz.h"
#include "linkedlistpost.h"
#include "Solicitud.h"
#include "dobleList.h"
#include "Abb.h"
#include "avl.h"

class User_Controller
{
private:
    static User_Controller* instance; // Instancia única
    int id_User;

    AVL* list_No_Amigos;
    AVL list_Users;
    ABB* arbolBBusqueda;
    // Constructor privado para que no pueda ser instanciado directamente
    User_Controller();
    DoublyLinkedList posts;
    Matriz m;

public:
    // Método estático para obtener la instancia única

    User* User_Logued;
    LinkedListPost *allPosts;
    static User_Controller* getInstance();

    // Métodos relacionados con el manejo de usuarios
    bool sigIn(QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_);
    void admin_add();
    User* logIn(QString gmai, QString password);
    User* addUserTable(int index);
    int sizeList();
    AVL& getListaUsers();
    bool carga_Usuarios(QString path);
    bool carga_Solicitudes(QString path);
    void add_Matriz(Solicitud* solicitud, int i, int j);

    bool carga_Post(QString path);
    void arbolAbb();
    void allList();
    void report_Posts();
    void searchDateAbb(QDate date);
    void addPost(QString contenido, QString path = "");
    User* searchUser(QString correo);

    AVL* getListaNoAmigos();
    void listDesconocidos();
};

#endif // USER_CONTROLLER_H
