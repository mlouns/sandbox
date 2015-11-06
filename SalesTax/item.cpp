// item.cpp
//
// Author: Michael Lounsbery
// Date: Nov 2, 2015

#include "item.h"

using std::ceil;
using std::cerr;
using std::endl;
using std::ostream;
using std::string;
using std::stringstream;
using std::vector;

using Store::Item;
using Store::ItemFactory;


namespace
{
    // Returns raw percentage of price, without rounding.
    //   price: amount to compute percentage on
    //   percent: percent to compute. 5.2% is represented as 5.2, not 0.052
    float RawPercentage(float price, float percent)
    {
        return price * percent / 100.0f;
    }

    // Returns value, rounded up to the nearest increment.
    //   value: base value to round from
    //   rounding: amount to round up to. If rounding up to nearest dime, set to 0.10
    float RoundUpToNearest(float value, float rounding)
    {
        int wholePart = value;
        float fractionalPart = value - wholePart;
        float roundingCount = ceil(fractionalPart / rounding);
        return wholePart + roundingCount * rounding;
    }

    // Returns percent of price, rounded up to nearest rounding factor.
    //   price: original price
    //   percent: percent of price to compute. 5.2% is represented as 5.2, not 0.052
    //   rounding: amount to round up to. If rounding up to nearest dime, set to 0.10
    float IncrementalPercentage(float price, float percent, float rounding)
    {
//        cerr << "<in inc:"
//             << " price=" << price
//             << " percent=" << percent
//             << " rounding=" << rounding
//             << " raw=" << RawPercentage(price, percent)
//             << ">" << endl;
        return RoundUpToNearest(RawPercentage(price, percent), rounding);
    }
} // anonymous namespace


const float Item::kDutyPercentage = 5.0f;
const float Item::kSalesTaxPercentage = 10.0f;
const float Item::kRoundingIncrement = 0.05f;

// Returns import duty to be charged on this item.
float Item::Duty() const
{
//    cerr << "<in Duty:"
//         << " import=" << (IsImport() ? "true" : "false")
//         << " base=" << BasePrice()
//         << " pct=" << IncrementalPercentage(BasePrice(), kDutyPercentage, kRoundingIncrement)
//         << ">" << endl;
    return IsImport() ? IncrementalPercentage(BasePrice(), kDutyPercentage, kRoundingIncrement) : 0.0f;
}


// Returns sales tax to be charged on this item.
float Item::SalesTax() const
{
    return IsExempt() ? 0.0f : IncrementalPercentage(BasePrice(), kSalesTaxPercentage, kRoundingIncrement);
}


// Prints out the item before tax is applied.
void Item::OutputPreTax(ostream & os) const
{
    os << std::setprecision(2) << std::fixed;
    os << Count()
       << (IsImport() ? " imported" : "")
       << " " << Name()
       << ": " << BasePrice();
}

// Prints out the item before tax is applied.
void Item::OutputWithTax(ostream & os) const
{
    os << std::setprecision(2) << std::fixed;
    os << Count()
       << (IsImport() ? " imported" : "")
       << " " << Name()
       << ": " << TotalPrice();
}


namespace
{
// Returns s, with leading and trailing spaces removed.
string TrimString(std::string & s)
{
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
    return s;
}

// Splits s into tokens, where space is the delimiter.
void SplitIntoTokens(const string & s, StringVector & tokens)
{
    tokens.clear();
    string tempBuffer;
    stringstream stream(s);

    while (stream >> tempBuffer)
    {
        tokens.push_back(tempBuffer);
    }
}

} // anonymous namespace


// Sets newItem to be a new item created from the new line of items.
// Returns success of the operation.
bool ItemFactory::CreateItem(const std::string & itemLine, Item & newItem)
{
    int itemCount = -1;
    string itemName = "";
    float itemPrice = 0.0f;
    bool isImported = false;
    bool success = ParseItemString(itemLine, itemCount, itemName, itemPrice, isImported);

    if (success)
    {
        bool isExempt = IsExempt(itemName);
        newItem = Item(itemCount, itemName, itemPrice, isExempt, isImported);
    }
    return success;
}


// Parses a line describing a sales item.
//   itemLine: the line to parse
//   itemCount: the count associated with the item, as given at the start of itemLine
//   itemName: the name of the item
//   itemPrice: the pre-tax price of the item
//   isImported: whether the item string says the item was imported
bool ItemFactory::ParseItemString(const string & itemLine, int & itemCount, string & itemName,
                                  float & itemPrice, bool & isImported)
{
    const string kImportString = "imported";

    bool success = true;
    string itemCopy = itemLine;
    itemCopy = TrimString(itemCopy);

    isImported = false;

    // Split itemCopy into tokens, where space is the delimiter
    StringVector itemTokens;
    SplitIntoTokens(itemCopy, itemTokens);
    size_t tokenCount = itemTokens.size();
    
    success = tokenCount >= 4;

    if (success)
    {
        // "at" should be the penultimate token
        string atString = itemTokens[tokenCount - 2];
        success = atString.compare("at") == 0;
        if (success)
        {
            try
            {
                // count is the first token
                string countString = itemTokens[0];
                itemCount = std::stoi(countString);

                // price is the last token
                string priceString = itemTokens[tokenCount - 1];
                itemPrice = std::stof(priceString);
            }
            catch (...)
            {
                // There was a problem converting a supposed number string to a number with stoi or stof
                success = false;
            }

            // concatenate the rest of the string into itemName
            itemName = "";
            for (int i = 1; success && (i < int(tokenCount - 2)); ++i)
            {
                if (itemTokens[i].compare(kImportString) == 0)
                {
                    // We found "imported" in the name
                    success = !isImported;              // we can't have "imported" appear twice
                    isImported = true;
                }
                else
                {
                    if (itemName.size() > 0)
                    {
                        // Put back spaces between tokens
                        itemName += " ";
                    }
                    itemName += itemTokens[i];
                }
            }
            success = success && (itemName.size() > 0);
        }
    }
    return success;
}
