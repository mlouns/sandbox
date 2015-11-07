// test.cpp
//
// Author: Michael Lounsbery
// Date: Nov 4, 2015

#include "receipt.h"

using std::endl;

using Store::Item;
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
