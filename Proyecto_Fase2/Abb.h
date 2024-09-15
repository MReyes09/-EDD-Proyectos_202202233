#ifndef ABB_H
#define ABB_H

#include <memory>
#include <fstream>
#include <string>
#include <QDate>
#include <QMessageBox>

using namespace std;

class NodeABB{
public:
    QDate value;                      // Valor almacenado en el nodo el cual tiene la fecha
    int id;                         // Valor almacenado con la lista enlazada simple
    shared_ptr<NodeABB> left, right;   // Punteros a los nodos izquierdo y derecho

    // Constructor del nodo
    NodeABB(QDate val, int idVal) : value(val), id(idVal), left(nullptr), right(nullptr) {}
};

class ABB
{
private:
    shared_ptr<NodeABB> root;          // Puntero a la raíz del árbol
    int globalNodeCount;            // Contador global de nodos

    bool insertRec(shared_ptr<NodeABB>& root, QDate val)
    {
        if (!root) {  // Si el nodo actual es nulo, se inserta el nuevo nodo aquí
            root = make_shared<NodeABB>(val, ++globalNodeCount);
            return true;
        } else if (val < root->value) {  // Si el valor es menor, se inserta en el subárbol izquierdo
            insertRec(root->left, val);
            return true;
        } else if (val > root->value) {  // Si el valor es mayor, se inserta en el subárbol derecho
            insertRec(root->right, val);
            return true;
        }
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

public:
    bool insert(QDate val)
    {
        if(!root){
            root = make_shared<NodeABB>(val, ++globalNodeCount);
            return true;
        }else{
            return insertRec(root, val);
        }
    }

    // Función para graficar el árbol
    void graph(const string& filename) const {

        string basePath = "C:\\Users\\matth\\Descargas\\";
        // Construir los nombres completos de los archivos .dot y .png
        string dotFilename = basePath + filename + ".dot";
        string pngFilename = basePath + filename + ".png";
        string dotCommand = "dot -Tpng " + dotFilename + " -o " + pngFilename;  // Comando para generar la imagen

        ofstream file(dotFilename);
        file << "digraph G {\n";  // Inicia el archivo DOT
        if (root) {
            int printNodeCount = 0;  // Reinicia el contador de nodos para graficar
            printRec(root, "Nodo" + to_string(++printNodeCount), file, printNodeCount);
        }
        file << "}\n";  // Finaliza el archivo DOT
        file.close();

        // Ejecuta el comando para convertir el archivo DOT en una imagen PNG
        int result = system(dotCommand.c_str());
        if (result != 0) {
            QMessageBox::critical(nullptr, "Error en dot ABB", "Error al generar imagen de ABB");
        } else {
            QMessageBox::information(nullptr, "Imagen ABB", "La imagen ABB se cargo con exito");
        }
    }

};

#endif // ABB_H
