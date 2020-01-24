//
//BY NADAV SULIMAN AND DOR LASRI
//GROUP 1, KEREN KALIF.

#include "MainHeader.h"

int main() {

    Manager manager;
    int ans;
    //manager._debugfill();
    printTitle("Welcome to YallaBuy!");     //Main menu
    do {
        ans = printMainMenu();
        if (ans == 1) {
            newAccount(manager);
        } else if (ans == 2) {
            makeFeedback(manager);
        } else if (ans == 3) {
            makeItem(manager);
        } else if (ans == 4) {
            addToCart(manager);
        } else if (ans == 5) {
            MakeOrderFromCart(manager);
        } else if (ans == 6) {
            manager.printBuyers();
        } else if (ans == 7) {
            manager.printSellers();
        }else if (ans == 8) {
            manager.printBuyerSellers();
        }else if (ans == 9) {
            getItemInfo(manager);
        }else if (ans == 10) {
            manager.printAccount();
        } else if (ans == 11) {
            testOperators(manager);
        }else if (ans == 12){
            saveSystem(manager);
        }else if (ans == 13) {
            loadSystem(manager);
        }else if (ans == 0) {
            char c;
            cout << "Are you sure? [Y/N]: ";
            cin >> c;
            if (c == 'Y' || c == 'y') {
                cout << "Thank you for shopping!\n";
                printLine();
                return 0;
            }
        } else {
            cout << "Your input is invalid, please try again.\n";
            printLine();
        }
    } while (true);
}


//A funciton that adds new account, takes in info from the user
void newAccount(Manager& admin) {
    int house_number;
    int account_type;
    string street, city, f_name, l_name, password, username;
    Account* temp;

    cout << "What type of user do you want to open?" << endl;
    cout << "1. Register as a new buyer"<< endl;
    cout << "2. Register as a new seller"<< endl;
    cout << "3. Register as a new buyer/seller" << endl;
    cin >> account_type;

    if (account_type == 1) {                                     //Choosing account type to create.
        printTitle("New Account Buyer");
    }
    else if(account_type == 2) {
        printTitle("New Account Seller");
    }
    else if (account_type == 3) {
        printTitle("New Account BuyerSeller");
    }
    else {
        cout << "Invalid Input" << endl;
        return;
    }
    cout << "First Name: ";//Taking info from the user.
    cin.getline(&trash,1);
    getline(cin, f_name);
    f_name.resize(FNAME_MAX_LEN);
    f_name.shrink_to_fit();
    cout << "Last Name: ";
    getline(cin, l_name);
    l_name.resize(LNAME_MAX_LEN);
    l_name.shrink_to_fit();
    cout << "Username: ";
    getline(cin, username);
    username.resize(USERNAME_MAX_LEN);
    username.shrink_to_fit();
    do {
        cout << "Password (at least 6): ";
        getline(cin, password);
    } while (password.length() < 6);
    cout << "City: ";
    getline(cin, city);
    city.resize(CITY_MAX_LEN);
    city.shrink_to_fit();
    cout << "Street: ";
    getline(cin, street);
    street.resize(STREET_MAX_LEN);
    street.shrink_to_fit();
    cout << "House Number: ";
    cin >> house_number;
    printLine();
    Address address(city, street, house_number);
    if (account_type == 1) {                                         //Creating the object based to the account_type
        temp = new Buyer(username, password, f_name, l_name, address) ;
    }
    else if (account_type == 2) {
        temp = new Seller(username, password, f_name, l_name, address);
    }
    else if (account_type == 3) {
        temp = new BuyerSeller(username, password, f_name, l_name, address);
    }
    else {
        cout << "Invalid Input" << endl;
        return;
    }
    admin += temp;
    delete temp;
}

