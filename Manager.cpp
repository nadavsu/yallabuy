//
// Created by Nadav Suliman on 19/12/19.
//

#include "Manager.h"

Manager::Manager() {
    this->max_account = 1;
    this->curr_account = 0;
    this->num_of_buyers = 0;
    this->num_of_sellers = 0;
    this->num_of_buyersellers = 0;
    this->account_arr = new Account *[max_account];
}

Manager::~Manager() {
    for(int i = 0; i < max_account; i++) {
        delete this->account_arr[i];
    }

    delete[] account_arr;
}

int Manager::getNumOfAccounts() const {
    return curr_account;
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

const Manager& Manager::operator+=(Account* other) {
    addAccout(other);
    return *this;
}

bool Manager::login(const char *username, const char *password) const {
    for (int i = 0; i < curr_account; i++) {
        if (strcmp(username, account_arr[i]->username) == 0) {
            return strcmp(password, account_arr[i]->password) == 0;
        }
    }
    return false;
}

Account *Manager::getAccount(const char *username) {
    for (int i = 0; i < curr_account; i++) {
        if (strcmp(account_arr[i]->username, username) == 0) {
            return account_arr[i];
        }
    }
    return nullptr;
}

void Manager::addAccout(Account* temp) {
    if (curr_account == max_account) {
        my_realloc();
    }
    const char* account_type;
    account_type = typeid(*temp).name();
    if (strcmp(account_type, typeid(Buyer).name()) == 0) {
        Buyer* temp_buyer = dynamic_cast<Buyer*>(temp);
        account_arr[curr_account++] = new Buyer(*temp_buyer);
        num_of_buyers++;
    }
    else if (strcmp(account_type, typeid(Seller).name()) == 0) {
        Seller* temp_seller = dynamic_cast<Seller*>(temp);
        account_arr[curr_account++] = new Seller(*temp_seller);
        num_of_sellers++;
    }
    else if (strcmp(account_type, typeid(BuyerSeller).name()) == 0) {
        BuyerSeller* temp_buyerseller = dynamic_cast<BuyerSeller*>(temp);
        account_arr[curr_account++] = new BuyerSeller(*temp_buyerseller);
        num_of_buyersellers++;
    }
    else {
        cout << "Error: didnt recognize account type try enter new account again" << endl;

    }
}

//TODO: Add exceptions in next exercise here.

bool Manager::buyerIsCartEmpty(const char *buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        return buyer->isEmptyCart();
    }
    cout << "Buyer not found!\n";
    return true;
}

bool Manager::sellerIsStockEmpty(const char* seller_username) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        return seller->isEmptyStock();
    }
    cout << "Seller not found!\n";
    return true;
}

bool Manager::isItemExistInSeller(const char* seller_username, const char* item_name_to_buy) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        return seller->itemExist(item_name_to_buy);
    }
    cout << "Seller not found!\n";
    return false;
}

bool Manager::sellerIsQuantityFine(const char* seller_username,const char* item_name_to_buy,int quantity) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        return seller->quantityIsFine(item_name_to_buy, quantity);
    }
    cout << "Seller not found!\n";
    return false;
}

void Manager::printSellerShop(const char* seller_username) {
    Seller* seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        seller->printStock();
    } else {
        cout << "Seller not found!\n";
    }
}


void Manager::addFeedback(const Feedback& feedback, const char *seller_username) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        seller->setFeedback(feedback);
    } else {
        cout << "Seller not found!\n";
    }
}


void Manager::AddItem(const char *seller_username, const Item& new_item) {
    Item* item;                 // responsible for pointer because add to list
    item = new Item(new_item);
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        seller->setItem(item);
    } else {
        cout << "Seller not found!\n";
    }
}


void Manager::addItemToCart(const char *buyer_username, const char* seller_username, const char* item_name_to_buy, int quantity) {
    Item* seller_item = getItemFromSellerToBuyer(seller_username, item_name_to_buy, quantity);
    Item* new_item;
    new_item = new Item(*seller_item);
    new_item->next = nullptr;
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        buyer->addToCart(new_item);
    } else {
        cout << "Buyer not found!\n";
    }
    delete seller_item;
}

Item* Manager::getItemFromSellerToBuyer(const char* seller_username, const char* item_name_to_buy, int quantity) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    if(seller) {
        Item *seller_item = seller->getItemToBuyer(item_name_to_buy, quantity);
        return seller_item;
    }
    return nullptr;
}

void Manager::printBuyerCart(const char *buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        buyer->printCart();
    }
    else {
        cout << "Buyer not found!\n";
    }
}

