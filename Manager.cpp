//
// Created by Nadav Suliman on 19/12/19.
//

#include "Manager.h"

///Constructors & Destructors----------------------------------------------------
Manager::Manager() {
    this->num_of_buyers = 0;
    this->num_of_sellers = 0;
    this->num_of_buyersellers = 0;
}

Manager::~Manager() {
    while (!account_arr.empty()) {
        delete account_arr.back();
        account_arr.pop_back();
    }
    
}


///Operators---------------------------------------------------------------------
const Manager& Manager::operator+=(Account* other) {
    addAccount(other);
    return *this;
}
/* the order of the saving of the file is (new line here is new line in file) :
curr_account, num_of_buyers,num_of_sellers,num_of_buyersellers,max_account
account_arr[0]
.

.
account_arr[curr_account-1]

account save in this order:
   typeofaccount,address(order:m_city,m_street,m_home_number),username,password,lname,fname

   (in same line)
   then if seller:
   logsize of feedback
   FeedBacks[0]
   .
   .
   FeedBacks[num_of_feedbacks-1]
   order :
       date(order:year,month,day ),username,comment

     if buyer:
      seller_history_size,
      seller_history[0][0]
      .
      .
      .
      seller_history[seller_history_size-1][0]
      if buyerseller then all of the detail first seller then buyer
*/
ostream& operator<<(ostream& os, Manager& base) {
    if (typeid(os) == typeid(ofstream)) {
        Account* temp;
        const char* TypeName;
        os << base.account_arr.size() << " " << base.num_of_buyers << " " << base.num_of_sellers << " " <<
            base.num_of_buyersellers << " " << base.account_arr.capacity() << endl;
        for (auto account : base.account_arr) {
            temp = account;
            TypeName = typeid(*temp).name();
            if (strcmp(TypeName, typeid(Seller).name()) == 0) {
                Seller* newtemp = dynamic_cast<Seller*>(temp);
                os << newtemp;
            }
            else if (strcmp(TypeName, typeid(Buyer).name()) == 0) {
                Buyer* newtemp = dynamic_cast<Buyer*>(temp);
                os << newtemp;
            }
            else {
                BuyerSeller* newtemp = dynamic_cast<BuyerSeller*>(temp);
                os << newtemp;
            }
        }
    }
}
// not completed
ifstream& operator>>(ifstream& in, Manager& base) {
    if (typeid(in) == typeid(ifstream)) {
        string TypeName;
        int size_of_arr;
        int capacity_account;
        in >> size_of_arr >> base.num_of_buyers >> base.num_of_sellers >>
            base.num_of_buyersellers>> capacity_account;
        base.account_arr.resize(capacity_account);
        for (int i = 0; i < size_of_arr; i++) {
            in >> TypeName;
            if (TypeName.compare(typeid(Seller).name()) == 0) {
                Seller* newtemp = new Seller(in);
                base.account_arr.push_back(newtemp);
            }
            else if (TypeName.compare(typeid(Buyer).name()) == 0) {
                Buyer* newtemp = new Buyer(in);
                base.account_arr.push_back(newtemp);
            }
            else {//TypeName.compare(typeid(BuyerSeller).name())
                BuyerSeller* newtemp = new BuyerSeller(in);
                base.account_arr.push_back(newtemp);
            }
        }
        return in;
    }
}
///Getters------------------------------------------------------------------------
int Manager::getNumOfAccounts() const {
    return account_arr.size();
}

int Manager::getNumOfBuyers() const {
    return num_of_buyers;
}

int Manager::getNumOfSellers() const {
    return num_of_sellers;
}

int Manager::getNumOfBuyerSellers() const {
    return num_of_buyersellers;
}

//A functions which gets an account based on a username.
Account *Manager::getAccount(const string& username) {
    for(auto account : account_arr) {
        if (account->username == username) {
            return account;
        }
    }
    return nullptr;
}

Item* Manager::getItemFromSellerToBuyer(const string& seller_username, const string& item_name_to_buy, int quantity) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        Item *seller_item = seller->getItemToBuyer(item_name_to_buy, quantity);
        return seller_item;
    }
    return nullptr;
}

///Manager Functions-------------------------------------------------------------------------------
bool Manager::login(const string& username, const string& password) {
    Account *account = getAccount(username);
    if(account) {
        return account->getPassword() == password;
    }
    return false;
}

//A function which creates a new account.
void Manager::addAccount(Account* temp) {
    Account* new_account;
    new_account = temp->clone();
    account_arr.push_back(new_account);
    /*                                                //check this
    const char* account_type;
    account_type = typeid(*temp).name();
    if (strcmp(account_type, typeid(Buyer).name()) == 0) {
        Buyer* temp_buyer = dynamic_cast<Buyer*>(temp);
        account_arr.push_back(temp);
        num_of_buyers++;
    }
    else if (strcmp(account_type, typeid(Seller).name()) == 0) {
        Seller* temp_seller = dynamic_cast<Seller*>(temp);
        account_arr.push_back(temp);
        num_of_sellers++;
    }
    else if (strcmp(account_type, typeid(BuyerSeller).name()) == 0) {
        BuyerSeller* temp_buyerseller = dynamic_cast<BuyerSeller*>(temp);
        account_arr.push_back(temp);
        num_of_buyersellers++;
    }
    else {
        cout << "Error: didn't recognize account type, try entering a new account again." << endl;

    }
    */
}

