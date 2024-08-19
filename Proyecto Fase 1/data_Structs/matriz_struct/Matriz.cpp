#include "Matriz.h"
#include <iostream>
#include <iomanip>

using namespace std;

Matriz::Matriz() : root(nullptr), width(0), height(0) {}
/*
void Matriz::insert(int i, int j, Solicitud* sol) {
    Node* newNode = new Node(i, j, sol);

    if (!root) {
        root = new Node(-1, -1);
    }

    Node* row = searchRow(i);
    Node* column = searchColumn(j);

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

Node* Matriz::searchRow(int i) {
    Node* current = root;

    while (current) {
        if (current->i == i) return current;
        current = current->down;
    }
    return nullptr;
}

Node* Matriz::searchColumn(int j) {
    Node* current = root;

    while (current) {
        if (current->j == j) return current;
        current = current->right;
    }
    return nullptr;
}

bool Matriz::nodeExists(Node* newNode) {
    Node* rowHeader = root;

    while (rowHeader) {
        if (rowHeader->i == newNode->i) {
            Node* column = rowHeader;
            while (column) {
                if (column->j == newNode->j) {
                    column->sol = newNode->sol;
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

Node* Matriz::insertRowHeader(int i) {
    Node* newRowHeader = new Node(i, -1);
    insertInRow(newRowHeader, root);
    return newRowHeader;
}

Node* Matriz::insertColumnHeader(int j) {
    Node* newColumnHeader = new Node(-1, j);
    insertInColumn(newColumnHeader, root);
    return newColumnHeader;
}

void Matriz::insertInRow(Node* newNode, Node* rowHeader) {
    Node* current = rowHeader;

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

void Matriz::insertInColumn(Node* newNode, Node* columnHeader) {
    Node* current = columnHeader;

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

void Matriz::print() const {
    printColumnHeaders();

    for (int i = 0; i <= height; ++i) {
        cout << "\n" << setw(3) << i;
        for (int j = 0; j <= width; ++j) {
            NodeVal val = getValue(i, j);
            if (!val.exists) {
                cout << setw(3) << "X";
            } else {
                cout << setw(3) << val.sol;
            }
        }
    }
    cout << endl;
}

void Matriz::printColumnHeaders() const {
    for (int j = -1; j <= width; ++j) {
        cout << setw(3) << j;
    }
}

NodeVal Matriz::getValue(int i, int j) const {
    NodeVal val;
    Node* rowHeader = root;

    while (rowHeader) {
        if (rowHeader->i == i) {
            Node* column = rowHeader;
            while (column) {
                if (column->j == j) {
                    val.sol = column->sol;
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
*/