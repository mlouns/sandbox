#include "gtest/gtest.h"
#include "item.h"

using Store::Item;
using Store::ItemFactory;

// Simple test for initializing an Item.
TEST(Item, Init)
{
//    Item item0;
    
    Item item(4, 1.20, false, true);

    EXPECT_EQ(4, item.Count());
    EXPECT_FLOAT_EQ(1.2, item.BasePrice());
    EXPECT_FALSE(item.IsExempt());
    EXPECT_TRUE(item.IsImport());
}



// Test adding special items to a factory.
TEST(ItemFactory, AddSpecialItems)
{
    ItemFactory itemFactory(-1);

    EXPECT_FALSE(itemFactory.IsMedicalItem("box of aspirin"));

    itemFactory.AddMedicalItem("box of aspirin");

    EXPECT_TRUE(itemFactory.IsMedicalItem("box of aspirin"));

    itemFactory.AddMedicalItem("snake oil");
    itemFactory.AddMedicalItem("hair of the dog");

    EXPECT_TRUE(itemFactory.IsMedicalItem("snake oil"));
    EXPECT_TRUE(itemFactory.IsMedicalItem("hair of the dog"));
    EXPECT_FALSE(itemFactory.IsMedicalItem("box of sleeping pills"));
}
