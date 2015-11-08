// item.h
//
// Author: Michael Lounsbery
// Date: Nov 2, 2015

#include "basics.h"

#ifndef ITEM_H

#define ITEM_H

namespace Store
{

// Item represents a single item on the receipt
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

    static const float kDutyPercentage;                               // The percent tax for imports
    static const float kSalesTaxPercentage;                           // The percent tax for sales tax
    static const float kRoundingIncrement;                            // How big a chunk we round tax up to

    float BasePrice() const { return basePrice_; }                    // Base price of the item, before tax
    float Duty() const;                                               // Returns import duty for the item
    float SalesTax() const;                                           // Returns sales tax for the item
    float TotalPrice() const { return BasePrice() + CombinedTax(); }  // Returns total price of item plus all tax
    float CombinedTax() const { return Duty() + SalesTax(); }         // Returns sales tax plus import duty

    int Count() const { return count_; }                              // how many of this item are there
    std::string Name() const { return name_; }                        // name field of the item
    bool IsExempt() const { return isExempt_; }                       // true iff this item is tax-exempt
    bool IsImport() const { return isImport_; }                       // true iff this item is an import

    void OutputPreTax(std::ostream & os) const;                       // Writes out the item to os, pre-tax
    void OutputWithTax(std::ostream & os) const;                      // Writes out the item, post-tax

protected:
    int count_;                                                       // Count field for this item
    std::string name_;                                                // Name of this item
    float basePrice_;                                                 // Pre-tax price of the item
    bool isExempt_;                                                   // True iff the item is tax-exempt
    bool isImport_;                                                   // True iff the item is an import
};


typedef std::vector<Store::Item> ItemVector;


// ItemFactory creates an Item from a string description of the item
class ItemFactory
{
public:
ItemFactory(int id) : id_(id) { }

    // Sets newItem to be a new Item, matching the description in itemLine.
    //   Returns true iff we successfully parsed itemLine
    bool CreateItem(const std::string & itemLine, Item & newItem) const;

    // Adds names of items to various sets of tax-exempt data
    void AddMedicalItem(const std::string & itemString) { medicalItems_.insert(itemString); }
    void AddFoodItem(const std::string & itemString) { foodItems_.insert(itemString); }
    void AddBookItem(const std::string & itemString) { bookItems_.insert(itemString); }

protected:
    void Initialize();

    // Parses an input line into various components we need for creating the Item
    bool ParseItemString(const std::string & itemLine, int & itemCount, std::string & itemName,
                         float & itemPrice, bool & isImported) const;

    // Tests for whether the given itemName is in our sets of exempt items
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

    // Catch-all test for whether an item is tax-exempt
    bool IsExempt(const std::string & itemName) const
    {
        return IsMedicalItem(itemName) || IsFoodItem(itemName) || IsBookItem(itemName);
    }

protected:
    std::set<std::string> medicalItems_;           // Set of tax-exempt medical items
    std::set<std::string> foodItems_;              // Set of tax-exempt food items
    std::set<std::string> bookItems_;              // Set of tax-exempt book items

    int id_;                                       // is for this ItemFactory
};

} // namespace Store

#endif // ITEM_H
