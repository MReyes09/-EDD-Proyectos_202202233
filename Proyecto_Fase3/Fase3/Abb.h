#ifndef ABB_H
#define ABB_H

#include <memory>
#include <fstream>
#include <string>
#include <QDate>
#include <QMessageBox>
#include <QProcess>  // Incluye QProcess para ejecutar comandos de consola
#include <QDebug>
#include "NodePost.h"

#include "publicacion.h"
#include "linkedlistpost.h"
#include "ordenamientoABB.cpp"

using namespace std;

class NodeABB {
public:
    int publicaciones;
    QDate value;                      // Valor almacenado en el nodo el cual tiene la fecha
    LinkedListPost* listPost;                         // Valor almacenado con la lista enlazada simple
    shared_ptr<NodeABB> left, right;   // Punteros a los nodos izquierdo y derecho

    // Constructor del nodo
    NodeABB(QDate val) : value(val), listPost(new LinkedListPost()), left(nullptr), right(nullptr), publicaciones(0) {}
};

class ABB {
private:
    shared_ptr<NodeABB> root;          // Puntero a la raíz del árbol
    int globalNodeCount;            // Contador global de nodos

    bool insertRec(shared_ptr<NodeABB>& root, QDate val, Publicacion* post) {
        if (!root) {  // Si el nodo actual es nulo, se inserta el nuevo nodo aquí
            root = make_shared<NodeABB>(val);
            root->listPost->append(post);
            root->publicaciones++;
            return true;
        } else if (val < root->value) {  // Si el valor es menor, se inserta en el subárbol izquierdo
            insertRec(root->left, val, post);

            return true;
        } else if (val > root->value) {  // Si el valor es mayor, se inserta en el subárbol derecho
            insertRec(root->right, val, post);
            return true;
        }
        root->listPost->append(post);
        root->publicaciones++;
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

    // Función recursiva para recorrido inorden con limitador
    void inOrderRec(shared_ptr<NodeABB> root, LinkedListPost* result, int& count, int limit) const {
        if (root && count < limit) {
            // Recorre el subárbol izquierdo
            inOrderRec(root->left, result, count, limit);

            // Procesa el nodo actual
            if (count < limit) {
                NodePost* temp = root->listPost->head;
                while( temp != nullptr ){
                    result->append(temp->post);
                    temp = temp->next;
                }
                count += 1; // Aumenta el contador según el número de publicaciones añadidas
            }

            // Recorre el subárbol derecho
            inOrderRec(root->right, result, count, limit);
        }
    }

    // Función recursiva para recorrido preorden con limitador
    void preOrderRec(shared_ptr<NodeABB> root, LinkedListPost* result, int& count, int limit) const {
        if (root && count < limit) {
            // Procesa el nodo actual
            if (count < limit) {
                NodePost* temp = root->listPost->head;
                while( temp != nullptr ){
                    result->append(temp->post);
                    temp = temp->next;
                }
                count += 1; // Aumenta el contador según el número de publicaciones añadidas
            }

            // Recorre el subárbol izquierdo
            preOrderRec(root->left, result, count, limit);

            // Recorre el subárbol derecho
            preOrderRec(root->right, result, count, limit);
        }
    }

    // Función recursiva para recorrido posorden con limitador
    void postOrderRec(shared_ptr<NodeABB> root, LinkedListPost* result, int& count, int limit) const {
        if (root && count < limit) {
            // Recorre el subárbol izquierdo
            postOrderRec(root->left, result, count, limit);

            // Recorre el subárbol derecho
            postOrderRec(root->right, result, count, limit);

            // Procesa el nodo actual
            if (count < limit) {
                NodePost* temp = root->listPost->head;
                while( temp != nullptr ){
                    result->append(temp->post);
                    temp = temp->next;
                }
                count += 1; // Aumenta el contador según el número de publicaciones añadidas
            }
        }
    }


public:

    bool insert(QDate val, Publicacion* post) {
        if (!root) {
            root = make_shared<NodeABB>(val);
            root->listPost->append(post);
            root->publicaciones++;
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

    // Recorrido inorden con límite
    LinkedListPost* inOrder(int limit) const {
        auto result = new LinkedListPost();  // Lista enlazada para almacenar las publicaciones
        int count = 0;  // Contador para limitar el número de nodos procesados
        inOrderRec(root, result, count, limit);
        return result;  // Retorna la lista de publicaciones obtenida
    }

    // Recorrido preorden con límite
    LinkedListPost* preOrder(int limit) const {
        auto result = new LinkedListPost();
        int count = 0;
        preOrderRec(root, result, count, limit);
        return result;
    }

    // Recorrido posorden con límite
    LinkedListPost* postOrder(int limit) const {
        auto result = new LinkedListPost();
        int count = 0;
        postOrderRec(root, result, count, limit);
        return result;
    }

    // Función recursiva para recolectar fechas y sus contadores
    void collectDates(shared_ptr<NodeABB> node, vector<FechaPublicacion>& fechas) const {
        if (node) {
            // Agrega la fecha y el contador al vector
            fechas.push_back(FechaPublicacion(node->value, node->publicaciones));

            // Recurre en los nodos izquierdo y derecho
            collectDates(node->left, fechas);
            collectDates(node->right, fechas);
        }
    }


    // Función para encontrar las tres fechas con más publicaciones
    vector<FechaPublicacion> topTresFechas() const {
        vector<FechaPublicacion> fechas;  // Vector para almacenar fechas y sus contadores
        collectDates(root, fechas);  // Llama a la función recursiva para llenar el vector

        // Ordena el vector por cantidad de publicaciones en orden descendente
        sort(fechas.begin(), fechas.end(), [](const FechaPublicacion& a, const FechaPublicacion& b) {
            return a.cantidad > b.cantidad;
        });

        // Crea un vector para almacenar las tres fechas principales
        vector<FechaPublicacion> topTres;
        for (int i = 0; i < 3 && i < fechas.size(); ++i) {
            topTres.push_back(fechas[i]);
        }

        return topTres;  // Retorna las tres fechas con más publicaciones
    }

    // Función para graficar el árbol incluyendo la lista de publicaciones de un nodo específico
    void graphDate(QDate dateG) {
        string basePath = "C:/Users/matth/OneDrive/Documentos/Proyectos C++/EDD_Proyectos_202202233/Proyecto_Fase2/report/";
        string filename = "abbDate";

        string dotFilename = basePath + filename + ".dot";
        string pngFilename = basePath + filename + ".png";

        ofstream file(dotFilename);
        file << "digraph G {\n";
        file << "node [shape=record];\n";
        file << "rankdir=TB;\n";  // Cambiar la dirección del gráfico

        // Graficar el árbol
        if (root) {
            printRec(root, file);  // Función que grafica el árbol completo
        }

        // Graficar la lista de publicaciones del nodo específico
        auto targetNode = findNodeByDate(root, dateG);
        if (targetNode) {
            graphPublications(targetNode, file);  // Graficar publicaciones del nodo encontrado
        }

        file << "}\n";  // Finaliza el archivo DOT
        file.close();

        // Ejecutar comando para convertir el archivo DOT en una imagen PNG
        QString command = "dot";
        QStringList arguments;
        arguments << "-Tpng" << QString::fromStdString(dotFilename) << "-o" << QString::fromStdString(pngFilename);

        QProcess process;
        process.start(command, arguments);
        process.waitForFinished();

        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            QMessageBox::information(nullptr, "Imagen ABB", "La imagen ABB se cargó con éxito");
        } else {
            QMessageBox::critical(nullptr, "Error en dot ABB", "Error al generar imagen de ABB");
            qDebug() << "Error:" << process.errorString();
        }
    }

    // Función para buscar un nodo por fecha
    shared_ptr<NodeABB> findNodeByDate(shared_ptr<NodeABB> node, QDate dateG) const {
        if (!node) return nullptr;  // Si el nodo es nulo, retorna nulo

        if (node->value == dateG) {
            return node;  // Nodo encontrado
        }

        // Buscar en el subárbol izquierdo o derecho
        if (dateG < node->value) {
            return findNodeByDate(node->left, dateG);
        } else {
            return findNodeByDate(node->right, dateG);
        }
    }

    // Función para graficar las publicaciones del nodo específico
    void graphPublications(shared_ptr<NodeABB> node, ofstream& file) const {
        // Graficar nodo de fecha
        file << "publications_" << node->value.toString("yyyyMMdd").toStdString() << " [label=\"{Publicaciones de "
             << node->value.toString("dd/MM/yyyy").toStdString() << "}\"];\n";

        // Graficar cada publicación en la lista enlazada
        NodePost* current = node->listPost->head;  // Asumiendo que tienes una lista enlazada de publicaciones
        int id = 0;
        while (current != nullptr) {
            string body = current->post->contenido.toStdString();  // Asumiendo que tienes un objeto Publicacion con contenido

            // Graficar cada publicación
            file << "pub_" << id << " [label=\"{" << body << "}\"];\n";
            file << "publications_" << node->value.toString("yyyyMMdd").toStdString() << " -> pub_" << id << ";\n";
            current = current->next;
            id++;
        }
    }

    // Función para imprimir el árbol
    void printRec(shared_ptr<NodeABB> node, ofstream& file) const {
        if (node) {
            file << "node_" << node->value.toString("yyyyMMdd").toStdString() << " [label=\"{"
                 << node->value.toString("dd/MM/yyyy").toStdString() << "}\"];\n";

            if (node->left) {
                file << "node_" << node->value.toString("yyyyMMdd").toStdString() << " -> node_"
                     << node->left->value.toString("yyyyMMdd").toStdString() << ";\n";
            }
            if (node->right) {
                file << "node_" << node->value.toString("yyyyMMdd").toStdString() << " -> node_"
                     << node->right->value.toString("yyyyMMdd").toStdString() << ";\n";
            }

            // Recursión en los subárboles
            printRec(node->left, file);
            printRec(node->right, file);
        }
    }
};

#endif // ABB_H
