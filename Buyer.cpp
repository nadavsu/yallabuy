//
// Created by Nadav Suliman on 24/11/19.
//

#include "Buyer.h"
using namespace std;

///Constructors and Destructors------------------------------------------
Buyer::Buyer(ifstream& os) :Account(os){
    os >> *this;
}
Buyer::Buyer(const string& username, const string& password, const string& fname, const string& lname, Address& address)
                                                                : Account(username, password, fname, lname, address) {
    this->seller_history;
    this->seller_history_size = 0;
    this->total_price         = 0;
}

//Copy ctor
Buyer::Buyer(const Buyer& other) : Account(other), cart(other.cart), total_price(other.total_price), seller_history_size
                                    (seller_history_size) {
    copySellerHistory(other);
}

//Move ctor
Buyer::Buyer(Buyer&& other) : Account(std::move(other)), cart(std::move(other.cart)), total_price(other.total_price),
                            seller_history_size(other.seller_history_size) {
    seller_history       = other.seller_history;
    other.seller_history = nullptr;
}

void Buyer::toOs(ostream& os) const {
    os << "Cart total: " << total_price << endl;
}

bool Buyer::operator>(const Buyer& other) const {
    return this->getTotalPriceOfCart() > other.getTotalPriceOfCart();
}
ifstream& operator>>(ifstream& in, Buyer& b) {
    if (typeid(in) == typeid(ifstream)) {
        in >> (Account&)b;
        in >> b.seller_history_size;
        for (int i = 0; i < b.seller_history_size; i++) {
            in >> b.seller_history[i];
        }
        return in;
    }
}
ostream& operator<<(ostream& out, Buyer& b) {
    if (typeid(out) == typeid(ofstream)) {
        out << (Account&)b;
        out << b.seller_history_size << endl; // add if size_of_feedback == 0
        for (int i = 0; i < b.seller_history_size; i++) {
            out << b.seller_history[i] << endl;
        }
    }
    return out;
}
Buyer::~Buyer() {
    delete[] seller_history;        //deleting it.
}

const Buyer& Buyer::operator=(const Buyer& other) {
    if(this != &other){
        delete[] seller_history;
        username = other.username;
        password = other.password;
        fname = other.fname;
        lname = other.lname;
        address = other.address;
        cart = other.cart;
        copySellerHistory(other);
        seller_history_size = other.seller_history_size;
        total_price = other.total_price;
    } else {
        return *this;
    }
}

///Getters and Setters------------------------------------------------------
ItemList Buyer::getCart() const {
    return cart;
}

const string *Buyer::getSellerHistory() const {
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
    cart.addToTail(new_item);                                               //Adding the new item to the end of the list
    this->total_price += new_item->GetPrice() * new_item->GetQuantity();    //Updating the buyer's price.
}

bool Buyer::isEmptyCart() {
    return cart.isEmpty();
}


///Seller History Functions-------------------------------------------------
//A function which adds an array of strings to the history of the buyer.
//Used for the feedback
void Buyer::addToSellerHistory(string *seller_names, int size_of_seller_names) {
    int index = 0;
    bool to_add = true;

    string *after_erase_dup = new string[size_of_seller_names];
    //char** AfterEaraseDup = new char* [size_of_seller_names];    //freeing memory in makeNewSellerHistory func
    for (int i = 0; i < size_of_seller_names; i++) {             //Going through the array of strings
        for (int j = 0; j < seller_history_size; j++) {          //Checking the seller already exists in the history
            to_add = (seller_history[j] != seller_names[i]);
        }
        if (to_add) {                                           //If the seller does not exist in the history
            after_erase_dup[index] = seller_names[i];
            index++;
        }
    }
    makeNewSellerHistory(after_erase_dup, index);
}

//A function which creates a new seller history array.
void Buyer::makeNewSellerHistory(string *after_erase_dup, int size) {

    string* new_seller_history = new string[size + seller_history_size];
    for (int i = 0; i < seller_history_size;i++) {
        new_seller_history[i] = seller_history[i];
    }
    for (int i = 0; i < size; i++) {
        new_seller_history[i + seller_history_size] = after_erase_dup[i];
    }
    delete[] this->seller_history;
    delete[] after_erase_dup;
    this->seller_history = new_seller_history;
    this->seller_history_size = size + seller_history_size;
}

/*void Buyer::emptySellerHistory() {
    for(int i = 0; i < seller_history_size; ++i) {
        delete seller_history[i];
    }
}*/

void Buyer::copySellerHistory(const Buyer& other) {
    if (other.seller_history_size > 0) {
        seller_history = new string[other.seller_history_size];
        for (int i = 0; i < other.seller_history_size; ++i) {
            seller_history[i] = other.seller_history[i];
        }
    }
    else {
        this->seller_history_size = 0;
        this->seller_history = nullptr;
    }
}

void Buyer::deleteItemFromCart(const string& item_name) {
    Item* item_to_delete;
    item_to_delete = cart.findItem(item_name);              //Finding the item to delete.
    total_price = total_price - (item_to_delete->GetPrice() * item_to_delete->GetQuantity());  //Decreasing the total price.
    cart.deleteItem(item_name);
}


///Printing Functions--------------------------------------------------------
void Buyer::printSellerHistory() const {
    cout << "Buyer : "<< endl << this->username<< endl << "Seller's History:" << endl;
    for (int i = 0; i < this->seller_history_size;i++) {
        cout << this->seller_history[i] <<endl;
    }

}

const char* Buyer::getType()const {
    return "Buyer";
}

Account* Buyer::clone() const {
    return new Buyer(*this);
}
