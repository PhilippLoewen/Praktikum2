//
// Created by loewi on 17.04.16.
//

#include "gtest/gtest.h"
#include "../src/Priorityqueue.h"
#include "../src/Priorityqueue.cpp"
#include <string.h>
#include <iterator>

#define MAX 100

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
        prios[i] = rand() % 100;
    }

    Priorityqueue<std::string> pq;
    EXPECT_ANY_THROW(pq.extractMin());

    for(i = 0; i < MAX; i++) {
        pq.insert(strings[i], prios[i]);
    }

    std::sort(std::begin(prios), std::end(prios));


    printf("nop");

}
