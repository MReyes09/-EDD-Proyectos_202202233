#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../../models/publicacion.h"

using namespace std;

struct NodeC {
    Publicacion* data;          // Dato almacenado en el nodo
    NodeC* next;        // Puntero al siguiente nodo
    NodeC* prev;        // Puntero al nodo anterior

    // Constructor del nodo
    NodeC(Publicacion* value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyCircular{
private:
    NodeC* head;         // Puntero al primer nodo
    NodeC* tail;         // Puntero al último nodo
public:

    DoublyCircular() {
        head = nullptr;
        tail = nullptr;
    }

    void append(Publicacion* value) {
        NodeC* newNode = new NodeC(value);

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            head->next = head;
            head->prev = head;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
    }

    bool search(Publicacion* value){
        if (head == nullptr) return false;

        NodeC* temp = head;
        do {
            if (temp->data == value) return true;
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    void remove(Publicacion* value){
        if (head == nullptr) return;

        NodeC* temp = head;
        do {
            if (temp->data == value) {
                if (temp == head) {
                    head = head->next;
                    tail->next = head;
                    head->prev = tail;
                } else if (temp == tail) {
                    tail = tail->prev;
                    head->prev = tail;
                    tail->next = head;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }

    void print() {
        
        if (head == nullptr) {
            cout << " >> No hay Publicaciones disponibles!!!" << endl;
            return;
        }

        NodeC* temp = head;
        int opcion = 0;
        do {
            system("cls");  // Limpia la pantalla, en sistemas Unix usa system("clear")

            cout << " Publicacion hecha por: " + temp->data->email << endl;
            cout << " Fecha: " + temp->data->fecha << "  Hora: " + temp->data->hora << endl;
            cout << " Contenido:\n " + temp->data->contenido << endl;

            cout << "\n ************************************ " << endl;
            cout << " || Opciones" << endl;
            cout << " || " << endl;
            cout << " || 1. Avanzar a la siguiente publicación" << endl;
            cout << " || 2. Retroceder a la publicación anterior" << endl;
            cout << " || 3. Salir" << endl;
            cout << " || " << endl;
            cout << " || Ingrese el número > ";
            cin >> opcion;

            system("cls");  // Limpia la pantalla después de seleccionar una opción
            
            switch (opcion) {
                case 1: // Avanzar a la siguiente publicación
                    temp = temp->next;
                    break;

                case 2: // Retroceder a la publicación anterior
                    temp = temp->prev;
                    break;

                case 3: // Salir
                    return;

                default:
                    cout << " >> Opción no válida. Inténtelo de nuevo." << endl;
                    cin.ignore(); // Espera a que el usuario presione Enter
                    break;
            }

        } while (opcion != 3);

    }

    void graph() {
        ofstream file("graph.dot");
        file << "digraph G {" << endl;
        file << "rankdir=LR;" << endl; // Horizontal
        file << "node [shape=record];" << endl;

        NodeC* current = head;
        int id = 0;
        if (head != nullptr) {
            do {
                file << "node" << id << " [label=\"{" << current->data << "}\"];" << endl;
                if (current->next != head) {
                    file << "node" << id << " -> node" << (id + 1) << " [dir=both];" << endl;
                }
                current = current->next;
                id++;
            } while (current != head);
            // Conexión del último nodo con el primero
            file << "node" << (id - 1) << " -> node0 [dir=both];" << endl;
        }

        file << "}" << endl;
        file.close();

        // Renderizar usando Graphviz
        string command = "dot -Tpng graph.dot -o graph.png";
        system(command.c_str());
    }

    ~DoublyCircular() {
        NodeC* current = head;
        NodeC* next;
        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != head);
    }
};

#endif