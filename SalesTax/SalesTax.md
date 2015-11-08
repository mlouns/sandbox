# Sales Tax

## Introduction

The code simulates computing sales tax and import duty on a series of purchased items.

## Classes

All classes and their interfaces are described in the `item.h` and `receipt.h` files.

`Item`: models a single item on a receipt.

`ItemFactory`: Creates items from a string describing the item.

`Receipt`: Tallies up the tax for all the items and prints information about all of it.


## Unit tests

Test files are in the SalesTax/utest directory.

## How to use

The code is run from a C++ main() routine, as illustrated in `tax.cpp`. The important steps are to:

* Declare an ImportFactory object.
* Use that object to enter the names of tax-exempt items.
* Declare a Receipt object to compute all the tax on.
* Call Receipt::ComputeTax() for an input file. The parameters to ComputeTax are described in `receipt.h`.

## Example output

For the input in `tax.cpp`, the following output is printed:

    1 book: 12.49
    1 music CD: 16.49
    1 chocolate bar: 0.85

    Sales Taxes: 1.50
    Total: 29.83

    1 imported box of chocolates: 10.50
    1 imported bottle of perfume: 54.65

    Sales Taxes: 7.65
    Total: 65.15

    1 imported bottle of perfume: 32.19
    1 bottle of perfume: 20.89
    1 packet of headache pills: 9.75
    1 imported box of chocolates: 11.85

    Sales Taxes: 6.70
    Total: 74.68