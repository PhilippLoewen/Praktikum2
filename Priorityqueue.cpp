//
// Created by loewi on 09.04.16.
//

#include "Priorityqueue.h"
#include <algorithm>


Priorityqueue::Priorityqueue() {

}

void Priorityqueue::insert(std::string value, float p) {
    pqentry_t data = {value, p};
    structs.push_back(data);
    bubbleUp(this->structs.size() -1);
}

std::string Priorityqueue::extractMin() {
    std::string tmpstr = structs[0].value;

    swap(0, structs.size() - 1);
    bubbleDown(0);
    structs.erase(structs.end() - 1);
    return tmpstr;
}

void Priorityqueue::bubbleUp(unsigned long index) {
    unsigned long i = index;
    while ( structs[i].prio < structs[getParent(i)].prio) {
        swap(i, getParent(i));
        i = getParent(i);
    }
}

unsigned long Priorityqueue::getParent(unsigned long index) {
    return index / 2;
}

void Priorityqueue::swap(unsigned long index1, unsigned long index2) {
    iter_swap(structs.begin() + index1, structs.begin() + index2);
}

void Priorityqueue::bubbleDown(unsigned long index) {
    unsigned long i = index;
    do {
        unsigned long min = i;
        if (getLeftChild(i) < structs.size() && structs[getLeftChild(i)].prio < structs[min].prio) {
            min = getLeftChild(i);
        }
        if (getRightChild(i) < structs.size() && structs[getRightChild(i)].prio < structs[min].prio) {
            min = getRightChild(i);
        }
        if (min == i) {
            break;
        }
        swap(i, min);
        i = min;

    } while(true);
}

unsigned long Priorityqueue::getLeftChild(unsigned long index) {
    return index * 2 + 1;
}

unsigned long Priorityqueue::getRightChild(unsigned long index) {
    return index * 2 + 2;
}

void Priorityqueue::decreaseKey(std::string value, float p) {
    try {
        unsigned long i = findByValue(value, 0);
        while (i >= 0 ) {
            structs[i].prio = p;

            bubbleUp(i);
            i = findByValue(value, i + 1);


            }
        }
    catch (int e) {
        if (e == 1) {
            return;
        }

    }
}

unsigned long Priorityqueue::findByValue(std::string value, unsigned long start) {
    unsigned long i = start;
    while  (i < structs.size() && value != structs[i].value){
        ++i;
    }
    if (i == structs.size()) {
        throw 1;
    }
    return 0;
}

void Priorityqueue::remove(std::string value) {

}























