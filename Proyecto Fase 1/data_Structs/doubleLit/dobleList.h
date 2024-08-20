#ifndef DOBLELIST_H
#define DOBLELIST_H

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../../models/publicacion.h"
#include "../circularList/CircularList.h"
#include "../LinkedList_Sol.h"

using namespace std;

struct NodeD{
    Publicacion* data;
    NodeD* next;
    NodeD* prev;

    NodeD(Publicacion* value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList{
private:
    NodeD* head;
    NodeD* tail;
public:
    DoublyLinkedList(){
        head = nullptr;
        tail = nullptr;
    }

    void append(Publicacion* value){
        NodeD* newNode = new NodeD(value);
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void print(){
        NodeD* current = head;
        while(current != nullptr){
            cout << current->data->fecha << " <-> ";
            current = current->next;
        }
        cout << "fin" <<endl;
    }

    void remove(Publicacion* value){
        NodeD* current = head;

        while (current != nullptr && current->data != value){
            current = current->next;
        }

        if(current == nullptr){
            cout << "No se encontro el valor a eliminar" << endl;
            return;
        }

        if(current->prev != nullptr){
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if(current->next != nullptr){
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        delete current;
    }

    bool search(Publicacion* value){
        NodeD* current = head;
        while(current != nullptr){
            if(current->data == value){
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void graph(){
        ofstream file("graph.dot");
        file << "digraph G {" << endl;
        file << "rankdir=LR;" << endl;
        file << "node [shape=record];" << endl;

        NodeD* current = head;
        int id = 0;
        while (current != nullptr) {
            file << "node" << id << " [label=\"{" << current->data << "}\"];" << endl;
            if (current->next != nullptr) {
                file << "node" << id << " -> node" << (id + 1) << " ;" << endl;
                file << "node" << (id + 1) << " -> node" << id << " ;" << endl;
            }
            current = current->next;
            id++;
        }

        file << "}" << endl;
        file.close();

        string command = "dot -Tpng graph.dot -o graph.png";
        system(command.c_str());
    }

    void extractPost(LinkedList_Sol& amigos, DoublyCircular* posts, string user_email){
        
        NodeD* current = head;

        if (!current) {
            cout << "No hay publicaciones disponibles." << endl;
            return;
        }

        do {

            string email = current->data->email;
            if( email == user_email || amigos.search(email, user_email)){
                posts->append(current->data);
            }

            current = current->next;

        }while(current != nullptr);

    }

    ~DoublyLinkedList(){
        NodeD* current = head;
        while(current != nullptr){
            NodeD* next = current->next;
            delete current;
            current = next;
        }
    }
};

#endif