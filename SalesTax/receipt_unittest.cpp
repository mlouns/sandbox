#include "gtest/gtest.h"
#include "receipt.h"

using std::cerr;
using std::endl;
using std::string;

using Store::Item;
using Store::ItemFactory;
using Store::Receipt;


// Simple test for initializing a Recipt.
TEST(Receipt, Init)
{
    Receipt receipt;

    EXPECT_EQ(0, receipt.ItemCount());
}


// Tests spec example 1
TEST(Receipt, Spec_01)
{
    Receipt receipt;

    // Test case 1 from the spec
    ItemFactory itemFactory(-1);

    itemFactory.AddFoodItem("chocolate bar");
    itemFactory.AddFoodItem("box of chocolates");
    itemFactory.AddBookItem("book");
    itemFactory.AddMedicalItem("packet of headache pills");

    bool success = false;
    Item item;
    
    success = itemFactory.CreateItem("1 book at 12.49", item);
    receipt.AddItem(item);
    success = itemFactory.CreateItem("1 music CD at 14.99", item);
    receipt.AddItem(item);
    success = itemFactory.CreateItem("1 chocolate bar at 0.85", item);
    receipt.AddItem(item);

    EXPECT_EQ(1.5, receipt.TotalSalesTax());
    EXPECT_NEAR(29.83, receipt.TotalCost(), 0.0001);
}
