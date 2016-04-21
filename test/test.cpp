//
// Created by loewi on 17.04.16.
//

#include "gtest/gtest.h"
#include "../src/Priorityqueue.h"

#define MAX 100000

std::string randomString(int size) {
    int i;
    std::string str;
    for (i = 0; i < size; ++i) {
        str.push_back((char)((rand() % 26) + 'A'));
    }
    return str;
}

TEST(basic_tests, first) {

    std::string strings[MAX];
    float prios[MAX];
    unsigned long i;
    for (i = 0; i < MAX; i++) {
        strings[i] = randomString(8);
    }

    Priorityqueue pq;
    EXPECT_ANY_THROW(pq.extractMin());

    for(i = 0; i < MAX; i++) {
        pq.insert(strings[i], rand() % 100);
    }

}
