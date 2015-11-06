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

// Reads file line by line, creating a new item from each line. Then writes out the receipt.
//   fileName: name of file to read from
//   itemFactory: creates items, knows about which item descriptions are in the lists of exemptions
//   os: where to write the output
bool ComputeTax(const string & fileName, const ItemFactory & itemFactory, ostream & os)
{
    bool success = true;
    
    Receipt receipt;

    ifstream infile(fileName);

    string line;
    while (std::getline(infile, line))
    {
        Item item;

        bool success = itemFactory.CreateItem(line, item);
        if (!success)
        {
            cerr << "Error reading line: \"line\"" << endl;
            return false;
        }
        receipt.AddItem(item);
    }
    receipt.Output(os);
    os << endl;
    return success;
}

int main()
{
    ItemFactory itemFactory(-1);

    itemFactory.AddFoodItem("chocolate bar");
    itemFactory.AddFoodItem("box of chocolates");
    itemFactory.AddBookItem("book");
    itemFactory.AddMedicalItem("packet of headache pills");

    ComputeTax("input1.txt", itemFactory, cout);
    ComputeTax("input2.txt", itemFactory, cout);
    ComputeTax("input3.txt", itemFactory, cout);

    return 0;
}
