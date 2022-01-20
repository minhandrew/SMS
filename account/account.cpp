#include "account.h"

using namespace std;

void Account::show()
{
    cout << "Customer's phone number: " << phone_number << endl;
    cout << "Customer's name: " << name << endl;
    cout << "Products that " << name << " has bought:" << endl;
    for(int i = 0; i < numBought; ++i) {
        cout << "Product " << i + 1 << ':' << endl;
        cout << "Barcode: " << items[i].barcode << endl;
        cout << "Name: " << items[i].name << endl;
        cout << "Number of items bought: " << items[i].num << endl;
        cout << "The price bought with: " << items[i].price << endl;
    }
}

void Account::input_phonenum()
{
    result res;
    do {
        cout << "Input account's phone number: ";
        res = read_code(phone_number, MAX_CODE);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again under " << MAX_CODE - 1 << " digits.\n";
        }
        else if(res == INVALID) {
            cout << "Invalid input. Please try again.\n";
        }
    } while(res != SUCCESSFUL);
}