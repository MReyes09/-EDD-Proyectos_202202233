#ifndef LISTOFLIST_H
#define LISTOFLIST_H

#include <iostream>
#include <memory>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>

#include "avl.h"
#include "user.h"

using namespace std;

class SubNodeLOL
{
public:
    int value;
    shared_ptr<SubNodeLOL> next = nullptr;

    SubNodeLOL(int value) : value(value) {}
};

class NodeLOL
{
public:
    int index;
    shared_ptr<NodeLOL> next = nullptr;
    shared_ptr<NodeLOL> prev = nullptr;
    shared_ptr<SubNodeLOL> list = nullptr;

    void append(int value)
    {
        shared_ptr<SubNodeLOL> newNodeLOL = make_shared<SubNodeLOL>(value);

        if (!list)
        {
            list = newNodeLOL;
        }
        else
        {
            shared_ptr<SubNodeLOL> temp = list;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNodeLOL;
        }
    }

    void print()
    {
        shared_ptr<SubNodeLOL> temp = list;
        while (temp)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class ListOfList
{

private:
    QString correoUsuario(int index, AVL* listUsers){
        User* user = listUsers->search_By_Id(index, "");
        return user->getEmail();
    }

public:
    shared_ptr<NodeLOL> head = nullptr;
    shared_ptr<NodeLOL> tail = nullptr;

    void insert(int index, int value)
    {
        shared_ptr<NodeLOL> new_NodeLOL = make_shared<NodeLOL>();
        new_NodeLOL->index = index;

        // Si la lista está vacía, inicializamos con el nuevo nodo
        if (!head)
        {
            head = new_NodeLOL;
            tail = new_NodeLOL;
            new_NodeLOL->append(value);
        }
        else
        {
            // Si el index ya existe en el head, simplemente hacemos append del valor
            if (index == head->index)
            {
                head->append(value);
                return;
            }

            // Si el nuevo index es menor que el del head, lo agregamos al inicio
            if (index < head->index)
            {
                head->prev = new_NodeLOL;
                new_NodeLOL->next = head;
                head = new_NodeLOL;
                new_NodeLOL->append(value);
            }
            else
            {
                // Recorremos la lista para encontrar si ya existe el nodo con el mismo index
                shared_ptr<NodeLOL> aux = head;

                while (aux != nullptr)
                {
                    // Si encontramos un nodo con el mismo index, hacemos append y salimos
                    if (aux->index == index)
                    {
                        aux->append(value);
                        return;
                    }

                    // Si aux->next es nullptr, significa que llegamos al final de la lista
                    if (aux->next == nullptr || index < aux->next->index)
                    {
                        break;  // Salimos del ciclo, ya que este es el lugar donde insertar
                    }

                    aux = aux->next;  // Avanzamos al siguiente nodo
                }

                // Ahora, insertamos el nuevo nodo en la posición correspondiente
                new_NodeLOL->next = aux->next;
                new_NodeLOL->prev = aux;
                if (aux->next)
                {
                    aux->next->prev = new_NodeLOL;
                }
                else
                {
                    tail = new_NodeLOL;  // Actualizamos el tail si estamos al final de la lista
                }
                aux->next = new_NodeLOL;
                new_NodeLOL->append(value);
            }
        }
    }

    void print()
    {
        shared_ptr<NodeLOL> temp = head;
        while (temp)
        {
            qDebug() << temp->index << ": ";
            temp->print();
            temp = temp->next;
        }
    }

    void graph(AVL& listUsers) {
        // Define las rutas absolutas para el archivo DOT y la imagen PNG
        QString dotFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase3/Fase3/reportes/graph.dot";
        QString pngFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase3/Fase3/reportes/graph.png";

        // Crear y abrir archivo DOT utilizando QFile
        QFile file(dotFilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "No se pudo abrir el archivo DOT para escritura.");
            return;
        }

        QTextStream out(&file);  // Para escribir en el archivo

        // Comenzar a escribir el archivo DOT
        out << "digraph G {" << Qt::endl;

        QSet<int> nodesCreated;  // Conjunto para rastrear los nodos que ya han sido creados

        // Aquí continuarías con la lógica de tu lista enlazada
        shared_ptr<NodeLOL> temp = head;
        while (temp) {
            // Si el nodo aún no ha sido creado, lo creamos
            if (!nodesCreated.contains(temp->index)) {
                out << temp->index << "[label=\"" << correoUsuario(temp->index, &listUsers) << "\"];" << Qt::endl;
                nodesCreated.insert(temp->index);  // Marcamos este nodo como creado
            }

            shared_ptr<SubNodeLOL> temp2 = temp->list;
            while (temp2) {
                // Si el nodo destino (el amigo) aún no ha sido creado, lo creamos
                if (!nodesCreated.contains(temp2->value)) {
                    out << temp2->value << "[label=\"" << correoUsuario(temp2->value, &listUsers) << "\"];" << Qt::endl;
                    nodesCreated.insert(temp2->value);  // Marcamos el nodo como creado
                }

                // Crear la relación entre los nodos
                out << temp->index << " -> " << temp2->value << "[dir=none];" << Qt::endl;
                temp2 = temp2->next;
            }

            temp = temp->next;
        }

        out << "}" << endl;
        file.close();  // Cerramos el archivo DOT

        // Usar QProcess para ejecutar el comando de Graphviz y generar la imagen PNG
        QString command = "dot";
        QStringList arguments;
        arguments << "-Tpng" << dotFilePath << "-o" << pngFilePath;

        QProcess process;
        process.start(command, arguments);
        process.waitForFinished();  // Espera a que el proceso termine

        // Verificar si el proceso fue exitoso
        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            QMessageBox::information(nullptr, "Imagen Generada", "La imagen se generó exitosamente.");
        } else {
            QMessageBox::critical(nullptr, "Error", "No se pudo generar la imagen.");
            qDebug() << "Error:" << process.errorString();
        }
    }

