#ifndef ABB_H
#define ABB_H

#include <memory>
#include <fstream>
#include <string>
#include <QDate>
#include <QMessageBox>
#include <QProcess>  // Incluye QProcess para ejecutar comandos de consola
#include <QDebug>

#include "publicacion.h"
#include "linkedlistpost.h"

using namespace std;

class NodeABB {
public:
    QDate value;                      // Valor almacenado en el nodo el cual tiene la fecha
    LinkedListPost* listPost;                         // Valor almacenado con la lista enlazada simple
    shared_ptr<NodeABB> left, right;   // Punteros a los nodos izquierdo y derecho

    // Constructor del nodo
    NodeABB(QDate val) : value(val), listPost(new LinkedListPost()), left(nullptr), right(nullptr) {}
};

class ABB {
private:
    shared_ptr<NodeABB> root;          // Puntero a la raíz del árbol
    int globalNodeCount;            // Contador global de nodos

    bool insertRec(shared_ptr<NodeABB>& root, QDate val, Publicacion* post) {
        if (!root) {  // Si el nodo actual es nulo, se inserta el nuevo nodo aquí
            root = make_shared<NodeABB>(val);
            root->listPost->append(post);
            return true;
        } else if (val < root->value) {  // Si el valor es menor, se inserta en el subárbol izquierdo
            insertRec(root->left, val, post);
            return true;
        } else if (val > root->value) {  // Si el valor es mayor, se inserta en el subárbol derecho
            insertRec(root->right, val, post);
            return true;
        }
        root->listPost->append(post);
        // Si el valor es igual, no se hace nada (no se permiten duplicados)
        return false;
    }

    // Función recursiva para generar el archivo DOT para graficar el árbol
    void printRec(shared_ptr<NodeABB> root, const string& name, ofstream& file, int& printNodeCount) const {
        if (root) {
            // Se generan nombres únicos para los nodos hijos
            string left = "Nodo" + to_string(++printNodeCount);
            string right = "Nodo" + to_string(++printNodeCount);

            // Escribe el nodo actual en el archivo DOT
            file << '"' << name << '"' << "[label=\"" << root->value.toString("dd/MM/yyyy").toStdString() << "\"];\n";
            if (root->left) {
                // Conecta el nodo actual con su hijo izquierdo
                file << '"' << name << "\"->\"" << left << "\";\n";
                printRec(root->left, left, file, printNodeCount);  // Recurre en el hijo izquierdo
            }
            if (root->right) {
                // Conecta el nodo actual con su hijo derecho
                file << '"' << name << "\"->\"" << right << "\";\n";
                printRec(root->right, right, file, printNodeCount);  // Recurre en el hijo derecho
            }
        }
    }

    // Método recursivo para buscar un nodo por fecha
    LinkedListPost* searchRec(shared_ptr<NodeABB> root, QDate date) const {
        if (!root) {
            return nullptr;  // Retorna nullptr si el nodo no se encuentra
        }

        if (date == root->value) {  // Si la fecha coincide con la del nodo actual
            return root->listPost;  // Retorna la lista de publicaciones asociada a este nodo
        } else if (date < root->value) {  // Si la fecha es menor, busca en el subárbol izquierdo
            return searchRec(root->left, date);
        } else {  // Si la fecha es mayor, busca en el subárbol derecho
            return searchRec(root->right, date);
        }
    }

public:

    bool insert(QDate val, Publicacion* post) {
        if (!root) {
            root = make_shared<NodeABB>(val);
            root->listPost->append(post);
            return true;
        } else {
            return insertRec(root, val, post);
        }
    }

    // Función para graficar el árbol
    void graph() const {
        // Rutas especificadas
        string basePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/";
        string filename = "abb";

        // Construir los nombres completos de los archivos .dot y .png
        string dotFilename = basePath + filename + ".dot";
        string pngFilename = basePath + filename + ".png";

        ofstream file(dotFilename);
        file << "digraph G {\n";  // Inicia el archivo DOT
        if (root) {
            int printNodeCount = 0;  // Reinicia el contador de nodos para graficar
            printRec(root, "Nodo" + to_string(++printNodeCount), file, printNodeCount);
        }
        file << "}\n";  // Finaliza el archivo DOT
        file.close();

        // Ejecuta el comando para convertir el archivo DOT en una imagen PNG usando QProcess
        QString command = "dot";
        QStringList arguments;
        arguments << "-Tpng" << QString::fromStdString(dotFilename) << "-o" << QString::fromStdString(pngFilename);

        QProcess process;
        process.start(command, arguments);
        process.waitForFinished();  // Espera a que el proceso termine

        // Verifica el estado del proceso
        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            QMessageBox::information(nullptr, "Imagen ABB", "La imagen ABB se cargó con éxito");
        } else {
            QMessageBox::critical(nullptr, "Error en dot ABB", "Error al generar imagen de ABB");
            qDebug() << "Error:" << process.errorString();
        }
    }

    // Método público para buscar un nodo por fecha
    LinkedListPost* search(QDate date) const {
        return searchRec(root, date);  // Inicia la búsqueda desde la raíz
    }

};

#endif // ABB_H
