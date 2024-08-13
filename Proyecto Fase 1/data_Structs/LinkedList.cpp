#include <iostream>
#include "LinkedList.h"
#include "../models/user.cpp"

using namespace std;

LinkedList::LinkedList()
{
    head = nullptr;
}

void LinkedList::append(User* value)
{
    Node *newNode = new Node(value);
    if ( head == nullptr )
    {
        head = newNode;
    }
    else
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LinkedList::print()
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->user->getLastname() << " -> ";
        temp = temp->next;
    }
    cout << " nullptr" << endl;
}