    void graphAsAdjacencyList(AVL& listUsers) {
        // Define las rutas absolutas para el archivo DOT y la imagen PNG
        QString dotFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase3/Fase3/reportes/adjacency_list_boxes.dot";
        QString pngFilePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase3/Fase3/reportes/adjacency_list_boxes.png";

        // Crear y abrir archivo DOT utilizando QFile
        QFile file(dotFilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr, "Error", "No se pudo abrir el archivo DOT para escritura.");
            return;
        }

        QTextStream out(&file);  // Para escribir en el archivo

        // Inicio del archivo DOT
        out << "digraph G {" << Qt::endl;
        out << "\tnode [shape=box];" << Qt::endl;

        // Lista enlazada principal
        shared_ptr<NodeLOL> temp = head;
        int No_nodo = 0;
        int base1;
        int base2;

        while (temp) {
            // Escribir el nodo principal con el correo del usuario
            out << "\t" << No_nodo << " [label=\"" << correoUsuario(temp->index, &listUsers) << "\"];" << Qt::endl;
            int base = No_nodo;  // Guardar la referencia del nodo actual (usuario principal)
            No_nodo++;  // Incrementar para el siguiente nodo

            // Sublista de amigos del nodo actual
            shared_ptr<SubNodeLOL> temp2 = temp->list;
            bool first = true;

            if (temp2) {
                // Definir un subgrafo para agrupar con rank=same a los amigos del nodo principal
                out << "\t{" << Qt::endl;
                out << "\t\trank = same;" << Qt::endl;

                while (temp2) {
                    // Crear un nodo para cada subnodo (amigo) y conectarlo con el nodo principal
                    out << "\t\t" << No_nodo << " [label=\"" << correoUsuario(temp2->value, &listUsers) << "\"];" << Qt::endl;

                    // Conectar el nodo principal a su primer amigo
                    if (first) {
                        out << "\t\t" << base << " -> " << No_nodo << " [label=\"amistades\"];" << Qt::endl;
                        first = false;
                    } else {
                        // Conectar amigos entre sí si son múltiples
                        out << "\t\t" << (No_nodo - 1) << " -> " << No_nodo << ";" << Qt::endl;
                    }

                    No_nodo++;
                    temp2 = temp2->next;
                }

                out << "\t}" << Qt::endl;  // Cerrar el subgrafo
            }

            if ( temp->next != nullptr ){
                out << "\t\t" << base << " -> " << No_nodo << ";" << Qt::endl;
            }

            // Mover al siguiente nodo de la lista principal (usuarios)
            temp = temp->next;
        }

        // Cierre del archivo DOT
        out << "}" << Qt::endl;
        file.close();

        // Ejecutar Graphviz para generar la imagen PNG
        QString command = "dot";
        QStringList arguments;
        arguments << "-Tpng" << dotFilePath << "-o" << pngFilePath;

        QProcess process;
        process.start(command, arguments);
        process.waitForFinished();  // Espera a que el proceso termine

        // Verificar si el proceso fue exitoso
        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            QMessageBox::information(nullptr, "Imagen Generada", "La imagen se generó exitosamente.");
        } else {
            QMessageBox::critical(nullptr, "Error", "No se pudo generar la imagen.");
            qDebug() << "Error:" << process.errorString();
        }
    }



};

#endif // LISTOFLIST_H
