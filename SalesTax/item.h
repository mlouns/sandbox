// item.h
//
// Author: Michael Lounsbery
// Date: Nov 2, 2015

#include "basics.h"

#ifndef ITEM_H

#define ITEM_H

namespace Store
{
class Item
{
public:
    // ctor for Item.
    // basePrice: cost of the item, before tax
    // isExempt: true iff the item is tax-exempt
    // isImport: true iff the item is an import
    Item(int count, const std::string & name, float basePrice, bool isExempt, bool isImport)
        : count_(count),
          name_(name),
          basePrice_(basePrice),
          isExempt_(isExempt),
          isImport_(isImport)
        { }

    Item() {}

    static const float kDutyPercentage;
    static const float kSalesTaxPercentage;
    static const float kRoundingIncrement;

    float BasePrice() const { return basePrice_; }
    float Duty() const;          // Returns import duty for the item
    float SalesTax() const;      // Returns sales tax for the item
    float TotalPrice() const { return BasePrice() + CombinedTax(); }
    float CombinedTax() const { return Duty() + SalesTax(); }

    int Count() const { return count_; }
    std::string Name() const { return name_; }
    bool IsExempt() const { return isExempt_; }
    bool IsImport() const { return isImport_; }

    void OutputPreTax(std::ostream & os) const;
    void OutputWithTax(std::ostream & os) const;

protected:
    int count_;                  // Count for this item
    std::string name_;           // Name of this item
    float basePrice_;            // Pre-tax price of the item
    bool isExempt_;              // True iff the item is tax-exempt
    bool isImport_;              // True iff the item is an import
};


//std::ostream & operator<<(std::ostream & os, const Item & item);

typedef std::vector<Store::Item> ItemVector;


class ItemFactory
{
public:
    ItemFactory(int size) { }

    bool CreateItem(const std::string & itemLine, Item & newItem) const;

    void AddMedicalItem(const std::string & itemString) { medicalItems_.insert(itemString); }
    void AddFoodItem(const std::string & itemString) { foodItems_.insert(itemString); }
    void AddBookItem(const std::string & itemString) { bookItems_.insert(itemString); }

//protected:
    void Initialize();

    bool ParseItemString(const std::string & itemLine, int & itemCount, std::string & itemName,
                         float & itemPrice, bool & isImported) const;

    bool IsMedicalItem(const std::string & itemName) const
    {
        return medicalItems_.find(itemName) != medicalItems_.end();
    }
    bool IsFoodItem(const std::string & itemName) const
    {
        return foodItems_.find(itemName) != foodItems_.end();
    }
    bool IsBookItem(const std::string & itemName) const
    {
        return bookItems_.find(itemName) != bookItems_.end();
    }
    bool IsExempt(const std::string & itemName) const
    {
        return IsMedicalItem(itemName) || IsFoodItem(itemName) || IsBookItem(itemName);
    }

protected:
    std::set<std::string> medicalItems_;
    std::set<std::string> foodItems_;
    std::set<std::string> bookItems_;
};

} // namespace Store

#endif // ITEM_H
