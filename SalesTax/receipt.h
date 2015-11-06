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
    void AddItem(const Store::Item & item) { itemVector_.push_back(item); }

    void OutputTaxedItems(std::ostream & os) const;
    void Output(std::ostream & os) const;

    const Item & ItemAt(size_t i) const { return itemVector_[i]; }

    float TotalBasePrice() const;          // total price of all items, before tax and import duty
    float TotalDuty() const;               // total import duty on all items
    float TotalSalesTax() const;           // total sales tax on all items
    float TotalCost() const { return TotalBasePrice() + TotalDuty() + TotalSalesTax(); }
    size_t ItemCount() const { return itemVector_.size(); }

private:
    ItemVector itemVector_;                // list of all items on the receipt
};

std::ostream & operator<<(std::ostream & os, const Receipt & receipt);

} // namespace Store

#endif // RECEIPT_H
