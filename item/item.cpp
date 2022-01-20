#include "item.h"

using namespace std;

void Item::show()
{
    cout << "Product's barcode: " << barcode << endl;
    cout << "Product's name: " << name << endl;
    cout << "Product's stock: " << stock << endl;
    cout << "Product's cost: " << cost << endl;
    cout << "Product's price: " << price << endl;
}

void Item::input_barcode()
{
    result res;
    // read barcode
    do {
        cout << "Item's barcode: ";
        res = read_code(barcode, MAX_CODE);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again under " << MAX_CODE - 1 << " digits.\n";
        }
        else if(res == INVALID) {
            cout << "Invalid input. Please try again with only digits.\n";
        }
    } while(res != SUCCESSFUL);
}