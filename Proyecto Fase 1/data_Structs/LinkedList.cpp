#include <iostream>
#include <fstream>
#include <cstdlib>
#include "LinkedList.h"
#include "../models/solicitud.h"

using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
}

void LinkedList::append(User* value)
{
    Node* newNode = new Node(value);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->user->getEmail() == value->getEmail())
            {
                cout << "\n >> El correo electrónico " + value->getEmail() + " ¡Ya existe!\n" << endl;
                delete newNode;
                cout << " Presiona Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Espera hasta que el usuario presione Enter
                cin.get(); // Lee la tecla Enter
                return; // Salir de la función para no añadir el nodo duplicado
            }
            if (temp->next == nullptr) // Verifica si es el último nodo
            {
                temp->next = newNode;
                cout << "\n >> Tu cuenta fue creada con éxito\n" << endl;
                return;
            }
            temp = temp->next;
        }
    }
}

void LinkedList::print(int id_UserLogin)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        if(temp->user->getIdUser() == id_UserLogin){
            temp = temp->next;
            continue;
        }
        int id = temp->user->getIdUser();
        string correo = temp->user->getEmail();
        string mensaje = " || " + to_string(id) + ") " + correo;
        cout << mensaje << endl;
        temp = temp->next;
    }
}

LinkedList::~LinkedList()
{
    Node* current = head;
    while(current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

User* LinkedList::search_LogIn(string email, string password)
{
    Node *temp = head;
    
    while (temp != nullptr)
    {
        if ( temp->user->getEmail() == email && temp->user->getPassword() == password )
        {
            cout << "\n >> Se ha iniciado sesión correctamente\n" << endl;
            return temp->user;
        }
        temp = temp->next;
    }
    cout << "\n >> El correo o la contraseña no corresponden a ningún usuario\n" << endl;
    return nullptr;
}

bool LinkedList::remove_User(User* user)
{
    if (head == nullptr)
        return false;

    if (head->user == user)
    {
        remove_All_Solicitudes(user);
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node *current = head;
    Node *previous = nullptr;

    while (current != nullptr && current->user != user)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
        return false;
        
    remove_All_Solicitudes(user);
    previous->next = current->next;
    delete current;
    return true;
}

User* LinkedList::search_By_Id(int id, string correo){

    Node *temp = head;

    while ( temp != nullptr )
    {
        if ( temp->user->getIdUser() == id || temp->user->getEmail() == correo){
            return temp->user;
        }
        temp = temp->next;
    }

    cout << "\n >> El id que has compartido no corresponde a ningún usuario\n" << endl;
    return nullptr;

}

void LinkedList::print_Desconocidos(int id_User, LinkedList_Sol& list_Env, LinkedList_Sol& list_Sol, LinkedList_Sol& amigos){
    Node *temp = head;

    while (temp != nullptr)
    {
        // Si el usuario actual es el que ha iniciado sesión, lo omitimos
        if (temp->user->getIdUser() == id_User){
            temp = temp->next;
            continue;
        }

        bool solicitud_enviada = false;
        bool solicitud_recibida = false;
        bool amigs = false;

        // Revisar si se ha enviado una solicitud a este usuario
        Node_Sol *temp2 = list_Env.head;
        while(temp2 != nullptr){
            if (temp2->solicitud->getCorreoReceptor() == temp->user->getEmail()) {
                solicitud_enviada = true;
                break;
            }
            temp2 = temp2->next;
        }

        // Revisar si se ha recibido una solicitud de este usuario
        Node_Sol *temp3 = list_Sol.head;
        while(temp3 != nullptr){
            if (temp3->solicitud->getCorreoEmisor() == temp->user->getEmail()) {
                solicitud_recibida = true;
                break;
            }
            temp3 = temp3->next;
        }

        Node_Sol *temp4 = amigos.head;
        while( temp4 != nullptr){
            if( temp4->solicitud->getCorreoEmisor() == temp->user->getEmail() || temp4->solicitud->getCorreoReceptor() == temp->user->getEmail() ){
                amigs = true;
                break;
            }
            temp4 = temp4->next;
        }

        // Si no se ha enviado ni recibido una solicitud, imprimir el usuario
        if (!solicitud_enviada && !solicitud_recibida && !amigs) {
            int id = temp->user->getIdUser();
            string correo = temp->user->getEmail();
            string mensaje = " || " + to_string(id) + ") " + correo;
            cout << mensaje << endl;
        }

        temp = temp->next;
    }
}

void LinkedList::remove_All_Solicitudes(User* user) {

    while (user->getListSol().head != nullptr) { // Verifico si la lista de solicitudes está vacía
        
        Solicitud* sol_Delete = user->getListSol().head->solicitud;
        
        // Borro de la lista de solicitudes pendientes del usuario
        user->getListSol().remove(sol_Delete); 
        
        // Obtengo el usuario emisor basado en el correo y elimino la solicitud
        User* user_Emisor = search_By_Id(-1, sol_Delete->getCorreoEmisor());
        user_Emisor->getListEnvios().remove(sol_Delete);
        delete sol_Delete;
    }
    cout << " || La Lista de Solicitudes fue vaciada con exito" << endl;

    while ( user->getListEnvios().head != nullptr ){// Verifico si la lista de mis envios de solicitud esta vacia

        Solicitud* envio_Delete = user->getListEnvios().head->solicitud;

        user->getListEnvios().remove(envio_Delete);

        //Obtengo el usuario receptor basado en el correo y elimino la solicitud
        User* user_Receptor = search_By_Id(-1, envio_Delete->getCorreoReceptor());
        user_Receptor->getListSol().remove(envio_Delete);
        delete envio_Delete;

    }

    cout << " || La Lista de Envios fue vaciada con exito" << endl;

    while ( user->getListAmigos().head != nullptr ){ //Verifico si la lista de mis amigos esta vacia

        Solicitud* amistad = user->getListAmigos().head->solicitud;
        user->getListAmigos().remove(amistad);

        //Obtengo el usuario del que soy amigo basado en el correo y elimino esa amistad
        if( amistad->getCorreoEmisor() == user->getEmail() ){//Si quien pidio la amistad fui yo

            User* user_Amigo = search_By_Id(-1, amistad->getCorreoReceptor());
            user_Amigo->getListAmigos().remove(amistad);
            user_Amigo->No_Fri -= 1;
            //delete amistad;

        }else{ //Si yo fui quien recibio y acepto esa lista de amistad (soy receptor)

            User* user_Amigo = search_By_Id(-1, amistad->getCorreoEmisor());
            user_Amigo->getListAmigos().remove(amistad);
            user_Amigo->No_Fri -= 1;
            //delete amistad;

        }

    }

    cout << " || La Lista de Amigos fue vaciada con exito" << endl;
}

void LinkedList::generateDot(){
    string filename = "report/list_Users.dot";
    ofstream file(filename);
    if (file.is_open())
    {
        file << "digraph G {" << endl;
        file << "node [shape=record];" << endl;
        file << "rankdir=LR;" << endl;

        Node *current = head;
        int id = 0;
        while (current != nullptr)
        {
            string body = current->user->getName() + "\\n"+ current->user->getEmail();

            file << "node" << id << " [label=\"{" << body << "}\"];" << endl;
            if (current->next != nullptr)
            {
                file << "node" << id << " -> node" << (id + 1) << ";" << endl;
            }
            current = current->next;
            id++;
        }

        file << "}" << endl;
        file.close();
    }
    else
    {
        cout << " || No se pudo abrir el archivo" << endl;
    }
}

void LinkedList::renderGraphviz(){
    string dotFilename = "report/list_Users.dot";
    string imageFilename = "report/list_Users.svg";

    // Generar el gráfico en formato SVG
    string command = "dot -Tsvg " + dotFilename + " -o " + imageFilename;
    system(command.c_str());
}

void LinkedList::sortListByPosts() {
    if (!head || !head->next) return; // No necesita ordenar si la lista está vacía o tiene un solo elemento

    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->user->No_Post < j->user->No_Post) {
                // Intercambiar los usuarios entre los nodos i y j
                User* temp = i->user;
                i->user = j->user;
                j->user = temp;
            }
        }
    }
}

// Método para imprimir la lista (para verificar la ordenación)
void LinkedList::printList(int op) {
    Node* current = head;
    int count = 5;
    if( op == 0){
        cout << " || Top 5 usuarios con mas publicaciones hechas" <<endl;
    }else{
        cout << " || Top 5 usuarios con mas amistades hechas" <<endl;
    }
    while (current != nullptr && count != 0) {
        if( op == 0 ){
            cout << " || " + to_string(count)+ ") " << current->user->getName() 
                << ", Publicaciones: " << current->user->No_Post << endl;
        }else{
            cout << " || " + to_string(count)+ ") " << current->user->getName() 
                << ", Amistades: " << current->user->No_Fri << endl;
        }
        
        current = current->next;
        count -=1;
    }
}

void LinkedList::sortListByFriends(){

    if( !head || !head->next) return;

    for(Node* i = head; i != nullptr; i = i->next){
        for(Node* j = i->next; j != nullptr; j= j->next){
            if( i->user->No_Fri > j->user->No_Fri ){
                User* temp = i->user;
                i->user = j->user;
                j->user = temp;
            }
        }
    }

}
