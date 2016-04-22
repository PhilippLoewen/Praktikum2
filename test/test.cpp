//
// Created by loewi on 17.04.16.
//

#include "gtest/gtest.h"
#include "../src/Priorityqueue.h"
#include "../src/Priorityqueue.cpp"
#include <string.h>
#include <iterator>

#define MAX 1000

std::string randomString(int size) {
    int i;
    std::string str;
    for (i = 0; i < size; ++i) {
        str.push_back((char)((rand() % 26) + 'A'));
    }
    return str;
}

TEST(basic_tests, insert) {

    std::string strings[MAX];
    float prios[MAX];
    unsigned long i;
    for (i = 0; i < MAX; i++) {
        strings[i] = randomString(8);
        prios[i] = rand() % 100;
    }

    Priorityqueue<std::string> pq;

    for(i = 0; i < MAX; i++) {
        pq.insert(strings[i], prios[i]);
    }

}

TEST(basic_tests, extractMin) {
    std::string strings[MAX];
    float prios[MAX];
    unsigned long i;
    for (i = 0; i < MAX; i++) {
        strings[i] = randomString(8);
        prios[i] = i;
    }

    Priorityqueue<std::string> pq;
    EXPECT_THROW(pq.extractMin(),QueueException);

    for(i = 0; i < MAX; i++) {
        pq.insert(strings[i], MAX - i);
    }

    for (i = 0; i < MAX; i++) {
        EXPECT_EQ(strings[MAX - i - 1],pq.extractMin());
    }

}


TEST(basic_tests, isEmpty) {
    std::string strings[MAX];
    float prios[MAX];
    unsigned long i;
    for (i = 0; i < MAX; i++) {
        strings[i] = randomString(8);
        prios[i] = i;
    }

    Priorityqueue<std::string> pq;
    EXPECT_TRUE(pq.isEmpty());

    for(i = 0; i < MAX; i++) {
        pq.insert(strings[i], MAX - i);
    }

    EXPECT_FALSE(pq.isEmpty());

    for (i = 0; i < MAX; i++) {
        pq.extractMin();
    }

    EXPECT_TRUE(pq.isEmpty());

}

TEST(basic_tests, decrease) {
    Priorityqueue<int> pq;

    pq.insert(5, 5);
    pq.insert(8, 8);

    pq.decreaseKey(8, 3);

    EXPECT_EQ(8, pq.extractMin());

    EXPECT_EQ(5, pq.extractMin());

}

TEST(basic_tests, increase) {
    Priorityqueue<int> pq;

    pq.insert(5, 5);
    pq.insert(8, 8);

    pq.decreaseKey(5, 10);

    EXPECT_EQ(8, pq.extractMin());

    EXPECT_EQ(5, pq.extractMin());

}

TEST(basic_tests, remove) {
    Priorityqueue<int> pq;

    for (int i = 0; i < 5; ++i){
        pq.insert(i,i);
    }
    try {
        pq.remove(2);
        pq.remove(4);
    }
    catch (QueueException e) {
        std::cout << e.msg() << e.code();
    }


    for (int i = 0; i < 5; ++i) {
        if (i != 2 && i != 4){
            try {
                EXPECT_EQ(i, pq.extractMin());

            }
            catch (QueueException e){
                std::cout << e.msg() << e.code();
            }

        }
    }

}