void Manager::payOrder(const char *buyer_username, Order& order) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    Item *curr_cart_item;
    Item *curr_order_item = order.getOrderedItemsHead();

    buyer->addToSellerHistory(order.getNameOfSellers(), order.getNumOfSellers());
    while (curr_order_item) {
        curr_cart_item = buyer->getCartHead();
        while (curr_cart_item) {
            if (curr_order_item->GetQuantity() && strcmp(curr_order_item->GetName(), curr_cart_item->GetName()) == 0) {
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
    for (int i = 0; i < curr_account; i++) {
        Buyer *temp = dynamic_cast<Buyer *>(account_arr[i]);
        if(temp) {
            printLine();
            cout << *temp;
            printLine();
        }
    }
}

void Manager::printSellers() const {
    for (int i = 0; i < curr_account; i++) {
        Seller *temp = dynamic_cast<Seller *>(account_arr[i]);
        if(temp) {
            printLine();
            cout << *temp;
            printLine();
        }
    }
}

bool Manager::isSellerExist(char *seller_username) {
    Seller *seller = dynamic_cast<Seller *>(getAccount(seller_username));
    return seller != nullptr;
}

bool Manager::printItemsNamed(const char *item_name) {
    bool res = false;
    for(int i = 0; i < curr_account; i++) {
        Seller *temp = dynamic_cast<Seller *>(account_arr[i]);
        if(temp) {
            Item *curr_item = temp->stock_list.getHead();
            while (curr_item) {
                if (strcmp(item_name, curr_item->GetName()) == 0) {
                    cout << *curr_item;
                    res = true;
                }
                curr_item = curr_item->getNext();
            }
        }
    }
    return res;
}

void Manager::printBuyerSellerHistory(const char *buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        buyer->printSellerHistory();
        printLine();
    } else {
        cout << "Buyer not found!\n";
    }
}

void Manager::printBuyerSellers() const {
    for (int i = 0; i < curr_account;i++) {
        if (strcmp(typeid(*account_arr[i]).name(),typeid(BuyerSeller).name()) == 0) {
            cout << *account_arr[i] << endl;
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

bool Manager::sellerExistInBuyerSeller(const char *buyer_username, const char *seller_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer) {
        for (int i = 0; i < buyer->seller_history_size; ++i) {                    //Looking in the buyer history.
            if (strcmp(buyer->seller_history[i], seller_username) == 0) {
                return true;
            }
        }
        return false;
    }
    cout << "Buyer not found!\n";
    return false;
}

void Manager::copyCartToOrder(Order& order, const char *buyer_username) {
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

///Test Functions-----------------------------------------------------------

void Manager::_debugfill() {
    Address b_address1("Nahariya", "Bialik", 2);
    Address b_address2("Tel Aviv", "Bograshov", 9);
    Address s_address1("Raanana", "Aharonson", 12);
    Address s_address2("Jerusalem", "Yitzhak Sade", 4);

    Account* temp;
    temp = new Buyer("dorlasri", "123456", "Dor", "Lasri", b_address1);
    this->addAccout(temp);
    delete temp;

    temp = new Buyer("arnaudmaarek", "ilovefrance", "Arnaud", "Maarek", b_address2);
    this->addAccout(temp);
    delete temp;

    temp = new Seller("nadavsuliman", "fuckyou", "Nadav", "Suliman", s_address1);
    this->addAccout(temp);
    delete temp;
    Item item1s1("nadavsuliman", "PS5", (Item::eCategory) 3, 4000, 20);
    Item item2s1("nadavsuliman", "Wii", (Item::eCategory) 3, 980, 5);
    Item item3s1("nadavsuliman", "Pizza", (Item::eCategory) 0, 60, 90);
    AddItem("nadavsuliman", item1s1);
    AddItem("nadavsuliman", item2s1);
    AddItem("nadavsuliman", item3s1);

    temp = new Seller("shaitek5", "maccabizona", "Shai", "Rubinstein", s_address2);
    addAccout(temp);
    delete temp;
    Item item1s2("shaitek5", "ASUS PC", (Item::eCategory) 0, 3000, 50);
    Item item2s2("shaitek5", "Macbook Pro", (Item::eCategory) 0, 10000, 5);
    Item item3s2("shaitek5", "Sambusak", (Item::eCategory) 0, 10, 20);
    AddItem("shaitek5", item1s2);
    AddItem("shaitek5", item2s2);
    AddItem("shaitek5", item3s2);

}


bool Manager::testCompareOperator(const char *username_1, const char *username_2) {
    Buyer *buyer_1 = dynamic_cast<Buyer *>(getAccount(username_1));                     //Note
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

bool Manager::testPrintCart(const char *buyer_username) {
    Buyer *buyer = dynamic_cast<Buyer *>(getAccount(buyer_username));
    if(buyer && !buyer->isEmptyCart()) {
        cout << buyer->cart;
        return true;
    }
    return false;
}

bool Manager::testPrintAccount(const char *username) {
    Account *account = getAccount(username);
    if(account) {
        cout << *account;
        return true;
    }
    return false;
}