//A function that creates a new feedback based on user input.
void makeFeedback(Manager& admin) {
    string buyer_username, password, seller_username, comment;
    bool found;
    char cont ;

    printTitle("New Feedback");
    printLogin(admin, buyer_username, password, "Buyer");            //Logging in.
    admin.printBuyerSellerHistory(buyer_username);
    do {
        cout << "Please enter the name of the seller you want to give feedback to: "<<endl;       //Checking if the user bought from the seller.
        getline(cin, seller_username);
        found = admin.sellerExistInBuyerSeller(buyer_username, seller_username);
        if (!found) {                                                                   //If the seller not found
            cout << seller_username << " not found in " << buyer_username << "'s history.\n"<<endl;
            cout << "Would you like to try again? [Y/N]"<<endl;
            cin.getline(&cont,1);
            if (cont == 'N' || cont == 'n') {
                return;
            }
        }
    } while (!found);
    cout << "Comment:" << endl;                                 //Taking comment from the user.
    getline(cin, comment);
    comment.resize(COMMENT_MAX_LEN);
    comment.shrink_to_fit();
    admin.addFeedback(Feedback(buyer_username, comment), seller_username);
    printLine();
}


//A function which creates an item from the user.
void makeItem(Manager &admin) {
    string seller_username, password;
    char ans;

    printTitle("Add a new item to stock");
    printLogin(admin, seller_username, password, "Seller");
    do {                                                            //Taking in information until the user says stop.
        string name;
        char trash;
        int category, price, quantity;

        printSubTitle("Add your product");
        cout << "Name:" << endl;
        getline(cin, name);
        name.resize(ITEM_MAX_NAME_LEN);
        name.shrink_to_fit();
        cout << "Category: (Enter 0 for Electronics, 1 for Home, 2 for Garden, 3 for Games):" << endl;
        cin >> category;
        cout << "Price: " << endl;
        cin >> price;
        cout << "Quantity: " << endl;
        cin >> quantity;;
        cout << "Enter another one? [Y/N]" << endl;
        cin >> ans;
        cin.getline(&trash, 1);
        Item item(seller_username, name, (Item::eCategory) category, price, quantity);      //Creating the item.
        admin.AddItem(seller_username, item);                                         //Adding it to the seller.
    } while (ans == 'y' || ans == 'Y');
}

//A function which is used to add to add an item from cart.
void addToCart(Manager &admin) {
    string buyer_username, seller_username, password, item_name_to_buy;
    int quantity;

    printTitle("Add to Cart");
    printLogin(admin, buyer_username, password, "Buyer");
    printLine();
    admin.printSellers();                             //Printing all available sellers you can buy from.
    do {
        cout << "Please enter the seller's username you want to buy from:\n";   //Letting the user choose a seller.
        getline(cin, seller_username);

    } while(!(admin.isSellerExist(seller_username)));
    if (!(admin.sellerIsStockEmpty(seller_username))) {
        admin.printSellerShop(seller_username);             //Printing the seller's stock.
    }
    else {
        cout << "No item in shop.\nReturning to menu.\n";
        return;
    }
    do {
        cout << "Please enter the items you want to buy.\n";
        getline(cin, item_name_to_buy);
    } while (!(admin.isItemExistInSeller(seller_username,item_name_to_buy)));//Checking if the item was found (null if not)

    do {
        cout << "Input quantity: ";
        cin >> quantity;
    } while (!(admin.sellerIsQuantityFine(seller_username, item_name_to_buy, quantity)));     //Taking in the quanityt while it's in range.
    admin.addItemToCart(buyer_username, seller_username,item_name_to_buy, quantity);        //Adding the item and the quantity to cart.
    printLine();
}

