#include "ResizableArray.h"
#include "../src/ResizableArray.cpp"
#include "gtest/gtest.h"
 
using namespace std;
 
TEST(ResizableArray, AddingItems) {
    ResizableArray<int> ra(1);
    ra.push(2);
    ra.push(4);
    ra.push(6);
    ASSERT_EQ(ra[0], 2);
    ASSERT_EQ(ra[1], 4);
    ASSERT_EQ(ra[2], 6);
}

TEST(ResizableArray, SwappingItems) {
    ResizableArray<int> ra(4);
    ra.push(2);
    ra.push(4);
    ra.push(6);
    ra.swap(0, 2);
    ASSERT_EQ(ra[0], 6);
    ASSERT_EQ(ra[1], 4);
    ASSERT_EQ(ra[2], 2);
}

TEST(ResizableArray, MoveToTop) {
    ResizableArray<int> ra(4);
    ra.push(2);
    ra.push(4);
    ra.push(6);
    ra.moveToTop(2);
    ASSERT_EQ(ra[0], 6);
    ASSERT_EQ(ra[1], 4);
    ASSERT_EQ(ra[2], 100000000);
}

int main(int argc, char** argv) {
 ::testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}

