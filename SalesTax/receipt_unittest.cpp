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

    EXPECT_NEAR(1.5, receipt.TotalCombinedTax(), 0.0001);
    EXPECT_NEAR(29.83, receipt.TotalCost(), 0.0001);

    receipt.OutputComplete(cerr);
}


// Tests spec example 2
TEST(Receipt, Spec_02)
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
    
    success = itemFactory.CreateItem("1 imported box of chocolates at 10.00", item);
    receipt.AddItem(item);
    success = itemFactory.CreateItem("1 imported bottle of perfume at 47.50", item);
    receipt.AddItem(item);

    EXPECT_NEAR(7.65, receipt.TotalCombinedTax(), 0.0001);
    EXPECT_NEAR(65.15, receipt.TotalCost(), 0.0001);

    receipt.OutputComplete(cerr);
}


// Tests spec example 3
TEST(Receipt, Spec_03)
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
    
    success = itemFactory.CreateItem("1 imported bottle of perfume at 27.99", item);
    receipt.AddItem(item);
    success = itemFactory.CreateItem("1 bottle of perfume at 18.99", item);
    receipt.AddItem(item);
    success = itemFactory.CreateItem("1 packet of headache pills at 9.75", item);
    receipt.AddItem(item);
    success = itemFactory.CreateItem("1 box of imported chocolates at 11.25", item);
    receipt.AddItem(item);

    EXPECT_NEAR(6.70, receipt.TotalCombinedTax(), 0.0001);
    EXPECT_NEAR(74.68, receipt.TotalCost(), 0.0001);

    receipt.OutputComplete(cerr);
}
