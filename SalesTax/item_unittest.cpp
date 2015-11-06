#include "gtest/gtest.h"
#include "item.h"

using std::string;

using Store::Item;
using Store::ItemFactory;

// Simple test for initializing an Item.
TEST(Item, Init)
{
    Item item(4, string("sardines"), 1.20, false, true);

    EXPECT_EQ(4, item.Count());
    EXPECT_STREQ("sardines", item.Name().c_str());
    EXPECT_FLOAT_EQ(1.2, item.BasePrice());
    EXPECT_FALSE(item.IsExempt());
    EXPECT_TRUE(item.IsImport());
}

// Test sales tax calculation on simple items

TEST(Item, CalculateTax_01)
{
    // Sales tax on a 1-cent gumball is 5 cents, since we round up
    bool isExempt = false;
    bool isImported = false;
    Item item(1, string("gumball"), 0.01, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.05, item.SalesTax());
}

TEST(Item, CalculateTax_02)
{
    // Sales tax on a 1-dollar item is a simple 10 cents
    bool isExempt = false;
    bool isImported = false;
    Item item(4, string("sardines"), 1.0, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.10, item.SalesTax());
}

TEST(Item, CalculateTax_03)
{
    // Sales tax on a $1.20 item is 15 cents: 12 cents rounded up
    bool isExempt = false;
    bool isImported = false;
    Item item(4, string("sardines"), 1.20, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.15, item.SalesTax());
}

TEST(Item, CalculateTax_04)
{
    // Sales tax on a free item is nothing.
    bool isExempt = false;
    bool isImported = false;
    Item item(5, string("breath of air"), 0.0, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.0, item.SalesTax());
}


// Calculate tax on exempt items

TEST(Item, CalculateExemptTax_01)
{
    // Sales tax on a 1-cent gumball is 0 cents, since it's exempt
    bool isExempt = true;
    bool isImported = false;
    Item item(1, string("gumball"), 0.01, isExempt, isImported);

    EXPECT_TRUE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.0, item.SalesTax());
}

TEST(Item, CalculateExemptTax_02)
{
    // Sales tax on a 1-dollar exempt item is still 0
    bool isExempt = true;
    bool isImported = false;
    Item item(4, string("sardines"), 1.0, isExempt, isImported);

    EXPECT_TRUE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.0, item.SalesTax());
}


// Calculate duty on various items.

TEST(Item, CalculateDuty_01)
{
    // Duty on a non-import 1-cent gumball is nothing
    bool isExempt = false;
    bool isImported = false;
    Item item(1, string("gumball"), 0.01, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.0, item.Duty());
}

TEST(Item, CalculateDuty_02)
{
    // Duty on an imported 1-cent gumball is 5 cents, since we round up
    bool isExempt = false;
    bool isImported = true;
    Item item(1, string("gumball"), 0.01, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_TRUE(item.IsImport());

    EXPECT_FLOAT_EQ(0.05, item.Duty());
}

TEST(Item, CalculateDuty_03)
{
    // Duty on a 1-dollar non-imported item is nothing
    bool isExempt = false;
    bool isImported = false;
    Item item(4, string("sardines"), 1.0, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_FALSE(item.IsImport());

    EXPECT_FLOAT_EQ(0.0, item.Duty());
}

TEST(Item, CalculateDuty_04)
{
    // Duty on a 1-dollar imported item is a clean nickel
    bool isExempt = false;
    bool isImported = true;
    Item item(4, string("sardines"), 1.0, isExempt, isImported);

    EXPECT_FALSE(item.IsExempt());
    EXPECT_TRUE(item.IsImport());

    EXPECT_FLOAT_EQ(0.05, item.Duty());
}

TEST(Item, CalculateDuty_05)
{
    // Being tax-exempt shouldn't change the result of the previous test
    bool isExempt = true;
    bool isImported = true;
    Item item(4, string("sardines"), 1.0, isExempt, isImported);

    EXPECT_TRUE(item.IsExempt());
    EXPECT_TRUE(item.IsImport());

    EXPECT_FLOAT_EQ(0.05, item.Duty());
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