//TODO: can create an object function for the following functions.
//Will take in class T, and function
//A function which adds a new feedback to a seller.
void Manager::addFeedback(const Feedback& feedback, const string& seller_username) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));           //Getting the seller based on ID.
    if(seller) {
        seller->setFeedback(feedback);                                              //Setting the feedback.
    } else {
        cout << "Seller not found!\n";
    }
}

//A function which returns if a buyer's cart is empty based on his username.
bool Manager::buyerIsCartEmpty(const string& buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));       //Getting the buyer
    if(buyer) {
        return buyer->isEmptyCart();                                        //Returning if his cart is empty.
    }
    cout << "Buyer not found!\n";
    return true;
}

//Same as function above just with seller's stock.
bool Manager::sellerIsStockEmpty(const string& seller_username) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        return seller->isEmptyStock();
    }
    cout << "Seller not found!\n";
    return true;
}

//A function which checks if an item name exists in a seller's stock.
bool Manager::isItemExistInSeller(const string& seller_username, const string& item_name_to_buy) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        return seller->itemExist(item_name_to_buy);
    }
    cout << "Seller not found!\n";
    return false;
}

bool Manager::sellerIsQuantityFine(const string& seller_username, const string& item_name_to_buy, int quantity) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        return seller->quantityIsFine(item_name_to_buy, quantity);
    }
    cout << "Seller not found!\n";
    return false;
}


void Manager::printSellerShop(const string& seller_username) {
    Seller* seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        cout << seller->stock_list;
    } else {
        cout << "Seller not found!\n";
    }
}

//A function which adds a new product to a seller.
void Manager::AddItem(const string& seller_username, const Item& new_item) {
    Item* item;                 // responsible for pointer because add to list
    item = new Item(new_item);  // Creating a new item copy.
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));   //Getting the seller based on the username.
    if(seller) {
        seller->setItem(item);                  //Giving the item to the seller.
    } else {
        cout << "Seller not found!\n";
    }
}

//A function which adds an item to the cart.
void Manager::addItemToCart(const string& buyer_username, const string& seller_username, const string& item_name_to_buy, int quantity) {
    Item* seller_item = getItemFromSellerToBuyer(seller_username, item_name_to_buy, quantity);
    Item* new_item;
    new_item = new Item(*seller_item);                              //Copying the seller's item.
    new_item->next = nullptr;
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));   //Searching for the username
    if(buyer) {
        buyer->addToCart(new_item);                                     //Adding the new item to the cart;
    } else {
        cout << "Buyer not found!\n";
    }
    delete seller_item;
}

void Manager::printBuyerCart(const string& buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        cout << buyer->cart;
    }
    else {
        cout << "Buyer not found!\n";
    }
}

//A function which closes an order.
void Manager::payOrder(const string& buyer_username, Order& order) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));           //Getting the buyer
    Item *curr_cart_item;
    Item *curr_order_item = order.getOrderedItemsHead();                        //Getting the head of the ordered items.

    buyer->addToSellerHistory(order.getNameOfSellers());
    while (curr_order_item) {                                                   //Updating the cart and order quantities.
        curr_cart_item = buyer->getCartHead();
        while (curr_cart_item) {
            if (curr_order_item->GetQuantity() && curr_order_item->GetName() == curr_cart_item->GetName()) {
                curr_cart_item->reduceQuantity(curr_order_item->GetQuantity());
                if (curr_cart_item->GetQuantity() == 0) {
                    buyer->deleteItemFromCart(curr_cart_item->GetName());
                }
                curr_cart_item = nullptr;
            } else {
                curr_cart_item = curr_cart_item->getNext();
            }
        }
        curr_order_item = curr_order_item->getNext();
    }
}

void Manager::printBuyers() const {
    for (auto account : account_arr) {
        Buyer *buyer = dynamic_cast<Buyer *>(account);
        if(buyer) {
            printLine();
            cout << *buyer;
            printLine();
        }
    }
}

void Manager::printSellers() const {
    for (auto account : account_arr) {
        Seller *seller = dynamic_cast<Seller *>(account);
        if(seller) {
            printLine();
            cout << *seller;
            printLine();
        }
    }
}

bool Manager::isSellerExist(string& seller_username) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    return seller != nullptr;
}

