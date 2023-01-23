//
// Created by matias on 1/23/23.
//

#ifndef RELOGIOPONTO_LIST_H
#define RELOGIOPONTO_LIST_H

#include "Node.h"

class List {
public:
    Node *first{};
    Node *end{};

    List();

    virtual ~List();

    bool empty();

    void createNewNode();

    void deleteElement();

    int sizeList();
};


#endif //RELOGIOPONTO_LIST_H
