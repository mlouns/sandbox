// test.cpp
//
// Author: Michael Lounsbery
// Date: Nov 4, 2015

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


// Outputs to os all items with their taxes.
void Receipt::OutputTaxedItems(std::ostream & os) const
{
    for (auto item : itemVector_)
    {
        item.OutputWithTax(os);
        os << endl;
    }
}


// Outputs to os all items with their taxes.
void Receipt::OutputComplete(std::ostream & os) const
{
    OutputTaxedItems(os);

    os << endl;
    os << "Sales Taxes: " << TotalCombinedTax() << endl;
    os << "Total: " << TotalCost() << endl;
}


// Outputs to os all items with their taxes.
float Receipt::TotalBasePrice() const
{
    float result = 0.0f;
    for (auto item : itemVector_)
    {
        result += item.BasePrice();
    }
    return result;
}


// Outputs to os all items with their taxes.
float Receipt::TotalDuty() const
{
    float result = 0.0f;
    for (auto item : itemVector_)
    {
        result += item.Duty();
    }
    return result;
}


// Outputs to os all items with their taxes.
float Receipt::TotalCombinedTax() const
{
    float result = 0.0f;
    for (auto item : itemVector_)
    {
        result += item.CombinedTax();
    }
    return result;
}

// Reads file line by line, creating a new item from each line. Then writes out the receipt.
//   fileName: name of file to read from
//   itemFactory: creates items, knows about which item descriptions are in the lists of exemptions
//   os: where to write the output
bool Receipt::ComputeTax(const string & fileName, const ItemFactory & itemFactory, ostream & os)
{
    bool success = true;
    
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
        AddItem(item);
    }
    OutputComplete(os);
    os << endl;
    return success;
}