//Searching for an item based on a name.
bool Manager::printItemsNamed(const string& item_name) {
    bool res = false;
    for (auto account : account_arr) {                 //Going through the account array and getting all the sellers.
        Seller *temp = dynamic_cast<Seller *>(account);
        if(temp) {
            Item *curr_item = temp->stock_list.getHead();   //Going through the list
            while (curr_item) {
                if (item_name == curr_item->GetName()) { //Checking if the item name matches the current item name in the list.
                    cout << *curr_item;                     //Printing.
                    res = true;
                }
                curr_item = curr_item->getNext();
            }
        }
    }
    return res;
}

//Printing the buyer's seller history.
void Manager::printBuyerSellerHistory(const string& buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        buyer->printSellerHistory();
        printLine();
    } else {
        cout << "Buyer not found!\n";
    }
}

void Manager::printBuyerSellers() const {
    for (auto account : account_arr) {
        if ((typeid(*account).name(), typeid(BuyerSeller).name()) == 0) {
            cout << *account << endl;
        }
    }
}

void Manager::printAccount() const {
    cout << "Buyers:"<<endl;
    printBuyers();
    cout << "Sellers:" << endl;
    printSellers();
    cout << "BuyerSellers:" << endl;
    printBuyerSellers();
}

//Checking if a seller exists in the buyer's seller history - used for feedback.
bool Manager::sellerExistInBuyerSeller(const string& buyer_username, const string& seller_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        auto found = find(buyer->seller_history.begin(), buyer->seller_history.end(), seller_username);
        return (found != buyer->seller_history.end());
    }
    cout << "Buyer not found!\n";
    return false;
}

//Copying a cart to the order.
void Manager::copyCartToOrder(Order& order, const string& buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        order.setItemList(buyer->getCart());//make copy twice!!!!
    }
    else {
        cout << "Buyer not found!\n";
    }
}

void Manager::my_realloc() {
    this->max_account = (this->max_account) * 2;
    Account **new_account_arr = new Account *[this->max_account];
    for (int i = 0; i < this->curr_account; i++) {
        new_account_arr[i] = this->account_arr[i];
    }
    delete[] account_arr;
    account_arr = new_account_arr;
}
*/

///Test Functions-----------------------------------------------------------

void Manager::_debugfill() {
    Address b_address1("Nahariya", "Bialik", 2);
    Address b_address2("Tel Aviv", "Bograshov", 9);
    Address s_address1("Raanana", "Aharonson", 12);
    Address s_address2("Jerusalem", "Yitzhak Sade", 4);

    Account* temp;
    temp = new Buyer("dorlasri", "123456", "Dor", "Lasri", b_address1);
    this->addAccount(temp);
    delete temp;

    temp = new Buyer("arnaudmaarek", "ilovefrance", "Arnaud", "Maarek", b_address2);
    this->addAccount(temp);
    delete temp;

    temp = new Seller("nadavsuliman", "fuckyou", "Nadav", "Suliman", s_address1);
    this->addAccount(temp);
    delete temp;
    Item item1s1("nadavsuliman", "PS5", (Item::eCategory) 3, 4000, 20);
    Item item2s1("nadavsuliman", "Wii", (Item::eCategory) 3, 980, 5);
    Item item3s1("nadavsuliman", "Pizza", (Item::eCategory) 0, 60, 90);
    AddItem("nadavsuliman", item1s1);
    AddItem("nadavsuliman", item2s1);
    AddItem("nadavsuliman", item3s1);

    temp = new Seller("shaitek5", "maccabizona", "Shai", "Rubinstein", s_address2);
    addAccount(temp);
    delete temp;
    Item item1s2("shaitek5", "ASUS PC", (Item::eCategory) 0, 3000, 50);
    Item item2s2("shaitek5", "Macbook Pro", (Item::eCategory) 0, 10000, 5);
    Item item3s2("shaitek5", "Sambusak", (Item::eCategory) 0, 10, 20);
    AddItem("shaitek5", item1s2);
    AddItem("shaitek5", item2s2);
    AddItem("shaitek5", item3s2);

}

bool Manager::testCompareOperator(const string& username_1, const string& username_2) {
    Buyer *buyer_1 = dynamic_cast<Buyer *>(getAccount(username_1));
    Buyer *buyer_2 = dynamic_cast<Buyer *>(getAccount(username_2));

    if(buyer_1 && buyer_2) {
        printLine();
        cout << *buyer_1;
        printLine();
        cout << *buyer_2;
        printLine();
        cout << username_1 << " > " << username_2 << "?\n";
        (*buyer_1 > *buyer_2) ? cout << "true\n" : cout << "false\n";
        return true;
    }
    return false;
}

bool Manager::testPrintCart(const string& buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer && !buyer->isEmptyCart()) {
        cout << buyer->cart;
        return true;
    }
    return false;
}

bool Manager::testPrintAccount(const string& username) {
    Account *account = getAccount(username);
    if(account) {
        cout << *account;
        return true;
    }
    return false;
}