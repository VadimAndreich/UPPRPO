#include "gtest/gtest.h"
#include "CB.cpp"


TEST(Lab_1_Tests, Push_back_frontCheck) {
    CircularBuffer<int> buf(12);
    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_front(4);
    EXPECT_EQ(buf.capacity() - buf.size(), 8);
}


TEST(Lab_1_Tests, PushfrontCheck) {
    CircularBuffer<double> buf(2);
    buf.push_back(1);
    buf.push_back(3.97);
    buf.push_front(-4.6);
    EXPECT_EQ(buf.front(), -4.6);
}


TEST(Lab_1_Tests, SwapCheck) {
    CircularBuffer<int> a(1, 3);
    CircularBuffer<int> &b(a);
    CircularBuffer<int> c(1, 3);

    c.swap(a);
    EXPECT_TRUE(a == b);
}


TEST(Lab_1_Tests, EmptyCheck) {
    CircularBuffer<int> a(10);
    CircularBuffer<int> b(10, 3);
    EXPECT_EQ(a.empty(), !b.empty());
}


TEST(Lab_1_Tests, AssignmentCheck) {
    CircularBuffer<int> a(12, 5);
//    CircularBuffer<int> b;
    CircularBuffer<int> c;
    c = a;
    const CircularBuffer<int>& b(a);
//    b = std::move(a);
    EXPECT_TRUE(c == b);
}

