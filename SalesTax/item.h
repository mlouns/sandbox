// item.h
//
// Author: Michael Lounsbery
// Date: Nov 2, 2015

#include "basics.h"

namespace Store
{

class Item
{
public:
    // ctor for Item.
    // basePrice: cost of the item, before tax
    // isExempt: true iff the item is tax-exempt
    // isImport: true iff the item is an import
    Item(int count, float basePrice, bool isExempt, bool isImport)
        : count_(count),
          basePrice_(basePrice),
          isExempt_(isExempt),
          isImport_(isImport)
        {
        }

    const float kDutyPercentage = 10.0f;
    const float kSalesTaxPercentage = 5.0f;
    const float kRoundingIncrement = 0.05;

    float Duty() const;          // Returns import duty for the item
    float SalesTax() const;      // Returns sales tax for the item
    float TotalPrice() const { return BasePrice() + Duty() + SalesTax(); }
    float BasePrice() const { return basePrice_; }

    int Count() const { return count_; }
    bool IsImport() const { return isImport; }
    bool IsExempt() const { return isExempt; }

protected:
    int count_;                  // Count for this item
    float basePrice_;            // Pre-tax price of the item
    bool isExempt_;              // True iff the item is tax-exempt
    bool isImport_;              // True iff the item is an import
};


std::ostream & operator<<(std::ostream & os, const Item & item);

typedef std::vector<Item> ItemVector;


class ItemFactory
{
public:
    ItemFactory();

public:
    bool CreateItem(const std::string & itemLine, Item & newItem);

    void AddMedicalItem(const std::string & itemString) { medicalItems.insert(itemString); }
    void AddFoodItem(const std::string & itemString) { foodItems.insert(itemString); }
    void AddBookItem(const std::string & itemString) { bookItems.insert(itemString); }

protected:
    Initialize();

    bool ParseItemString(const std::string & itemLine, int & itemCount, std::string & itemName,
                         float & itemPrice, bool & isImported);

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
