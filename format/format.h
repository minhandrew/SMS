// Implementations of functions for checking the validity of data inputted from the user.

#pragma once

#include <iostream>
#include <cstring>
#include <cassert>
#include "..\constant\constant.h"

void reverseStr(char[]); // reverse a given string

enum result {
    SUCCESSFUL,
    EMPTY,
    EXCESSIVE,
    INVALID
};

/*
read_code(): Input a barcode or a phone number (containing only digits) on a line with a certain number of characters. Return:
SUCCESSFUL: if barcode or phone number is read successfully (that contains only digits).
EMPTY: if an empty line is read. String of null is returned.
EXCESSIVE: if the number of characters inputted exceeds the limit allowed. String of null is returned.
INVALID: if contain characters other than digits. String of null is returned.
*/
result read_code(char[], const int &);

/*
read_name(): Input a command or a name on a line with a certain number of characters. Return:
SUCCESSFUL: if the command or name is read successfully.
EMPTY: if an empty line is read. String of null is returned.
EXCESSIVE: if the number of characters inputted exceeds the limit allowed. String of null is returned.
*/
result read_name(char[], const int &);

/*
read_char(): Input a choice of 'Y' (yes) or 'N' (no). Return:
SUCCESSFUL: If the character inputted is valid.
EMPTY: If no character was inputted at all. A null character is returned.
EXCESSIVE: If too many character were inputted. A null character is returned.
INVALID: If the character inputted is invalid. A null character is returned.
*/
result read_char(char &);

/*
read_double(): Input a real number and return:
SUCCESSFUL: If the number inputted is in valid format and contains <= 15 significant figures.
EMPTY: If nothing was inputted. A value of -1.0 is returned.
EXCESSIVE: If too many characters were inputted. A value of -1.0 is returned.
INVALID: If the number inputted is in the wrong format or contains more than 15 significant figures or has more than MAX_DECIMAL
    decimal places. A value of -1.0 is returned.
In addition, the number of digits found after the decimal point would also be returned.

Note that leading and trailing zeroes will be eliminated appropriately.
*/
result read_double(double &);

/*
read_pos_int(): Input an 32-bit positive integer and return:
SUCCESSFUL: If the number inputted is valid and in int's range.
EMPTY: If nothing was inputted. A value of -1 is returned.
EXCESSIVE: If too many characters were inputted. A value of -1 is returned.
INVALID: If the number inputted is out of int's range or negative or contains invalid characters.
*/
result read_pos_int(int &);

#include "format.cpp"