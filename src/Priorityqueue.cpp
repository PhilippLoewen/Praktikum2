//
// Created by loewi on 09.04.16.
//

#include "Priorityqueue.h"
#include <algorithm>

#define STARTSIZE 100


Priorityqueue::Priorityqueue() {
    size = STARTSIZE;
    insPos = 0;
    content = new pqentry_t*[size];
    for (int i = 0; i < size; i++) {
        content[i] = new pqentry_t;
    }
}

void Priorityqueue::insert(std::string value, float p) {
    if (insPos == size) {
        grow();
    }
    content[insPos]->value = value;
    content[insPos]->prio = p;
    bubbleUp(insPos);
    insPos -= 1;
}

std::string Priorityqueue::extractMin() {
    return removeIndx(0);
}

void Priorityqueue::bubbleUp(unsigned long index) {
    unsigned long i = index;
    while ( content[i]->prio < content[getParent(i)]->prio) {
        swap(i, getParent(i));
        i = getParent(i);
    }
}

unsigned long Priorityqueue::getParent(unsigned long index) {
    return index / 2;
}

void Priorityqueue::swap(unsigned long index1, unsigned long index2) {
    pqentry_t *tmp = content[index1];
    content[index1] = content[index2];
    content[index2] = tmp;
}

void Priorityqueue::bubbleDown(unsigned long index) {
    unsigned long i = index;
    do {
        unsigned long min = i;
        if (getLeftChild(i) < insPos && content[getLeftChild(i)]->prio < content[min]->prio) {
            min = getLeftChild(i);
        }
        if (getRightChild(i) < insPos && content[getRightChild(i)]->prio < content[min]->prio) {
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
            content[i]->prio = p;

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
    while  (i < insPos && value != content[i]->value) {
        ++i;
    }
    if (i == insPos) {
        return insPos;
    }
    return 0;
}

std::string Priorityqueue::removeIndx(unsigned long index) {
    unsigned long i = index;
    unsigned long last_idx = insPos - 1;
    if (0 <= i && i <= last_idx && insPos != 0) {
        unsigned long length = content[i]->value.length();
        std::string val = content[i]->value;
        if (last_idx > 0) {
            swap(i, last_idx);
            insPos -= 1;
        }
        if (i != last_idx) {
            if (i == 0 || content[i]->prio > content[getParent(i)]->prio) {
                bubbleDown(i);
            }
            else {
                bubbleUp(i);
            }
        }
        return val;
    }
    else {
        throw QueueException("Index nicht vorhanden", 2);
    }
}

void Priorityqueue::remove(std::string value) {
    unsigned long index = 0;
        while (index != insPos) {
                index = findByValue(value,index);
                removeIndx(index);
        }
}

Priorityqueue::~Priorityqueue() {

    for(int i = 0; i < size; i++) {
        delete content[i];
    }

    delete[](content);

}

void Priorityqueue::grow() {
    unsigned long newSize = size * 2;
    pqentry_t **new_content = new pqentry_t*[newSize];
    for (unsigned long i = 0; i < size; i++) {
        new_content[i] = content[i];
    }
    for (unsigned long i = size; i < newSize; i++) {
        new_content[i] = new pqentry_t;
    }
    delete[] content;
    content = new_content;
}


QueueException::QueueException(std::string message, int code) : _msg(message), _errorCode(code) {

}

std::string QueueException::msg() {
    return _msg;
}

int QueueException::code() {
    return _errorCode;
}





