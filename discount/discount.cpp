#include "discount.h"

void Discount::show()
{
    cout << "Discount's spend: " << spend << endl;
    cout << "Discount's percentage: " << perc << endl;
}

void Discount::input_spend()
{
    result res;
    do {
        cout << "Input the spend (integer): ";
        res = read_pos_int(spend);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Invalid number. Please try again.\n";
        }
    } while(res != SUCCESSFUL);
}