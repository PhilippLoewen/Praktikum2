//
// Created by loewi on 09.04.16.
//

#include "Priorityqueue.h"
#include <algorithm>

#define STARTSIZE 100

template<typename T>
Priorityqueue<T>::Priorityqueue() {
    size = STARTSIZE;
    insPos = 0;
    content = new pqentry_t *[size];
    for (int i = 0; i < size; i++) {
        content[i] = new pqentry_t;
    }
}

template<typename T>
void Priorityqueue<T>::insert(T value, float p) {
    if (insPos == size) {
        grow();
    }
    content[insPos]->value = value;
    content[insPos]->prio = p;
    bubbleUp(insPos);
    insPos += 1;
}

template<typename T>
T Priorityqueue<T>::extractMin() {
    return removeIndx(0);
}

template<typename T>
void Priorityqueue<T>::bubbleUp(unsigned long index) {
    unsigned long i = index;
    while (i > 0 && content[i]->prio < content[getParent(i)]->prio) {
        swap(i, getParent(i));
        i = getParent(i);
    }
}

template<typename T>
unsigned long Priorityqueue<T>::getParent(unsigned long index) {
    return (index - 1) / 2;
}

template<typename T>
void Priorityqueue<T>::swap(unsigned long index1, unsigned long index2) {
    pqentry_t tmp = *content[index1];
    *content[index1] = *content[index2];
    *content[index2] = tmp;
}

template<typename T>
void Priorityqueue<T>::bubbleDown(unsigned long index) {
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

    } while (true);
}

template<typename T>
unsigned long Priorityqueue<T>::getLeftChild(unsigned long index) {
    return index * 2 + 1;
}

template<typename T>
unsigned long Priorityqueue<T>::getRightChild(unsigned long index) {
    return index * 2 + 2;
}

template<typename T>
void Priorityqueue<T>::decreaseKey(T value, float p) {
    unsigned long i = findByValue(value, 0);
    float old_value;
    if (i == insPos) {
        throw QueueException("This doesn't exist in here", 1337);
    }
    while (i != insPos) {
        old_value = content[i]->prio;
        content[i]->prio = p;
        if (old_value > p) {
            bubbleUp(i);
        }
        else if (p > old_value){
            bubbleDown(i) ;
        };
        i = findByValue(value, i + 1);
    }


}

template<typename T>
unsigned long Priorityqueue<T>::findByValue(T value, unsigned long start) {
    unsigned long i = start;
    while (i < insPos && value != content[i]->value) {
        ++i;
    }
    if (i == insPos) {
        return insPos;
    }
    return i;
}

template<typename T>
T Priorityqueue<T>::removeIndx(unsigned long index) {
    unsigned long i = index;
    unsigned long last_idx = insPos - 1;
    if (0 <= i && i <= last_idx && insPos != 0) {
        T val = content[i]->value;
        if (last_idx > 0) {
            swap(i, last_idx);
            if (size / 2 > insPos) {
                shrink();
            }
        }
        insPos -= 1;
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

template<typename T>
void Priorityqueue<T>::remove(T value) {
    unsigned long index = findByValue(value,0);
    while (index != insPos) {
        removeIndx(index);
        index = findByValue(value, index + 1);
    }
}

template<typename T>
Priorityqueue<T>::~Priorityqueue() {

    for (int i = 0; i < size; i++) {
        delete content[i];
    }

    delete[](content);

}

template<typename T>
void Priorityqueue<T>::grow() {
    unsigned long newSize = size * 2;
    pqentry_t **new_content = new pqentry_t *[newSize];
    for (unsigned long i = 0; i < size; i++) {
        new_content[i] = content[i];
    }
    for (unsigned long i = size; i < newSize; i++) {
        new_content[i] = new pqentry_t;
    }
    delete[] content;
    content = new_content;
    size = newSize;
}

template<typename T>
bool Priorityqueue<T>::isEmpty() {
    return !insPos;
}

template<typename T>
void Priorityqueue<T>::shrink() {
    unsigned long newSize = size / 2;
    if (insPos < newSize) {
        pqentry_t **new_content = new pqentry_t *[newSize];
        for (unsigned long i = 0; i < newSize; i++) {
            new_content[i] = content[i];
        }
        delete[] content;
        content = new_content;
        size = newSize;
    }
}


QueueException::QueueException(std::string message, int code) : _msg(message), _errorCode(code) {

}

std::string QueueException::msg() {
    return _msg;
}

int QueueException::code() {
    return _errorCode;
}
