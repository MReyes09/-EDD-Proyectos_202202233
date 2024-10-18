#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <iomanip>
#include "Solicitud.h"

using namespace std;

// Clase NodeVal para manejar los valores en la matriz
class NodeVal {
public:
    bool exists = false;
    Solicitud* value = nullptr;
};

// Clase NodeM para cada nodo de la matriz
class NodeM {
public:
    int i = -1, j = -1;
    Solicitud* value = nullptr;
    NodeM* up = nullptr;
    NodeM* down = nullptr;
    NodeM* right = nullptr;
    NodeM* left = nullptr;

    NodeM(int i = -1, int j = -1, Solicitud* value = nullptr) : i(i), j(j), value(value) {}
};


class Matriz {
private:
    NodeM* root = nullptr;
    int width = 0;
    int height = 0;

public:

    void insert(int i, int j, Solicitud* value) {
        NodeM* newNode = new NodeM(i, j, value);

        if (!root) {
            root = new NodeM(-1, -1);
        }

        NodeM* row = searchRow(i);
        NodeM* column = searchColumn(j);

        if (j > width) width = j;
        if (i > height) height = i;

        if (!nodeExists(newNode)) {
            if (!column) {
                column = insertColumnHeader(j);
            }

            if (!row) {
                row = insertRowHeader(i);
            }
            insertInColumn(newNode, row);
            insertInRow(newNode, column);
        }
    }


    NodeM* searchRow(int i) {
        NodeM* current = root;

        while (current) {
            if (current->i == i) return current;
            current = current->down;
        }
        return nullptr;
    }


    NodeM* searchColumn(int j) {
        NodeM* current = root;

        while (current) {
            if (current->j == j) return current;
            current = current->right;
        }
        return nullptr;
    }


    bool nodeExists(NodeM* newNode) {
        NodeM* rowHeader = root;

        while (rowHeader) {
            if (rowHeader->i == newNode->i) {
                NodeM* column = rowHeader;
                while (column) {
                    if (column->j == newNode->j) {
                        column->value = newNode->value;
                        return true;
                    }
                    column = column->right;
                }
                return false;
            }
            rowHeader = rowHeader->down;
        }
        return false;
    }


    NodeM* insertRowHeader(int i) {
        NodeM* newRowHeader = new NodeM(i, -1);
        insertInRow(newRowHeader, root);
        return newRowHeader;
    }


    NodeM* insertColumnHeader(int j) {
        NodeM* newColumnHeader = new NodeM(-1, j);
        insertInColumn(newColumnHeader, root);
        return newColumnHeader;
    }


    void insertInRow(NodeM* newNode, NodeM* rowHeader) {
        NodeM* current = rowHeader;

        while (current->down) {
            if (newNode->i < current->down->i && newNode->i > current->i) {
                newNode->down = current->down;
                newNode->up = current;
                current->down->up = newNode;
                current->down = newNode;
                return;
            }
            current = current->down;
        }

        current->down = newNode;
        newNode->up = current;
    }


    void insertInColumn(NodeM* newNode, NodeM* columnHeader) {
        NodeM* current = columnHeader;

        while (current->right) {
            if (newNode->j < current->right->j && newNode->j > current->j) {
                newNode->right = current->right;
                newNode->left = current;
                current->right->left = newNode;
                current->right = newNode;
                return;
            }
            current = current->right;
        }

        current->right = newNode;
        newNode->left = current;
    }


    void print() const {
        printColumnHeaders();

        for (int i = 0; i <= height; ++i) {
            cout << "\n" << setw(3) << i;
            for (int j = 0; j <= width; ++j) {
                NodeVal val = getValue(i, j);
                if (!val.exists) {
                    cout << setw(3) << "X";
                } else {
                    cout << setw(3) << "V";
                }
            }
        }
        cout << endl;
    }


    void printColumnHeaders() const {
        for (int j = -1; j <= width; ++j) {
            cout << setw(3) << j;
        }
    }


    NodeVal getValue(int i, int j) const {
        NodeVal val;
        NodeM* rowHeader = root;

        while (rowHeader) {
            if (rowHeader->i == i) {
                NodeM* column = rowHeader;
                while (column) {
                    if (column->j == j) {
                        val.value = column->value;
                        val.exists = true;
                        return val;
                    }
                    column = column->right;
                }
                return val;
            }
            rowHeader = rowHeader->down;
        }
        return val;
    }

