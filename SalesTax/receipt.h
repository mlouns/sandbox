// receipt.h
//
// Author: Michael Lounsbery
// Date: Nov 2, 2015

#include "basics.h"
#include "item.h"

#ifndef RECEIPT_H

#define RECEIPT_H

namespace Store
{

class Receipt
{
public:
    // Adds an item to the Receipt
    void AddItem(const Store::Item & item) { itemVector_.push_back(item); }

    void OutputTaxedItems(std::ostream & os) const;                             // Outputs all taxed items to os
    void OutputComplete(std::ostream & os) const;                               // Outputs a complete receipt

    const Item & ItemAt(size_t i) const { return itemVector_[i]; }              // Returns item i in the receipt

    float TotalBasePrice() const;          // total price of all items, before tax and import duty
    float TotalDuty() const;               // total import duty on all items
    float TotalCombinedTax() const;        // total sales tax plus duty on all items
    float TotalCost() const { return TotalBasePrice() + TotalCombinedTax(); }   // Total cost of everything
    size_t ItemCount() const { return itemVector_.size(); }                     // How many items we have

private:
    ItemVector itemVector_;                // list of all items on the receipt
};

} // namespace Store

#endif // RECEIPT_H
