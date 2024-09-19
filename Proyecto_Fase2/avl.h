#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QMessageBox>
#include <Qstring>
#include <QDebug>
#include "user.h" // Asegúrate de incluir el archivo de cabecera para la clase User

using namespace std;

struct NodeAVL {
    User* user; // Cambiamos de int value a User*
    int height = 1;
    NodeAVL* left = nullptr;
    NodeAVL* right = nullptr;

    NodeAVL(User* usr) : user(usr) {}
};

class AVL {
private:
    int userCount = 0; // Contador de usuarios

    // Inserción recursiva
    NodeAVL* insertRec(NodeAVL* node, User* user, bool& added) {
        if (!node) {
            added = true; // Indicar que se ha añadido un usuario
            return new NodeAVL(user);
        }

        // Ordenar alfabéticamente por correo
        if (user->getEmail() < node->user->getEmail()) {
            node->left = insertRec(node->left, user, added);
        } else if (user->getEmail() > node->user->getEmail()) {
            node->right = insertRec(node->right, user, added);
        } else {
            // Correo ya existe, mostrar mensaje y no insertar
            QMessageBox::warning(nullptr, "Error", "El correo electrónico " + user->getEmail() + " ¡Ya existe!");
            added = false;
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Verificar balance y aplicar rotaciones
        int balance = getBalance(node);

        if (balance > 1) {
            if (user->getEmail() < node->left->user->getEmail()) {
                return rightRotation(node);
            } else {
                node->left = leftRotation(node->left);
                return rightRotation(node);
            }
        }

        if (balance < -1) {
            if (user->getEmail() > node->right->user->getEmail()) {
                return leftRotation(node);
            } else {
                node->right = rightRotation(node->right);
                return leftRotation(node);
            }
        }

        return node;
    }

    // Rotación hacia la izquierda
    NodeAVL* leftRotation(NodeAVL* node) {
        NodeAVL* newRoot = node->right;
        NodeAVL* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    // Rotación hacia la derecha
    NodeAVL* rightRotation(NodeAVL* node) {
        NodeAVL* newRoot = node->left;
        NodeAVL* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    int getHeight(NodeAVL* node) const {
        return node ? node->height : 0;
    }

    int getBalance(NodeAVL* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }


    // Método auxiliar para imprimir el árbol en formato .dot
    void printRec(NodeAVL* node, const QString& nodeName, QTextStream& out, int& nodeCount) const {
        if (!node) return;

        // Crear etiquetas para los nodos con el correo del usuario
        QString label = QString("%1").arg(node->user->getEmail());

        // Etiqueta del nodo
        out << "\"" << nodeName << "\" [label=\"" << label << "\"];\n";

        // Imprimir nodos hijos
        if (node->left) {
            QString leftChild = QString("Nodo%1").arg(++nodeCount);
            out << "\"" << nodeName << "\" -> \"" << leftChild << "\";\n";
            printRec(node->left, leftChild, out, nodeCount);
        }

        if (node->right) {
            QString rightChild = QString("Nodo%1").arg(++nodeCount);
            out << "\"" << nodeName << "\" -> \"" << rightChild << "\";\n";
            printRec(node->right, rightChild, out, nodeCount);
        }
    }

    // Recorrido en orden para recolectar usuarios
    void inOrderRec(NodeAVL* node, vector<User*>& users) const {
        if (!node) return;

        inOrderRec(node->left, users);
        users.push_back(node->user);
        inOrderRec(node->right, users);
    }


public:
    NodeAVL* root = nullptr;
    // Método append que devuelve bool
    bool append(User* user, int opcion) {
        bool added = false;
        root = insertRec(root, user, added);
        if (added) {
            userCount++; // Incrementar el contador de usuarios
            // Mostrar mensaje de éxito
            if ( opcion == 0 )
            {
                QMessageBox::information(nullptr, "Éxito", "Tu cuenta fue creada con éxito");
            }
        }
        return added;
    }

    // Buscar un usuario por email y contraseña
    User* search_LogIn(const QString& email, const QString& password) {
        NodeAVL* current = root;
        while (current != nullptr) {
            if (email == current->user->getEmail() && password == current->user->getPassword()) {
                QMessageBox::information(nullptr, "Éxito", "Se ha iniciado sesión correctamente");
                return current->user;
            } else if (email < current->user->getEmail()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        QMessageBox::warning(nullptr, "Error", "El correo o la contraseña no corresponden a ningún usuario");
        return nullptr;
    }

    int size_List(){
        return userCount;
    }

    // Método para acceder a un usuario por índice
    User* at(int index) {
        if (index < 0 || index >= userCount) {
            return nullptr; // Índice fuera de rango
        }

        vector<User*> users;
        inOrderRec(root, users);

        return users[index];
    }

    // Método para buscar un usuario por ID o por correo (opcional)
    User* search_By_Id(int id, const QString& correo = QString()) {
        NodeAVL* current = root;
        while (current) {
            // Verificar si el ID o el correo coinciden
            if (current->user->getIdUser() == id || correo == current->user->getEmail()) {
                return current->user;
            }

            // Moverse a la izquierda o a la derecha según el correo
            if (correo.isEmpty() || correo < current->user->getEmail()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return nullptr;
    }

    // Método para graficar el árbol AVL
    void graph(const QString& filename) const {
        QString dotFilename = filename + ".dot";
        QString pngFilename = filename + ".png";

        // Escribir el archivo .dot
        QFile file(dotFilename);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "digraph G {\n";
            out << "node [shape=box];\n"; // Opcional: Define la forma de los nodos como cajas

            if (root) {
                int nodeCount = 0;
                // Imprimir la raíz del árbol
                printRec(root, QString("Nodo%1").arg(++nodeCount), out, nodeCount);
            }

            out << "}\n";
            file.close();
        } else {
            cerr << "Error opening file for writing: " << dotFilename.toStdString() << endl;
            return;
        }

        // Ejecutar el comando de Graphviz usando QProcess
        QProcess process;
        QStringList arguments;
        arguments << "-Tpng" << dotFilename << "-o" << pngFilename;

        process.start("dot", arguments);
        if (!process.waitForFinished()) {
            cerr << "Error generating image: " << process.errorString().toStdString() << endl;
        } else {
            cout << "Image generated successfully\n";
        }
    }

    AVL* getDesconocidos(int id_User, LinkedList_Sol& list_Env, LinkedList_Sol& list_Sol, LinkedList_Sol& amigos) {
        // Crear un nuevo AVL para almacenar los desconocidos
        AVL *listDesconocidos = new AVL();
        // Función lambda recursiva para recorrer el AVL y encontrar los desconocidos
        function<void(NodeAVL* node)> findDesconocidos = [&](NodeAVL* node) {
            if (!node) return;

            // Si el usuario actual es el que ha iniciado sesión, lo omitimos
            if (node->user->getIdUser() == id_User) {
                findDesconocidos(node->left);
                findDesconocidos(node->right);
                return;
            }

            bool solicitud_enviada = false;
            bool solicitud_recibida = false;
            bool amigs = false;

            // Revisar si se ha enviado una solicitud a este usuario
            Node_Sol* temp2 = list_Env.head;
            while (temp2 != nullptr) {
                if (temp2->solicitud->getCorreoReceptor() == node->user->getEmail()) {
                    solicitud_enviada = true;
                    break;
                }
                temp2 = temp2->next;
            }

            // Revisar si se ha recibido una solicitud de este usuario
            Node_Sol* temp3 = list_Sol.head;
            while (temp3 != nullptr) {
                if (temp3->solicitud->getCorreoEmisor() == node->user->getEmail()) {
                    solicitud_recibida = true;
                    break;
                }
                temp3 = temp3->next;
            }

            // Revisar si el usuario ya es amigo
            Node_Sol* temp4 = amigos.head;
            while (temp4 != nullptr) {
                if (temp4->solicitud->getCorreoEmisor() == node->user->getEmail() ||
                    temp4->solicitud->getCorreoReceptor() == node->user->getEmail()) {
                    amigs = true;
                    break;
                }
                temp4 = temp4->next;
            }
            if (!solicitud_enviada && !solicitud_recibida && !amigs) {
                listDesconocidos->append(node->user, -1);
            }

            // Recorrer los subárboles izquierdo y derecho
            findDesconocidos(node->left);
            findDesconocidos(node->right);
        };

        // Comenzar a recorrer desde la raíz del AVL principal
        findDesconocidos(root);

        return listDesconocidos;
    }

};

#endif // AVL_H
