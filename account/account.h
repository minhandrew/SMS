#pragma once

#include <iostream>
#include "..\constant\constant.h"
#include "..\format\format.h"

struct Account {
    char phone_number[MAX_CODE];
    char name[MAX_NAME];
    int numBought; // number of items bought
    struct itemsBought {
        char barcode[MAX_CODE];
        char name[MAX_NAME]; // the name of this item at the moment it was bought
        int num; // the number of this item bought
        double price; // the price of this item at the moment it was bought
    };
    itemsBought items[MAX_ITEM];

    Account(): numBought(0) {}
    void show(); // show all the information of this struct
    void input_phonenum(); // input the phone number of an account
};

#include "account.cpp"