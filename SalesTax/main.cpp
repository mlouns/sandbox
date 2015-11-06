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

bool ComputeTax(const string & fileName, ostream & os)
{
    bool success = true;
    
    ItemFactory itemFactory(-1);

    itemFactory.AddFoodItem("chocolate bar");
    itemFactory.AddFoodItem("box of chocolates");
    itemFactory.AddBookItem("book");
    itemFactory.AddMedicalItem("packet of headache pills");

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
    ComputeTax("input1.txt", cout);
    ComputeTax("input2.txt", cout);
    ComputeTax("input3.txt", cout);

    return 0;
}
