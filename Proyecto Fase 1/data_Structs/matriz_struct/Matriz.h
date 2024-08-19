#ifndef MATRIZ_H
#define MATRIZ_H

#include "Node.h"
#include "NodeVal.h"


class Matriz {
    
    private:
        Node* root;
        int width;
        int height;

    public:

        Matriz();
        /*
        void insert(int i, int j, Solicitud* sol);
        Node* searchRow(int i);
        Node* searchColumn(int j);
        bool nodeExists(Node* newNode);
        Node* insertRowHeader(int i);
        Node* insertColumnHeader(int j);
        void insertInRow(Node* newNode, Node* rowHeader);
        void insertInColumn(Node* newNode, Node* columnHeader);
        void print() const;
        void printColumnHeaders() const;
        NodeVal getValue(int i, int j) const;
        */
};

#endif