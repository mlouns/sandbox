# Sales Tax

## Introduction

The code simulates computing sales tax and import duty on a series of purchased items.

## Classes

All classes and their interfaces are described in the `item.h` and `receipt.h` files.

`Item`: models a single item on a receipt.

`ItemFactory`: Creates items from a string describing the item.

`Receipt`: Tallies up the tax for all the items and prints information about all of it.


## How to use

The code is run from a C++ main() routine, as illustrated in `tax.cpp`. The important steps are to:

* Declare an ImportFactory object.
* Use that object to enter the names of tax-exempt items.
* Call ComputeTax for one or more input files. The parameters to ComputeTax are described in `receipt.h`.
