#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "..\format\format.h"
#include "..\item\item.h"
#include "..\constant\constant.h"
#include "..\account\account.h"
#include "..\discount\discount.h"

using namespace std;

struct Shop {
    double totalCost; // the total cost of all products
    double totalRevenue; // the total revenue of selling
    int totalSales; // the total items sold

    int numItems;
    Item itemsList[MAX_ITEM];
    int numAccounts;
    Account accountsList[MAX_ACCOUNT];
    int numDisc;
    Discount discList[MAX_DISC];

    Shop(): totalCost(0.0), totalRevenue(0.0), totalSales(0), numItems(0), numAccounts(0), numDisc(0) {}
    void show(); // show all the present data of the shop
    void read_input(ifstream &); // first, the program reads data from the text file via this procedure
    void save_output(ofstream &); // to save the current status of all items and accounts to the text file

    int find_item(const char[]); // to find the position of a specific item in itemsList, -1 if not found.
    void add_item(); // to add a new item to itemsList
    void edit_item(); // to edit an existing item in itemsList
    void remove_item(); // to remove an existing item from itemsList

    int find_discount(const int &); // to find the position of a specific discount in discList via its money spent, -1 if not found.
    void set_discount(); // to set up a new discount
    void edit_discount(); // to edit an existing discount
    void remove_discount(); // to remove an existing discount
    void applyDiscount(double &); // to apply a specific discount to the given price
    
    int find_account(const char[]); // to find the position of a specific account in accountsList, -1 if not found.
    void sell(); // to sell items chosen by the customer
    void remove_account(); // to remove an existing account in the system.
    void check_profit(); // to check the current profit the shop has attained.
};
Shop myShop; // main variable to manipulate the shop's activities.

#include "shop.cpp"