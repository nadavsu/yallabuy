//
//BY NADAV SULIMAN AND DOR LASRI
//GROUP 1, KEREN KALIF.

#include "MainHeader.h"
#include "CUI.h"

int main() {

    Manager manager;
    int ans;
    
    printTitle("Welcome to LASU!");     //Main menu
    do {
        ans = printMenu();
        if (ans == 1) {
            Buyer b(newBuyer());
            manager.AddBuyer(b);
        } else if (ans == 2) {
            Seller s(newSeller());
            manager.AddSeller(s);
        } else if (ans == 3) {
            makeFeedback(manager);
        } else if (ans == 4) {
            makeItem(manager);
        } else if (ans == 5) {
            addToCart(manager);
        } else if (ans == 6) {
            MakeOrderFromCart(manager);
        } else if (ans == 7) {
            manager.printBuyers();
        } else if (ans == 8) {
            manager.printSellers();
        } else if (ans == 9) {
            getItemInfo(manager);
        } else if (ans == 0) {
            char c;
            cout << "Are you sure? [Y/N]: ";
            cin >> c;
            if (c == 'Y' || c == 'y') {
                cout << "Thank you for shopping!\n";
                printLine();
            }
        } else {
            cout << "Your input is invalid, please try again.\n";
            printLine();
        }
    } while (true);
}


//A funciton that adds new buyer, takes in info from the user
Buyer newBuyer() {
    char street[STREET_MAX_LEN + 1];
    char city[CITY_MAX_LEN + 1];
    int house_number;
    char f_name[bFNAME_MAX_LEN + 1];
    char l_name[bLNAME_MAX_LEN + 1];
    char username[bUSERNAME_MAX_LEN + 1];
    char password[bPASSWORD_MAX_LEN + 1];
    char trash;

    printTitle("New Buyer Account");
    cout << "First Name: ";
    cin.getline(&trash, 1);
    cin.getline(f_name, bFNAME_MAX_LEN);
    cout << "Last Name: ";
    cin.getline(l_name, bLNAME_MAX_LEN);
    cout << "Username: ";
    cin.getline(username, bUSERNAME_MAX_LEN);
    cout << "Password: ";
    cin.getline(password, bPASSWORD_MAX_LEN);
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
    char f_name[sFNAME_MAX_LEN + 1];
    char l_name[sLNAME_MAX_LEN + 1];
    char username[sUSERNAME_MAX_LEN + 1];
    char password[sPASSWORD_MAX_LEN + 1];
    char trash;

    printTitle("New Seller Account");       //Inputting information
    cout << "First Name: ";
    cin.getline(&trash, 1);
    cin.getline(f_name, sFNAME_MAX_LEN);
    cout << "Last Name: ";
    cin.getline(l_name, sLNAME_MAX_LEN);
    cout << "Username: ";
    cin.getline(username, sUSERNAME_MAX_LEN);
    cout << "Password: ";
    cin.getline(password, sPASSWORD_MAX_LEN);
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
void makeFeedback(Manager& admin) {
    char buyer_username[bUSERNAME_MAX_LEN + 1];
    char password[bPASSWORD_MAX_LEN + 1];
    char seller_username[sUSERNAME_MAX_LEN + 1];
    char comment[COMMENT_MAX_LEN + 1];
    bool found;
    char cont;

    printTitle("New Feedback");
    printBuyerLogin(admin, buyer_username, password);
    admin.printBuyerSellerHistory(buyer_username);
    do {
        cout << "Please enter the name of the seller you want to give feedback to: ";       //Checking if the user bought from the seller.
        cin.getline(seller_username, sUSERNAME_MAX_LEN);
        found = admin.sellerExistInBuyerSeller(buyer_username, seller_username);
        if (!found) {                                                                   //If the seller not found
            cout << seller_username << " not found in " << buyer_username << "'s history.\n";
            cout << "Would you like to continue? [Y/N]";
            cin >> cont;
        }
    } while (!found || (cont != 'N' && cont != 'n'));
    cin.getline(comment, COMMENT_MAX_LEN);
    admin.addFeedback(Feedback(buyer_username, comment), seller_username);
}


//A function which creates an item from the user.
void makeItem(Manager &admin) {
    Item *new_list; // head of List
    char password[sPASSWORD_MAX_LEN + 1]; // may cause problem for strcmp in manager login
    char seller_username[sUSERNAME_MAX_LEN + 1];
    char ans;

    printTitle("Add a new item to stock");
    printSellerLogin(admin, seller_username, password);
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
        admin.AddItem(seller_username, item);                                         //Adding it to the seller.
    } while (ans == 'y' || ans == 'Y');
}

//A function which is used to add to add an item from cart.
void addToCart(Manager &admin) {
    char buyer_username[bUSERNAME_MAX_LEN + 1];
    char seller_username[sUSERNAME_MAX_LEN + 1];
    char password[bPASSWORD_MAX_LEN + 1];
    char item_name_to_buy[ITEM_MAX_NAME_LEN + 1];
    int quantity;
    Seller *seller = nullptr;

    printTitle("Add to Cart");
    printBuyerLogin(admin, buyer_username, password);
    admin.printSellers();                             //Printing all available sellers you can buy from.
    do {
        cout << "Please enter the seller's username you want to buy from:\n";   //Letting the user choose a seller.
        cin.getline(seller_username, bUSERNAME_MAX_LEN);
        seller = admin.getSeller(seller_username);                //getSeller returns null if no seller is found.
    } while(!seller);
    seller->printStock();                                           //Printing the seller's stock.
    do {
        cout << "Please enter the items you want to buy.\n";
        cin.getline(item_name_to_buy, ITEM_MAX_NAME_LEN);
    } while (!(seller->itemExist(item_name_to_buy)));                //Checking if the item was found (null if not)

    do {
        cout << "Input quantity: ";
        cin >> quantity;
    } while (!(seller->quantityIsFine(item_name_to_buy,quantity)));     //Taking in the quanityt while it's in range.
    admin.addItemToCart(buyer_username, seller->getItemToBuyer(item_name_to_buy, quantity));        //Adding the item and the quantity to cart.
}

//A function used to make an order from the cart. choosing items.
void MakeOrderFromCart(Manager &admin) {
    char buyer_username[bUSERNAME_MAX_LEN + 1];
    char password[bPASSWORD_MAX_LEN + 1];
    char add_to_order;
    char want_to_pay;
    int quantity;

    printTitle("Make Order");
    printBuyerLogin(admin, buyer_username, password);
    printSubTitle("Choose from your cart:");

    if(admin.isCartEmpty(buyer_username)) {
        cout << "Your cart is empty.\n";
        return;
    }

    Order curr_order(buyer_username);                                   //Creating a new order with the username.
    admin.copyCartToOrder(curr_order, buyer_username);              //Copying the items from the cart to the order.
    Item *temp = curr_order.getOrderedItemsHead();

    while (temp) {                                            //Going through the items in the users cart
            temp->printItem();
            cout << "Do you want to add this Item to your cart [Y/N]?" << endl; //Asking him what he wants to add.
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

    cout << "Do you want to pay?" << endl;
    cin >> want_to_pay;
    if (want_to_pay == 'y' || want_to_pay == 'Y') {
        cout << "In Payment..." << endl;
        admin.payOrder(buyer_username, curr_order);           //Processing the payment.
        cout << "Thank you for buying" << endl;
    } 
    else {
        cout << "Canceling order.\n";
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
    if(!does_exist) {
        cout << item_name << " not found!\n";
        printLine();
    }
}