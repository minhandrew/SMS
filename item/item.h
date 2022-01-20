#pragma once

#include <iostream>
#include "..\constant\constant.h"
#include "..\format\format.h"

struct Item {
    char barcode[MAX_CODE];
    char name[MAX_NAME];
    int stock;
    double cost;
    double price;

    void show(); // show all the information of this struct
    void input_barcode(); // input the barcode for an item
};

#include "item.cpp"