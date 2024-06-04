#include <gtest/gtest.h>
#include "lib.h"

TEST(MyTestSuite, Test1) {
    int a = my_sum(12, 5);
    EXPECT_EQ(a, 17);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
