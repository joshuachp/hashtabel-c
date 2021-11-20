#include <gtest/gtest.h>

extern "C" {
#include "hashtable.h"
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    ASSERT_EQ(0, hashtable());
}
