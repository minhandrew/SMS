#include "shop\shop.h"

using namespace std;

int main()
{
    cout << "WELCOME TO THE SHOP MANAGEMENT SYSTEM.\n\n";
    ifstream fin("shop.txt");
    if(fin) {
        myShop.read_input(fin);
    }
    fin.close();
    
    cout << fixed << setprecision(MAX_DECIMAL);
    while(true) {
        char com[MAX_COM];
        result res;
        do {
            cout << ">> ";
            res = read_name(com, MAX_COM);
            if(res == EMPTY) {
                // print nothing
            }
            else if(res == EXCESSIVE) {
                cout << "The command is too long. Please try again.\n";
            }
            else {
                bool accept = true;
                int N = strlen(com);
                for(int i = 0; i < N; ++i) {
                    if(com[i] < 'a' || com[i] > 'z') {
                        accept = false;
                        break;
                    }
                }
                if(!accept) {
                    cout << "Invalid command. Commands consist of only lowercase English letters. Please try again.\n";
                    res = EMPTY; // random assignment to make the loop continue
                }
            }
        } while(res != SUCCESSFUL);

        if(strcmp(com, "help") == 0) {
            cout << "-help: Show all the available commands." << endl;
            cout << "-status: Check the current status of the shop, including: the total cost, the total revenue, the total sales, all the items on sale, all the customers' accounts signed up, and all the discounts available." << endl;
            cout << "-add: Insert a new product into storage." << endl;
            cout << "-edit: Edit an existing item in storage." << endl;
            cout << "-rem: Remove an existing item in storage." << endl;
            cout << "-set: Set up a new discount to apply." << endl;
            cout << "-editdisc: Edit an existing discount in storage." << endl;
            cout << "-remdisc: Remove an existing discount in storage." << endl;
            cout << "-sell: Sell existing products in storage." << endl;
            cout << "-remacc: Remove an existing account from the system." << endl;
            cout << "-profit: Check the profit attained so far." << endl;
            cout << "-exit: Save all the processed data and exit the program." << endl;
        }
        else if(strcmp(com, "status") == 0) {
            myShop.show();
        }
        else if(strcmp(com, "add") == 0) {
            myShop.add_item();
        }
        else if(strcmp(com, "edit") == 0) {
            myShop.edit_item();
        }
        else if(strcmp(com, "rem") == 0) {
            myShop.remove_item();
        }
        else if(strcmp(com, "set") == 0) {
            myShop.set_discount();
        }
        else if(strcmp(com, "editdisc") == 0) {
            myShop.edit_discount();
        }
        else if(strcmp(com, "remdisc") == 0) {
            myShop.remove_discount();
        }
        else if(strcmp(com, "sell") == 0) {
            myShop.sell();
        }
        else if(strcmp(com, "remacc") == 0) {
            myShop.remove_account();
        }
        else if(strcmp(com, "profit") == 0) {
            myShop.check_profit();
        }
        else if(strcmp(com, "exit") == 0) {
            ofstream fout("shop.txt");
            myShop.save_output(fout);
            fout.close();
            return 0;
        }
        else {
            cout << "The command is unavailable. Please try again.\n";
        }
    }

    return 0;
}