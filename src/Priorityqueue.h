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


class Priorityqueue {
public:
    void insert(std::string value, float p);

    std::string extractMin();

    void decreaseKey(std::string value, float p);

    void remove(std::string value);

    void print();

    Priorityqueue();

    ~Priorityqueue();



private:
    struct pqentry_t {
        std::string value;
        float prio;
    };
    unsigned long insPos;
    unsigned long size;
    pqentry_t **content;
    void bubbleDown(unsigned long index);
    void swap(unsigned long index1, unsigned long index2);
    void bubbleUp(unsigned long index);
    unsigned long getParent(unsigned long index);
    unsigned  long getLeftChild(unsigned long index);
    unsigned long getRightChild(unsigned long index);
    unsigned long findByValue(std::string value, unsigned long start);
    std::string removeIndx(unsigned long index);

    void grow();
};


#endif //PRAKTIKUM2_PRIORITYQUEUE_H
