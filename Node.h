//
// Created by matias on 1/23/23.
//

#ifndef RELOGIOPONTO_NODE_H
#define RELOGIOPONTO_NODE_H


class Node {
public:
    int dayL;
    int mouthL;
    int yearL;

    int hoursS;
    int minutesS;
    int hoursE;
    int minutesE;

    int totalHours = -1;
    int totalMinutes = -1;

    Node *next;

    void setNext(Node *p) {
        next = p;
    }

    void calculateTotal() {
        totalHours = hoursE - hoursS;
        if (minutesS > minutesE) {
            totalHours--;
            totalMinutes = (minutesE + 60) - minutesS;
        } else
            totalMinutes = minutesE - minutesS;
    }
};


#endif //RELOGIOPONTO_NODE_H