//A function used to make an order from the cart. choosing items.
void MakeOrderFromCart(Manager &admin) {
    string buyer_username, password;
    char add_to_order;
    char want_to_pay;
    int quantity;

    printTitle("Make Order");
    printLogin(admin, buyer_username, password, "Buyer");
    printSubTitle("Choose from your cart:");

    if(admin.buyerIsCartEmpty(buyer_username)) {
        cout << "Your cart is empty.\n";
        return;
    }

    Order curr_order(buyer_username);                                   //Creating a new order with the username.
    admin.copyCartToOrder(curr_order, buyer_username);              //Copying the items from the cart to the order.
    Item *temp = curr_order.getOrderedItemsHead();
    cout << "Your cart :" << endl;
    while (temp) {                                            //Going through the items in the users cart
            temp->printItem();
            cout << "Do you want to add this Item to your order [Y/N]?" << endl; //Asking him what he wants to add.
            cin >> add_to_order;
            if (add_to_order == 'y' || add_to_order == 'Y') {           //Adding the item from the cart to the order list.
                do {
                    cout << "Add the quantity you want to buy:" << endl;
                    cin >> quantity;
                } while (quantity <= 0 && quantity >= temp->GetQuantity());
                temp->SetQuantity(quantity);                    //Updating the quantity.
            } else {                                            //Setting the quantity to 0 if the user does not want to add the item.
                temp->SetQuantity(0);
            }
            temp = temp->getNext();
    }
    curr_order.updatePrice();
    curr_order.updateSellerHistory();

    cout << "Do you want to pay[Y/N]?" << endl;
    cin >> want_to_pay;
    if (want_to_pay == 'y' || want_to_pay == 'Y') {
        cout << "In Payment..." << endl;
        admin.payOrder(buyer_username, curr_order);           //Processing the payment.
        cout << "Thank you for buying" << endl;
    } 
    else {
        cout << "Canceling order.\n";
    }
    printLine();
}

//getting information about an item.
void getItemInfo(Manager& manager) {
    char trash;
    string item_name;
    bool does_exist;
    cout << "Please enter the name of the item you want to print:\n";       //Taking item name from the user.
    cin.getline(&trash, 1);
    getline(cin, item_name);
    does_exist = manager.printItemsNamed(item_name);        //Printing the items named by the users.
    if(!does_exist) {
        cout << item_name << " not found!\n";
        printLine();
    }
}

void testOperators(Manager& admin) {
    int ans;
    char trash;
    do{
        ans = printOperatorsMenu();
        if (ans == 1) {
            string buyer_username1, buyer_username2;
            cout << "Enter two buyer or buyerseller usernames:\n";
            cin.getline(&trash, 1);
            getline(cin, buyer_username1);
            getline(cin, buyer_username2);
            if(!admin.testCompareOperator(buyer_username1, buyer_username2)) {
                cout << "One of the buyers not found!\n";
            }
        } else if (ans == 2) {
            string buyer_username;
            cout << "Enter a buyer username: ";
            cin.getline(&trash, 1);
            getline(cin, buyer_username);
            printSubTitle(buyer_username.append("'s Cart:\n"));
            if(!admin.testPrintCart(buyer_username)) {
                cout << "Buyer not found or his cart is empty.\n";
            }
        } else if (ans == 3) {
            string username;
            cout << "Enter a username: ";
            cin.getline(&trash, 1);
            getline(cin, username);
            if(!admin.testPrintAccount(username)) {
                cout << "Account with username " << username << " not found!\n";
            }
        } else if (ans == 4) {
            newAccount(admin);
        } else if (ans == 0) {
            return;
        } else {
            cout << "Invalid input!\n";
            printLine();
        }
    } while(true);
}

void saveSystem(Manager& manager) {
    string filename;
    char trash;
    cout << "Please Enter the name of the file that you want to save the system to(include end file like .txt etc):" << endl;
    cin.getline(&trash, 1);
    getline(cin,filename);
    ofstream OutFile(filename);
    OutFile << manager;
    OutFile.close();
}

void loadSystem(Manager& manager) {
    string filename;
    char trash;
    cout << "Please Enter the name of the file that you want to load from(include end file like .txt etc):" << endl;
    cin.getline(&trash, 1);
    getline(cin, filename);
    ifstream inFile("C:\\Users\\lasri\\source\\repos\\Amalasu\\Ecommerce\\test10.txt");
    inFile >> manager;
    inFile.close();
}