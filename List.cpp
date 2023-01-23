//
// Created by matias on 1/23/23.
//

#include "List.h"
#include <iostream>

List::List() {
    first = nullptr;
    end = nullptr;
};

List::~List() {
    delete first;
};

void List::createNewNode() {
    Node *newNode = new Node;

    if (empty()) {
        first = newNode;
        end = newNode;
        end->next = first;
    } else {
        end->setNext(newNode);
        end = newNode;
        end->next = nullptr;
    }

}

bool List::empty() {
    return (first == nullptr);
}

//Deleta o último elemento da lista;
void List::deleteElement() {
    if (!empty()) {
        if (first->next == nullptr)
            first = nullptr;
        else if (first->next->next == nullptr)
            first->setNext(nullptr);
        else {
            Node *ant_ant = first;
            Node *ant = first->next;
            Node *chain = first->next->next;

            while (chain) {
                Node *aux = ant;
                ant = chain;
                ant_ant = aux;
                chain = chain->next;
            }
            delete ant_ant->next;
            ant_ant->setNext(nullptr);
            end = ant_ant;
        }
    }
}

int List::sizeList() {
    if (empty())
        return 0;

    Node *f = first;
    int size = 0;

    do {
        f = f->next;
        size++;
    } while (f);

    return size;
}

