#include "shop.h"

using namespace std;

void Shop::read_input(ifstream &inp)
{
    /*
    This input file is supposed to be read-only, meaning all the parameters should be valid.
    Therefore, no checking is needed.

    Expected format:
    totalCost
    totalRevenue
    totalSales

    N
    Item1
    Item2
    ...
    ItemN

    M
    Account1
    Account2
    ...
    AccountM

    K
    Discount1
    Discount2
    ...
    DiscountK
    */
    inp >> totalCost >> totalRevenue >> totalSales;
    inp >> numItems;
    for(int i = 0; i < numItems; ++i) {
        inp >> itemsList[i].barcode;
        inp.get(); // get rid of the newline character
        inp.get(itemsList[i].name, MAX_NAME);
        inp >> itemsList[i].stock;
        inp >> itemsList[i].cost;
        inp >> itemsList[i].price;
    }
    inp >> numAccounts;
    for(int i = 0; i < numAccounts; ++i) {
        inp >> accountsList[i].phone_number;
        inp.get(); // get rid of the newline character
        inp.get(accountsList[i].name, MAX_NAME);
        inp >> accountsList[i].numBought;
        for(int j = 0; j < accountsList[i].numBought; ++j) {
            inp >> accountsList[i].items[j].barcode;
            inp.get();
            inp.get(accountsList[i].items[j].name, MAX_NAME);
            inp >> accountsList[i].items[j].num;
            inp >> accountsList[i].items[j].price;
        }
    }
    inp >> numDisc;
    for(int i = 0; i < numDisc; ++i) {
        inp >> discList[i].spend;
        inp >> discList[i].perc;
    }
}

void Shop::show()
{
    cout << "The total cost of all products is: " << totalCost << endl;
    cout << "The total revenue of selling is: " << totalRevenue << endl;
    cout << "The total sales is: " << totalSales << endl;

    cout << endl;
    cout << "There are " << numItems << " products on sale." << endl;
    for(int i = 0; i < numItems; ++i) {
        cout << "Product " << i + 1 << ':' << endl;
        itemsList[i].show();
    }

    cout << endl;
    cout << "There are " << numAccounts << " accounts signed up." << endl;
    for(int i = 0; i < numAccounts; ++i) {
        cout << "Account " << i + 1 << ':' << endl;
        accountsList[i].show();
    }

    cout << endl;
    cout << "There are " << numDisc << " discounts available." << endl;
    for(int i = 0; i < numDisc; ++i) {
        cout << "Discount " << i + 1 << ':' << endl;
        discList[i].show();
    }
}

int Shop::find_item(const char bc[])
{
    for(int i = 0; i < numItems; ++i) {
        if(strcmp(itemsList[i].barcode, bc) == 0)
            return i;
    }
    return -1;
}

void Shop::add_item()
{
    if(numItems == MAX_ITEM) {
        cout << "The number of products exceeds the maximum allowed. Please consider removing some." << endl;
        return;
    }

    Item cur;
    cur.input_barcode();
    if(find_item(cur.barcode) != -1) {
        cout << "This item has already been inserted, please consider editing it instead." << endl;
        return;
    }

    result res;
    // read item's name
    do {
        cout << "Item's name: ";
        res = read_name(cur.name, MAX_NAME);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again under " << MAX_NAME - 1 << " characters.\n";
        }
    } while(res != SUCCESSFUL);
    // read product's stock
    do {
        cout << "Number of copies (stock): ";
        res = read_pos_int(cur.stock);
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
    // read product's cost
    do {
        cout << "Item's cost: ";
        res = read_pos_double(cur.cost);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Errors. Make sure that the input contains valid characters, no more than " << MAX_DECIMAL << " digits"
                    " after the decimap point, no more than 15 significant digits, and the number is positive.\n";
        }
    } while(res != SUCCESSFUL);
    totalCost += cur.cost * cur.stock;
    // read item's price
    do {
        cout << "Item's price: ";
        res = read_pos_double(cur.price);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Errors. Make sure that the input contains valid characters, no more than " << MAX_DECIMAL << " digits"
                    " after the decimap point, no more than 15 significant digits, and the number is positive.\n";
        }
    } while(res != SUCCESSFUL);

    itemsList[numItems++] = cur;
    cout << "Product has been added successfully." << endl;
}

