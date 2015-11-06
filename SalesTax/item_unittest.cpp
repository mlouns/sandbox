#include "gtest/gtest.h"
#include "item.h"

using Store::Item;

// Simple test for initializing item.
TEST(Item, Init) {
    Item item(4, 1.20, false, true);

    EXPECT_EQ(4, item.Count());
    EXPECT_FLOAT_EQ(1.2, item.BasePrice());
    EXPECT_FALSE(item.IsExempt());
    EXPECT_TRUE(item.IsImport());
}
