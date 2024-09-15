#ifndef DOBLELIST_H
#define DOBLELIST_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

#include <string>

#include "publicacion.h"
#include "linkedlist_sol.h"
#include "Abb.h"

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
            qDebug() << current->data->fecha;
            current = current->next;
        }
        qDebug("fin");
    }

    void remove(QString email){
        NodeD* current = head;

        while (current != nullptr && current->data->email != email){
            current = current->next;
        }

        if(current == nullptr){
            cout << "No se encontro el valor a eliminar o no hay publicaciones" << endl;
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

    void graph() {
        // Define las rutas absolutas para el archivo DOT y la imagen PNG
        string dotFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/List_Posts.dot";
        string pngFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/posts.png";

        // Crear el archivo DOT
        ofstream file(dotFilePath);
        file << "digraph G {" << endl;
        file << "rankdir=LR;" << endl;
        file << "node [shape=record];" << endl;

        NodeD* current = head;
        int id = 0;
        while (current != nullptr) {
            QString lab = current->data->email + "\\n" + current->data->contenido;
            file << "node" << id << " [label=\"{" << lab.toStdString() << "}\"];" << endl;
            if (current->next != nullptr) {
                file << "node" << id << " -> node" << (id + 1) << " ;" << endl;
                file << "node" << (id + 1) << " -> node" << id << " ;" << endl;
            }
            current = current->next;
            id++;
        }

        file << "}" << endl;
        file.close();
    }

    void generateDot(){
        // Define las rutas absolutas para el archivo DOT y la imagen PNG
        QString dotFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/List_Posts.dot";
        QString pngFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/posts.png";
        // Redirigir la salida de error a un archivo para ver los errores de Graphviz
        QString command = "dot";
        QStringList arguments;
        arguments << "-Tpng" << dotFilePath << "-o" << pngFilePath;
        QProcess process;

        process.start(command, arguments);
        process.waitForFinished();  // Espera a que el proceso termine

        // Verifica el estado del proceso
        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            QMessageBox::information(nullptr, "Imagen Generada", "La imagen se generó exitosamente.");
        } else {
            QMessageBox::critical(nullptr, "Error", "No se pudo generar la imagen.");
            qDebug() << "Error:" << process.errorString();
        }
    }

    ABB* extractPost(LinkedList_Sol& amigos, QString user_email){

        NodeD* current = head;

        if (current == nullptr) {
            QMessageBox::information(nullptr, "Carga De Publicaciones", "¡No tienes publicaciones para ver ahora!");
            return nullptr;
        }
        ABB* arbolGenerado = new ABB();
        do {

            QString email = current->data->email;
            if( email == user_email || amigos.search(email, user_email)){
                arbolGenerado->insert(current->data->fecha);
            }

            current = current->next;

        }while(current != nullptr);

        return nullptr;
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