void Shop::edit_item()
{
    Item cur;
    cur.input_barcode();
    int pos = find_item(cur.barcode);
    if(pos == -1) {
        cout << "This item does not exist, please consider inserting it first." << endl;
        return;
    }

    result res;
    // read item's name
    do {
        cout << "Item's new name (hit Enter to keep the old name): ";
        res = read_name(cur.name, MAX_NAME);
        if(res == EMPTY) {
            strcpy(cur.name, itemsList[pos].name);
            res = SUCCESSFUL;
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again under " << MAX_NAME - 1 << " characters.\n";
        }
    } while(res != SUCCESSFUL);
    strcpy(itemsList[pos].name, cur.name);

    // read product's stock
    do {
        cout << "Item's new stock (hit Enter to keep the old stock): ";
        res = read_pos_int(cur.stock);
        if(res == EMPTY) {
            cur.stock = itemsList[pos].stock;    
            res = SUCCESSFUL;
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Invalid number. Please try again.\n";
        }
    } while(res != SUCCESSFUL);
    totalCost -= (itemsList[pos].stock - cur.stock) * itemsList[pos].cost;
    itemsList[pos].stock = cur.stock;

    // read product's cost
    do {
        cout << "Item's new cost (hit Enter to keep the old cost): ";
        res = read_pos_double(cur.cost);
        if(res == EMPTY) {
            cur.cost = itemsList[pos].cost;
            res = SUCCESSFUL;
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Errors. Make sure that the input contains valid characters, no more than " << MAX_DECIMAL << " digits"
                    " after the decimap point, no more than 15 significant digits, and the number is positive.\n";
        }
    } while(res != SUCCESSFUL);
    // update the totalCost based on the new cost of the product
    totalCost -= itemsList[pos].stock * (itemsList[pos].cost - cur.cost);
    itemsList[pos].cost = cur.cost;
    
    // read item's price
    do {
        cout << "Item's new price (hit Enter to keep the old price): ";
        res = read_pos_double(cur.price);
        if(res == EMPTY) {
            cur.price = itemsList[pos].price;
            res = SUCCESSFUL;
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Errors. Make sure that the input contains valid characters, no more than " << MAX_DECIMAL << " digits"
                    " after the decimap point, no more than 15 significant digits, and the number is positive.\n";
        }
    } while(res != SUCCESSFUL);
    itemsList[pos].price = cur.price;

    cout << "Product has been edited successfully." << endl;
}

void Shop::save_output(ofstream &out)
{
    /*
    Expected format:
    totalCost
    totalRevenue
    totalSales

    N
    Item1
    Item2
    ...
    ItemN

    M
    Account1
    Account2
    ...
    AccountM

    K
    Discount1
    Discount2
    ...
    DiscountK
    */
    out << totalCost << endl << totalRevenue << endl << totalSales << endl;
    out << numItems << endl;
    for(int i = 0; i < numItems; ++i) {
        out << itemsList[i].barcode << endl;
        out << itemsList[i].name << endl;
        out << itemsList[i].stock << endl;
        out << itemsList[i].cost << endl;
        out << itemsList[i].price << endl;
    }
    out << numAccounts << endl;
    for(int i = 0; i < numAccounts; ++i) {
        out << accountsList[i].phone_number << endl;
        out << accountsList[i].name << endl;
        out << accountsList[i].numBought << endl;
        for(int j = 0; j < accountsList[i].numBought; ++j) {
            out << accountsList[i].items[j].barcode << endl;
            out << accountsList[i].items[j].name << endl;
            out << accountsList[i].items[j].num << endl;
            out << accountsList[i].items[j].price << endl;
        }
    }
    out << numDisc << endl;
    for(int i = 0; i < numDisc; ++i) {
        out << discList[i].spend << endl;
        out << discList[i].perc << endl;
    }
}

