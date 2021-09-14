#include "PriorityQueue.h"
#include "../src/PriorityQueue.cpp"
#include "gtest/gtest.h"
 
using namespace std;
 
TEST(PriorityQueue, AddingItems) {
    PriorityQueue<int> pq;
    pq.push(45);
    pq.push(20);
    pq.push(14);
    pq.push(12);
    pq.push(31);
    pq.push(7);
    pq.push(11);
    pq.push(13);
    pq.push(7);
    ASSERT_EQ(pq.pop(), 7);
}

TEST(PriorityQueue, CheckingSize) {
    PriorityQueue<int> pq;
    ASSERT_EQ(pq.getSize(), 0);
    pq.push(45);
    ASSERT_EQ(pq.getSize(), 1);
    pq.push(20);
    ASSERT_EQ(pq.getSize(), 2);
    pq.push(14);
    ASSERT_EQ(pq.getSize(), 3);
    pq.pop();
    ASSERT_EQ(pq.getSize(), 2);
    pq.pop();
    ASSERT_EQ(pq.getSize(), 1);
    pq.pop();
    ASSERT_EQ(pq.getSize(), 0);
}

TEST(PriorityQueue, CheckOrder) {
    PriorityQueue<int> pq;
    pq.push(45);
    pq.push(20);
    pq.push(14);
    pq.push(12);
    pq.push(31);
    pq.push(7);
    pq.push(11);
    pq.push(13);
    pq.push(7);
    ASSERT_EQ(pq.pop(), 7);
    ASSERT_EQ(pq.pop(), 7);
    ASSERT_EQ(pq.pop(), 11);
    ASSERT_EQ(pq.pop(), 12);
    ASSERT_EQ(pq.pop(), 13);
    ASSERT_EQ(pq.pop(), 14);
    ASSERT_EQ(pq.pop(), 20);
    ASSERT_EQ(pq.pop(), 31);
    ASSERT_EQ(pq.pop(), 45);
}
 
int main(int argc, char** argv) {
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}

