/*
#include"MainHeader.h"

Buyer newBuyer() {
    char street[STREET_MAX_LEN + 1];
    char city[CITY_MAX_LEN + 1];
    int house_number;
    char f_name[FNAME_MAX_LEN + 1];
    char l_name[LNAME_MAX_LEN + 1];
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char trash;

    printTitle("New Buyer Account");
    cout << "First Name: ";
    cin.getline(&trash, 1);
    cin.getline(f_name, FNAME_MAX_LEN);
    cout << "Last Name: ";
    cin.getline(l_name, LNAME_MAX_LEN);
    cout << "Username: ";
    cin.getline(username, USERNAME_MAX_LEN);
    cout << "Password: ";
    cin.getline(password, PASSWORD_MAX_LEN);
    cout << "City: ";
    cin.get(city, CITY_MAX_LEN);
    cout << "Street: ";
    cin.getline(&trash, 1);
    cin.getline(street, STREET_MAX_LEN);
    cout << "House Number: ";
    cin >> house_number;
    printLine();

    return Buyer(username, password, f_name, l_name, Address(city, street, house_number));
}

//A function that takes in info from the user to add a new seller.
Seller newSeller() {
    char street[STREET_MAX_LEN + 1];
    char city[CITY_MAX_LEN + 1];
    int house_number;
    char f_name[FNAME_MAX_LEN + 1];
    char l_name[LNAME_MAX_LEN + 1];
    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char trash;

    printTitle("New Seller Account");       //Inputting information
    cout << "First Name: ";
    cin.getline(&trash, 1);
    cin.getline(f_name, FNAME_MAX_LEN);
    cout << "Last Name: ";
    cin.getline(l_name, LNAME_MAX_LEN);
    cout << "Username: ";
    cin.getline(username, USERNAME_MAX_LEN);
    cout << "Password: ";
    cin.getline(password, PASSWORD_MAX_LEN);
    cout << "City: ";
    cin.get(city, CITY_MAX_LEN);
    cout << "Street: ";
    cin.getline(&trash, 1);
    cin.getline(street, STREET_MAX_LEN);
    cout << "House Number: ";
    cin >> house_number;
    printLine();

    return Seller(username, password, f_name, l_name, Address(city, street, house_number)); //Creating the seller.
}


//A function that creates a new feedback based on user input.
void makeFeedback(Manager& manager) {
    char buyer_username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char seller_username[USERNAME_MAX_LEN + 1];
    bool found = false;
    char cont;

    printTitle("New Feedback");
    printBuyerLogin(manager, buyer_username, password);
    char** seller_history = manager.getBuyer(
        buyer_username)->getSellerHistory();       //getBuyer will never return nullptr here because of login.
    int size_of_seller_history = manager.getBuyer(buyer_username)->getNumOfSellers();
    do {
        cout << "Please enter the name of the seller you want to give feedback to: ";       //Checking if the user bought from the seller.
        cin.getline(seller_username, USERNAME_MAX_LEN);

        for (int i = 0; i < size_of_seller_history && !found; ++i) {                    //Looking in the buyer history.
            if (strcmp(seller_history[i], seller_username) == 0) {
                manager.AddFeedback(seller_username, newFeedback(buyer_username));      //Adding the feedback.
                found = true;
            }
        }
        if (!found) {                                                                   //If the seller not found
            cout << seller_username << " not found in " << buyer_username << "'s history.\n";
            cout << "Would you like to continue? [Y/N]";
            cin >> cont;
        }
    } while (!found || (cont != 'N' && cont != 'n'));
}

//A function that creates a new feedback
Feedback newFeedback(char* buyer_username) {
    char comment[COMMENT_MAX_LEN];              //It takes in the current time of the computer.
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);

    cout << "Enter your comment:\n";            //The comment is inserted here.
    cin.getline(comment, COMMENT_MAX_LEN);

    return Feedback(buyer_username, Date(TM.tm_year, TM.tm_mon, TM.tm_mday), comment); //returning the fededback.
}



//A function which creates an item from the user.
void makeItem(Manager& manager) {
    Item* new_list; // head of List
    char password[PASSWORD_MAX_LEN + 1]; // may cause problem for strcmp in manager login
    char seller_username[USERNAME_MAX_LEN + 1];
    char ans;

    printTitle("Add a new item to stock");
    printSellerLogin(manager, seller_username, password);
    do {                                                            //Taking in information until the user says stop.
        char name[ITEM_MAX_NAME_LEN + 1], trash;
        int category;
        int price;
        int quantity;

        printSubTitle("Add your product");
        cout << "Name:" << endl;
        cin.getline(name, ITEM_MAX_NAME_LEN);
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
        manager.AddItem(seller_username, item);                                         //Adding it to the seller.
    } while (ans == 'y' || ans == 'Y');
}

//A function which is used to add to add an item from cart.
void addToCart(Manager& manager) {
    char buyer_username[USERNAME_MAX_LEN + 1];
    char seller_username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char item_name_to_buy[ITEM_MAX_NAME_LEN + 1];
    int quantity;
    Seller* seller = nullptr;

    printTitle("Add to Cart");
    printBuyerLogin(manager, buyer_username, password);

    manager.printSellers();                             //Printing all available sellers you can buy from.
    do {
        cout << "Please enter the seller's username you want to buy from:\n";   //Letting the user choose a seller.
        cin.getline(seller_username, USERNAME_MAX_LEN);
        seller = manager.GetSeller(seller_username);                //GetSeller returns null if no seller is found.
    } while (!seller);

    seller->printStock();                                           //Printing the seller's stock.
    do {
        cout << "Please enter the items you want to buy.\n";
        cin.getline(item_name_to_buy, ITEM_MAX_NAME_LEN);
    } while (!(seller->getItem(item_name_to_buy)));                //Checking if the item was found (null if not)

    Item* to_sell = seller->getItem(item_name_to_buy);          //Copying the item so we can add it to the cart
    Item to_buy(*to_sell);
    do {
        cout << "Input quantity: ";
        cin >> quantity;
    } while (quantity <= 0 && quantity > to_buy.GetQuantity());     //Taking in the quanityt while it's in range.
    manager.addItemToCart(buyer_username, to_buy, quantity);        //Adding the item and the quantity to cart.
    to_sell->reduceQuantity(quantity);


}

//A function used to make an order from the cart. choosing items.
void MakeOrderFromCart(Manager& manager) {
    bool flag;
    char buyer_username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];
    char item_to_buy[ITEM_MAX_NAME_LEN + 1];
    char add_to_cart;
    char add_to_order;
    char want_to_pay;
    int quantity;

    printTitle("Make Order");
    printBuyerLogin(manager, buyer_username, password);
    printSubTitle("Choose from your cart:");

    Buyer* curr_buyer = manager.getBuyer(buyer_username);       //Getting the logged in buyer.

    while (curr_buyer->isEmptyCart()) {                                 //If the cart is empty then we'll go to the addToCart func
        cout << "Your cart is empty." << endl;
        cout << "Do you want to add item to your cart? [Y/N]" << endl;
        cin >> add_to_cart;
        if (add_to_cart == 'y' || add_to_cart == 'Y') {
            addToCart(manager);
        }
        else { // probably no.
            return;
        }
    }


    Order curr_order(buyer_username);                               //Creating a new order with the username.
    Item* curr_cart_item = curr_buyer->getCart().getHead();
    while (curr_cart_item) {                                            //Going through the items in the users cart
        cout << "Do you want to add this Item to your cart [Y/y]?" << endl; //Asking him what he wants to add.
        curr_cart_item->printItem();
        cin >> add_to_order;
        if (add_to_order == 'y' || add_to_order == 'Y') {           //Adding the item from the cart to the order list.
            Item* temp = new Item(*curr_cart_item);
            do {
                cout << "Add the quantity you want to buy:" << endl;
                cin >> quantity;
            } while (quantity <= 0 && quantity >= temp->GetQuantity());
            temp->SetQuantity(quantity);                    //Updating the quantity.
            curr_order.setItem(*temp);
            delete temp;
        }
        curr_cart_item = curr_cart_item->getNext();
    }

    cout << "Do you want to pay?" << endl;
    cin >> want_to_pay;
    if (want_to_pay == 'y' || want_to_pay == 'Y') {
        cout << "Thank you for buying" << endl;
        manager.payOrder(buyer_username, curr_order);           //Processing the payment.
    }
    else {
        cout << "Canceling order.\n";
    }
    else {
    cout << "canceling your order" << endl;
    }
}

//getting information about an item.
void getItemInfo(Manager& manager) {
    char trash;
    char item_name[ITEM_MAX_NAME_LEN + 1];
    bool does_exist;
    cout << "Please enter the name of the item you want to print:\n";
    cin.getline(&trash, 1);
    cin.getline(item_name, ITEM_MAX_NAME_LEN);
    does_exist = manager.printItemsNamed(item_name);        //Printing the items named by the users.
    if (!does_exist) {
        cout << item_name << " not found!\n";
        printLine();
    }
}

///The following functions are used for CUI. A bunch of for loops.
void printSubTitle(const char* title) {
    for (int i = 0; i < (PAGE_WIDTH - strlen(title)) / 2; ++i) {
        cout << "-";
    }
    cout << title;
    for (int i = 0; i < (PAGE_WIDTH - strlen(title)) / 2; ++i) {
        cout << "-";
    }
    cout << '\n';
}

void printTitle(const char* title) {

    cout << "+";
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
    cout << "|";
    for (int i = 0; i < (PAGE_WIDTH - 2 - strlen(title)) / 2; ++i) {
        cout << " ";
    }
    cout << title;
    for (int i = 0; i < (PAGE_WIDTH - 1 - strlen(title)) / 2; ++i) {
        cout << " ";
    }
    cout << "|\n";
    cout << "+";
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
}

void printLine() {
    cout << "+";
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
}

int printMenu() {
    int ans;
    cout << "To register as a new buyer, press 1.\n";
    cout << "To register as a new seller, press 2.\n";
    cout << "To add feedback on a seller, press 3.\n";
    cout << "To add a new item to your shop, press 4.\n";
    cout << "To add a new item to your cart, press 5.\n";
    cout << "To make a new order, press 6.\n";
    cout << "To show all the buyers, press 7.\n";
    cout << "To show all the seller, press 8.\n";
    cout << "To get information about a specific item, press 9.\n";
    cout << "To exit, press 0\n";
    printLine();
    cin >> ans;
    printLine();
    return ans;
}

void printBuyerLogin(const Manager& manager, char* username, char* password) {
    bool logged = true;
    emptyBuffer();
    printSubTitle("Buyer Login");
    do {
        if (!logged) {
            cout << "Wrong username or password!\n";
        }
        cout << "Username: ";
        cin.getline(username, USERNAME_MAX_LEN);
        cout << "Password: ";
        cin.getline(password, PASSWORD_MAX_LEN);
        logged = manager.loginBuyer(username, password);
    } while (!logged);
}

void printSellerLogin(const Manager& manager, char* username, char* password) {
    bool logged = true;
    emptyBuffer();
    printSubTitle("Seller Login");
    do {
        if (!logged) {
            cout << "Wrong username or password!\n";
        }
        cout << "Username: ";
        cin.getline(username, USERNAME_MAX_LEN);
        cout << "Password: ";
        cin.getline(password, PASSWORD_MAX_LEN);
        logged = manager.loginSeller(username, password);
    } while (!logged);
}


void emptyBuffer() {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != '\0');
}
*/