void Shop::remove_item()
{
    Item cur;
    cur.input_barcode();
    int pos = find_item(cur.barcode);
    if(pos == -1) {
        cout << "This item does not exist, please consider inserting it first." << endl;
        return;
    }

    cout << "The product's information:" << endl;
    itemsList[pos].show();
    // here, it is understood that the shop owner eliminates the product, so the totalCost stays the same.
    // totalCost -= itemsList[pos].cost * itemsList[pos].stock;
    for(int i = pos; i < numItems - 1; ++i) {
        itemsList[i] = itemsList[i + 1];
    }
    --numItems;

    cout << "Product has been removed successfully." << endl;
}

int Shop::find_account(const char phone_num[])
{
    for(int i = 0; i < numAccounts; ++i) {
        if(strcmp(accountsList[i].phone_number, phone_num) == 0) {
            return i;
        }
    }
    return -1;
}

int Shop::find_discount(const int &lv)
{
    for(int i = 0; i < numDisc; ++i) {
        if(discList[i].spend == lv) {
            return i;
        }
    }
    return -1;
}

void Shop::set_discount()
{
    if(numDisc == MAX_DISC) {
        cout << "The number of discounts exceeds the maximum allowed. Please consider removing some." << endl;
        return;
    }

    Discount dis;
    dis.input_spend();
    int pos = find_discount(dis.spend);
    if(pos != -1) {
        cout << "This discount has already existed. Please consider editing it instead." << endl;
        return;
    }

    discList[numDisc].spend = dis.spend;
    result res;
    do {
        cout << "Input the percentage (integer from 0 to 100, no %): ";
        res = read_pos_int(dis.perc);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "Too many characters. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Invalid number. Please try again.\n";
        }
        else {
            if(dis.perc < 0 || dis.perc > 100) {
                cout << "Out of range. Please try again.\n";
                res = EMPTY; // random assignment to make the loop continue
            }
        }
    } while(res != SUCCESSFUL);
    discList[numDisc].perc = dis.perc;
    ++numDisc;
    cout << "The discount is added successfully." << endl;
}

