//
// Created by Nadav Suliman on 24/11/19.
//

#include "Buyer.h"
using namespace std;

///Constructors and Destructors------------------------------------------
Buyer::Buyer(const char *username,const char *password,const char *fname,const char *lname, Address& address): Account(username, password, fname, lname, address) {
    this->seller_history      = nullptr;
    this->seller_history_size = 0;
    this->total_price         = 0;
}

//Copy ctor
Buyer::Buyer(const Buyer& other) : Account(other), cart(other.cart) {
    copySellerHistory(other);
    this->total_price = other.total_price;
}

//Move ctor
Buyer::Buyer(Buyer&& other) : Account(std::move(other)), cart(std::move(other.cart)) {
    seller_history       = other.seller_history;
    seller_history_size  = other.seller_history_size;
    other.seller_history = nullptr;
    this->total_price = other.total_price;
}

void Buyer::toOs(ostream& os) const {
    os << "Cart total: " << total_price << endl;
}

bool Buyer::operator>(const Buyer& other) const {
    return this->getTotalPriceOfCart() > other.getTotalPriceOfCart();
}
Buyer::~Buyer() {
    emptySellerHistory();           //emptying the seller history.
    delete[] seller_history;        //deleting it.
}

const Buyer& Buyer::operator=(const Buyer& other) {
    if(this != &other){
        delete[]username;
        delete[]password;
        delete[]fname;
        delete[]lname;
        emptySellerHistory();
        setUsername(other.username);
        setPassword(other.password);
        setFName(other.fname);
        setLName(other.lname);
        this->address = other.address;
        this->cart = other.cart;
        copySellerHistory(other);
        this->seller_history_size = other.seller_history_size;
        this->total_price = other.total_price;
    } else {
        return *this;
    }
}

///Getters and Setters------------------------------------------------------
ItemList Buyer::getCart() const {
    return cart;
}

char **Buyer::getSellerHistory() const {
    return seller_history;
}

int Buyer::getNumOfSellers() const {
    return seller_history_size;
}

Item* Buyer::getCartHead() {
    return cart.getHead();
}

int Buyer::getTotalPriceOfCart() const  {
    return total_price;
}

///Cart Functions----------------------------------------------------------
void Buyer::addToCart(Item* new_item) {
    cart.addToTail(new_item);
    this->total_price += new_item->GetPrice() * new_item->GetQuantity();
}

bool Buyer::isEmptyCart() {
    return cart.isEmpty();
}


///Seller History Functions-------------------------------------------------
//A function used to add an array of strings to the history of the buyer.
//Used for the feedback
void Buyer::addToSellerHistory(char** seller_name,int size_of_seller_name) {
    int index = 0;
    bool To_add = true;

    char** AfterEaraseDup = new char* [size_of_seller_name]; // delete in makeNewSellerHistory func
    for (int i = 0; i < size_of_seller_name;i++) {
        for (int j = 0; j < seller_history_size;j++) {
            if (strcmp(seller_history[j], seller_name[i]) == 0) {
                To_add = false;
            }
            else {
                To_add = true;
            }
        }
        if (To_add) { // did the last compare
            AfterEaraseDup[index] = new char[strlen(seller_name[i]) + 1];
            strcpy(AfterEaraseDup[index], seller_name[i]);
            index++;
        }
    }
    makeNewSellerHistory(AfterEaraseDup, index);
}

//A function used to make a new seller history array.
void Buyer::makeNewSellerHistory(char** AfterEaraseDup, int size_of_AfterEaraseDup) {
    char** NewSellerHistory = new char* [size_of_AfterEaraseDup + seller_history_size];
    for (int i = 0; i < seller_history_size;i++) {
        NewSellerHistory[i] = seller_history[i];
    }
    for (int i = 0; i < size_of_AfterEaraseDup; i++) {
        NewSellerHistory[i + seller_history_size] = AfterEaraseDup[i];
    }
    delete[]this->seller_history;
    delete[]AfterEaraseDup;
    this->seller_history = NewSellerHistory;
    this->seller_history_size = size_of_AfterEaraseDup + seller_history_size;
}

void Buyer::emptySellerHistory() {
    for(int i = 0; i < seller_history_size; ++i) {
        delete seller_history[i];
    }
}

void Buyer::copySellerHistory(const Buyer& other) {
    if (other.seller_history_size > 0) {
        seller_history = new char* [other.seller_history_size];
        for (int i = 0; i < other.seller_history_size; ++i) {
            strcpy(seller_history[i], other.seller_history[i]);
        }
    }
    else {
        this->seller_history_size = 0;
        this->seller_history = nullptr;
    }
}

///Printing Functions--------------------------------------------------------
void Buyer::printSellerHistory()const {
    cout << "Buyer : "<< endl << this->username<< endl << "Seller's History:" << endl;
    for (int i = 0; i < this->seller_history_size;i++) {
        cout << this->seller_history[i] <<endl;
    }

}

void Buyer::printCart() const {
    if(cart.isEmpty()) {
        cout << "Your cart is empty!";
    } else {
        cout << cart;
    }
}

void Buyer::deleteItemFromCart(const char* item_name) {
    Item* item_to_delete;
    item_to_delete = cart.findItem(item_name);
    total_price -= item_to_delete->GetPrice() + item_to_delete->GetQuantity();
    cart.deleteItem(item_name);
}

const char* Buyer::getType()const {
    return "Buyer";
}

Account* Buyer::clone() const {
    return new Buyer(*this);
}