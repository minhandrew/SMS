# SMS
SMS - STORE MANAGEMENT SYSTEM

**I.	Introduction:**
This is a simple program to help store managers manipulate the data of their products. Because my knowledge about user interface is limited, managers are expected to use given commands to interact with the program. Further features are listed out below.

**II.	Features:**
-	Run the “**main.exe**” file to use the program.
-	Features are used through specific commands (after the sign “>>”) and are executed by hitting Enter.
-	Throughout the process, the barcode of any item is constant. No updating action on the barcode is allowed.
1.	View all the commands:
One can use the command “**help**” to see all the available commands of the program. Brief description of each command is provided.
2.	View the status of the shop:
One can use the command “**status**” to check the current status of the shop, including: the total cost, the total revenue, the total sales, all the items on sale, all the customers’ accounts signed up, and all the discounts available.
3.	Insert a new item:
One can use the command “**add**” to insert a new item into storage.
First, the program checks whether the inputed item has existed or not by looking at the barcode inputed. If it already exists, a warning message is displayed. Otherwise, the program then continues asking the following information about the product: name, stock, price.
4.	Edit an existing item:
One can use the command “**edit**” to edit an existing item.
If the item, however, does not exist by looking at the barcode, a warning message is displayed. Otherwise, the program asks the name, stock and price of the item.
5.	Remove an existing item:
One can use the command “**rem**” to remove an existing item.
If the item, however, does not exist by looking at the barcode, a warning message is displayed. Otherwise, the program first displays the information of this item and then removes it completely.
6.	Set up a new discount:
One can use the command “**set**” to add a new discount.
The program first checks whether this discount already exists or not. If it does, a warning message is displayed. Otherwise, the discount’s level and percentage are required as integers.
7.	Edit an existing discount:
One can use the command “**editdisc**” to edit an existing discount.
The program first checks whether this discount already exists or not. If it does not, a warning message is displayed. Otherwise, the discount’s level and percentage are allowed to be edited.
8.	Remove an existing discount:
One can use the command “**remdisc**” to remove an existing discount.
The program first checks whether this discount already exists or not. If it does not, a warning message is displayed. Otherwise, this discount will be removed.
9.	Sell an item:
One can use the command “**sell**” to sell an existing item in storage.
First, the program asks the barcode of each product being sought and the number of items of this product. If this number exceeds the actual number of items, a warning message is displayed and the user is allowed to input the number again. To end this process, input 0 at any time.
Next the program asks whether the buyer would like to save this payment to their personal account. If the choice is yes:
-	If they haven’t had an account yet by the phone number inputted, create a new account by enter the customer’s name and go to the next step below.
-	If the account has already been created, update the customer’s buying history.
In the next step, the program checks whether the total price satisfies the a specific discount. If numerous discounts are satisfied, the discount with the highest level is applied. The final price is which the customer needs to pay.
10.	 Remove an account:
One can use the command “**remacc**” to remove an existing account from the system.
The program first checks whether the account exists or not by looking at the phone number. If it does not, a warning message is displayed. Otherwise, the account is removed from the system (so that further accounts might be signed up).
11.	 Check the profit:
One can use the command “**profit**” to check the profit that the shop has attained.
12.	 Exit the program:
One can use the command “**exit**” to exit the program, all the data processed will be saved. This is the only way to save the data processed, so **don’t forget this command when closing the program!**