    // void generateDot(){
    //     string filename = "report/matriz.dot";
    //     ofstream file2(filename);
    //     if (file2.is_open()) {
    //         file2 << "digraph Sparce_Matrix {" << endl;
    //         file2 << "node [shape=box, fontname=Arial];" << endl;

    //         // Nodo principal (raíz)
    //         file2 << "root [label=\"Root\", shape=ellipse, group=1];" << endl;

    //         // Encabezados de columna
    //         NodeM* currentColumn = root->right;
    //         while (currentColumn) {
    //             string user = currentColumn->j != -1 ? "User" + to_string(currentColumn->j) : "Col";
    //             file << "col" << currentColumn->j << " [label=<" << user << ">, shape=box, group=" << currentColumn->j + 2 << "];" << endl;
    //             file << "root -> col" << currentColumn->j << " [dir=none];" << endl;
    //             currentColumn = currentColumn->right;
    //         }

    //         // Encabezados de fila
    //         NodeM* currentRow = root->down;
    //         while (currentRow) {
    //             string user = currentRow->i != -1 ? "User" + to_string(currentRow->i) : "Row";
    //             file << "row" << currentRow->i << " [label=<" << user << ">, shape=box, group=1];" << endl;
    //             file << "root -> row" << currentRow->i << " [dir=none];" << endl;
    //             currentRow = currentRow->down;
    //         }

    //         // Conexión entre nodos
    //         currentRow = root->down;
    //         while (currentRow) {
    //             NodeM* currentNode = currentRow->right;
    //             while (currentNode) {
    //                 string nodeName = "node" + to_string(currentNode->i) + "_" + to_string(currentNode->j);
    //                 file << nodeName << " [label=<Solicitud>, shape=box, group=" << currentNode->j + 2 << "];" << endl;

    //                 if (currentNode->up) {
    //                     string upNodeName = currentNode->up->i == -1
    //                                             ? "col" + to_string(currentNode->up->j)
    //                                             : "node" + to_string(currentNode->up->i) + "_" + to_string(currentNode->up->j);
    //                     file << upNodeName << " -> " << nodeName << " [dir=none];" << endl;
    //                 }
    //                 if (currentNode->down) {
    //                     string downNodeName = "node" + to_string(currentNode->down->i) + "_" + to_string(currentNode->down->j);
    //                     file << nodeName << " -> " << downNodeName << " [dir=none];" << endl;
    //                 }
    //                 if (currentNode->left) {
    //                     string leftNodeName = "node" + to_string(currentNode->left->i) + "_" + to_string(currentNode->left->j);
    //                     file << leftNodeName << " -> " << nodeName << " [dir=none];" << endl;
    //                 }
    //                 if (currentNode->right) {
    //                     string rightNodeName = "node" + to_string(currentNode->right->i) + "_" + to_string(currentNode->right->j);
    //                     file << nodeName << " -> " << rightNodeName << " [dir=none];" << endl;
    //                 }

    //                 // Conexiones desde los encabezados
    //                 file << "row" << currentNode->i << " -> " << nodeName << " [dir=none];" << endl;
    //                 file << "col" << currentNode->j << " -> " << nodeName << " [dir=none];" << endl;

    //                 currentNode = currentNode->right;
    //             }
    //             currentRow = currentRow->down;
    //         }

    //         // Ajustar el rango para alinearlos adecuadamente
    //         file << "{ rank=same; root;";
    //         currentColumn = root->right;
    //         while (currentColumn) {
    //             file << " col" << currentColumn->j << ";";
    //             currentColumn = currentColumn->right;
    //         }
    //         file << "}" << endl;

    //         // Alinear filas
    //         currentRow = root->down;
    //         while (currentRow) {
    //             file << "{ rank=same; row" << currentRow->i << ";";
    //             NodeM* currentNode = currentRow->right;
    //             while (currentNode) {
    //                 string nodeName = "node" + to_string(currentNode->i) + "_" + to_string(currentNode->j);
    //                 file << nodeName << ";";
    //                 currentNode = currentNode->right;
    //             }
    //             file << "}" << endl;
    //             currentRow = currentRow->down;
    //         }

    //         file << "}" << endl;
    //         file.close();
    //     } else {
    //         cout << " || No se pudo abrir el archivo" << endl;
    //     }
    // }

    // void renderGraphviz(){
    //     string dotFilename = "report/matriz.dot";
    //     string imageFilename = "report/matriz.svg";

    //     string command = "dot -Tsvg " + dotFilename + " -o " + imageFilename;
    //     system(command.c_str());
    // }


};

#endif
