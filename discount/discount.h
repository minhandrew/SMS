#pragma once

#include <iostream>
#include "..\format\format.h"

struct Discount {
    int spend; // the minimum amount of money purchased, usually as an integer
    int perc; // discount percentage (%)

    void show(); // show all the information of this struct
    void input_spend(); // input the spend of a discount
};

#include "discount.cpp"