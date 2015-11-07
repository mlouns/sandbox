// main.cpp
//
// Author: Michael Lounsbery
// Date: Nov 4, 2015

#include "item.h"
#include "receipt.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ostream;
using std::string;

using Store::Item;
using Store::ItemFactory;
using Store::Receipt;

int main()
{
    ItemFactory itemFactory(-1);

    itemFactory.AddFoodItem("chocolate bar");
    itemFactory.AddFoodItem("box of chocolates");
    itemFactory.AddBookItem("book");
    itemFactory.AddMedicalItem("packet of headache pills");

    Receipt receipt;

    receipt.ComputeTax("input1.txt", itemFactory, cout);
    receipt.ComputeTax("input2.txt", itemFactory, cout);
    receipt.ComputeTax("input3.txt", itemFactory, cout);

    return 0;
}
