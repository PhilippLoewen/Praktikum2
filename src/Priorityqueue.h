//
// Created by loewi on 09.04.16.
//

#ifndef PRAKTIKUM2_PRIORITYQUEUE_H
#define PRAKTIKUM2_PRIORITYQUEUE_H

#include <string>
#include <exception>

class QueueException {
public:
    QueueException(std::string message, int code);
    std::string msg();
    int code();

protected:
    std::string _msg;
    int _errorCode;

};

template <typename T>
class Priorityqueue {
public:
    void insert(T value, float p);

    T extractMin();

    void decreaseKey(T value, float p);

    void remove(T value);

    bool isEmpty();

    Priorityqueue();

    ~Priorityqueue();



private:
    struct pqentry_t {
        T value;
        float prio;
    };
    unsigned long insPos;
    unsigned long size;
    pqentry_t **content;
    void bubbleDown(unsigned long index);
    void swap(unsigned long index1, unsigned long index2);
    void bubbleUp(unsigned long index);
    unsigned long getParent(unsigned long index);
    unsigned long getLeftChild(unsigned long index);
    unsigned long getRightChild(unsigned long index);
    unsigned long findByValue(T value, unsigned long start);
    T removeIndx(unsigned long index);

    void grow();
    void shrink();
};



#endif //PRAKTIKUM2_PRIORITYQUEUE_H