void Shop::edit_discount()
{
    Discount dis;
    dis.input_spend();
    int pos = find_discount(dis.spend);
    if(pos == -1) {
        cout << "This discount does not exist. Please consider inserting it first." << endl;
        return;
    }

    result res;
    do {
        cout << "Input new spend (integer): ";
        res = read_pos_int(discList[pos].spend);
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
    
    do {
        cout << "Input new percentage (integer from 0 to 100, no %): ";
        res = read_pos_int(discList[pos].perc);
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

    cout << "The discount is edited successfully." << endl;
}

void Shop::remove_discount()
{
    Discount dis;
    dis.input_spend();
    int pos = find_discount(dis.spend);
    if(pos == -1) {
        cout << "This discount does not exist." << endl;
        return;
    }

    cout << "The discount's information:" << endl;
    discList[pos].show();
    for(int i = pos; i < numDisc - 1; ++i) {
        discList[i] = discList[i + 1];
    }
    --numDisc;

    cout << "Discount has been removed successfully." << endl;
}

void Shop::applyDiscount(double &price)
{
    Discount cur;
    cur.spend = 0;
    for(int i = 0; i < numDisc; ++i) {
        if(price >= discList[i].spend && discList[i].spend > cur.spend) {
            cur.spend = discList[i].spend;
            cur.perc = discList[i].perc;
        }
    }
    if(cur.spend != 0) {
        price -= price * cur.perc / 100.0;
    }
}

void Shop::sell()
{
    cout << "Please begin. Enter 0 to stop this process at any time." << endl;
    bool stop = false;
    double totalPrice = 0;
    Account cur; // current payment
    result res;

    for(int i = 1;; ++i) {
        cout << "Product " << i << ':' << endl;

        char bc[MAX_CODE];
        int pos;
        do {
            // read barcode
            do {
                cout << "Item's barcode: ";
                res = read_code(bc, MAX_CODE);
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
            if(strcmp(bc, "0") == 0) {
                stop = true;
                break;
            }
            pos = find_item(bc);
            if(pos == -1) {
                cout << "This item does not exist. Please try again!" << endl;
            }
        } while(pos == -1);

        if(stop) break;

        int num;
        do {
            do {
                cout << "Number of items: ";
                res = read_pos_int(num);
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
            if(num == 0) {
                stop = true;
                break;
            }
            if(num > itemsList[pos].stock) {
                cout << "There are only " << itemsList[pos].stock << " items left of this product. Please try again!" << endl;
            }
        } while(num > itemsList[pos].stock);

        if(stop) break;

        strcpy(cur.items[cur.numBought].barcode, bc);
        strcpy(cur.items[cur.numBought].name, itemsList[pos].name);
        cur.items[cur.numBought].price = itemsList[pos].price;
        cur.items[cur.numBought].num = num;
        itemsList[pos].stock -= num;
        totalPrice += itemsList[pos].price * num;
        if(itemsList[pos].stock == 0) {
            // this product is sold out, so remove it from myShop
            for(int i = pos; i < numItems - 1; ++i) {
                itemsList[i] = itemsList[i + 1];
            }
            --numItems;
        }
        ++cur.numBought;
    }

    char option;
    do {
        cout << "Save this payment to personal account? (Y/N) ";
        res = read_char(option);
        if(res == EMPTY) {
            cout << "Nothing was inputted. Please try again.\n";
        }
        else if(res == EXCESSIVE) {
            cout << "More than one character inputted. Please try again.\n";
        }
        else if(res == INVALID) {
            cout << "Invalid character. Please try again.\n";
        }
    } while(res != SUCCESSFUL);

    if(option == 'Y') {
        cur.input_phonenum();
        int pos = find_account(cur.phone_number);
        bool can_signup = true;
        if(pos == -1) {
            if(numAccounts == MAX_ACCOUNT) {
                cout << "This account has not been created yet. Since the number of accounts exceeds the maximum allowed,"
                        " please consider removing some in order to sign up this account.\n";
                can_signup = false;
            }
            else {
                cout << "This account has not been created yet. Please sign up:\n";
                do {
                    cout << "Customer's name: ";
                    res = read_name(cur.name, MAX_NAME);
                    if(res == EMPTY) {
                        cout << "Nothing was inputted. Please try again.\n";
                    }
                    else if(res == EXCESSIVE) {
                        cout << "Too many characters. Please try again under " << MAX_NAME - 1 << " characters.\n";
                    }
                } while(res != SUCCESSFUL);
                pos = numAccounts++;
            }
        }
        else {
            strcpy(cur.name, accountsList[pos].name);
        }
        
        if(can_signup) {
            Account &acc = accountsList[pos];
            strcpy(acc.phone_number, cur.phone_number); // recopy if the account already exists before
            strcpy(acc.name, cur.name);
            for(int i = 0; i < cur.numBought; ++i) {
                acc.items[acc.numBought] = cur.items[i];
                ++acc.numBought;
            }
        }
    }

    cout << "The total price is: " << totalPrice << endl;
    applyDiscount(totalPrice);
    cout << "The price after the discount is applied is: " << totalPrice << endl;
    totalRevenue += totalPrice;
    for(int i = 0; i < cur.numBought; ++i) {
        totalSales += cur.items[i].num;
    }
}

void Shop::remove_account()
{
    Account acc;
    acc.input_phonenum();
    int pos = find_account(acc.phone_number);
    if(pos == -1) {
        cout << "This account does not exist." << endl;
        return;
    }

    cout << "Account's information:" << endl;
    accountsList[pos].show();
    for(int i = pos; i < numAccounts - 1; ++i) {
        accountsList[i] = accountsList[i + 1];
    }
    --numAccounts;
    cout << "The account is removed successfully." << endl;
}

void Shop::check_profit()
{
    cout << "The profit attained so far is: " << totalRevenue - totalCost << endl;
}