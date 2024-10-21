#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

//Archivos del proyecto
#include "user.h"
#include "linkedlist.h"
#include "Matriz.h"
#include "linkedlistpost.h"
#include "Solicitud.h"
#include "dobleList.h"
#include "Abb.h"
#include "avl.h"
#include "ListOfList.h"

class User_Controller
{
private:
    static User_Controller* instance; // Instancia única
    int id_User;

    AVL* list_No_Amigos;
    AVL list_Users;
    // Constructor privado para que no pueda ser instanciado directamente
    User_Controller();
    DoublyLinkedList posts;
    ListOfList listOflist;

public:
    // Método estático para obtener la instancia única

    ABB* arbolBBusqueda;
    User* User_Logued;
    LinkedListPost *allPosts;
    static User_Controller* getInstance();

    // Métodos relacionados con el manejo de usuarios
    bool sigIn(QString name_, QString lastname_, QString email_, QString password_, QString birthdate_, QString rol_);
    void admin_add();
    User* logIn(QString gmai, QString password);
    User* addUserTable(int index);
    void report_AVL();
    int sizeList();
    AVL& getListaUsers();
    bool carga_Usuarios(QString path);
    bool carga_Solicitudes(QString path);
    void add_ListOfList(int i, int j);

    bool carga_Post(QString path);
    void arbolAbb();
    void allList();
    void report_Posts();
    LinkedListPost* inordenPosts(int limit);
    LinkedListPost* posordenPosts(int limit);
    LinkedListPost* preordenPosts(int limit);
    void searchDateAbb(QDate date);
    void addPost(QString contenido, QString path = "");
    User* searchUser(QString correo);
    void avl_inorden(LinkedList* listOrden);
    void avl_posorden(LinkedList* listOrden);
    void avl_preorden(LinkedList* listOrden);

    AVL* getListaNoAmigos();
    void listDesconocidos();
    void solicitudes(int opcion);
    void cancelarSolicitud(QString email_Sol);
    void solicitud_Amistad(QString email);

    // LIST OF LIST
    void ListOfListGraph();
    void ListOfListGraphAsAdjacenty();

    //Actualizar usuario
    void ActualizarUser(QString name, QString lastname, QString birthDay, QString pass);
};

#endif // USER_CONTROLLER_H
