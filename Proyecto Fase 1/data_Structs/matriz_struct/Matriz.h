#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <iomanip>
#include "../../models/solicitud.h"

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
};

#endif