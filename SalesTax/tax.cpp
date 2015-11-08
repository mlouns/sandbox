// main.cpp
//
// Author: Michael Lounsbery
// Date: Nov 4, 2015

#include "item.h"
#include "receipt.h"

using std::cout;

using Store::ItemFactory;
using Store::Receipt;

int main()
{
    ItemFactory itemFactory(1);

    itemFactory.AddFoodItem("chocolate bar");
    itemFactory.AddFoodItem("box of chocolates");
    itemFactory.AddBookItem("book");
    itemFactory.AddMedicalItem("packet of headache pills");

    {
        Receipt receipt;
        receipt.ComputeTax("input1.txt", itemFactory, cout);
    }
    {
        Receipt receipt;
        receipt.ComputeTax("input2.txt", itemFactory, cout);
    }
    {
        Receipt receipt;
        receipt.ComputeTax("input3.txt", itemFactory, cout);
    }
    return 0;
}
