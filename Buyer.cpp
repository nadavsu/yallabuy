//
// Created by Nadav Suliman on 24/11/19.
//

#include "Buyer.h"
using namespace std;

///Constructors and Destructors------------------------------------------
Buyer::Buyer(ifstream& os) : Account(os){
    os >> *this;
}
Buyer::Buyer(const string& username, const string& password, const string& fname, const string& lname, Address& address)
                                                                : Account(username, password, fname, lname, address) {
    this->total_price = 0;
}

//Copy ctor
Buyer::Buyer(const Buyer& other) : Account(other), total_price(other.total_price), seller_history(other.seller_history) {
    for (auto item : other.cart) {
        cart.push_back(new Item(*item));
    }
}

//Move ctor
Buyer::Buyer(Buyer&& other) : Account(std::move(other)), cart(std::move(other.cart)), total_price(other.total_price) {
    seller_history = move(other.seller_history);
}

Buyer::~Buyer() {
    auto item_itr = cart.begin();
    while (item_itr != cart.end()) {
        auto temp = item_itr;
        ++temp;
        delete *item_itr;
        item_itr = temp;
    }
}

void Buyer::toOs(ostream& os) const {
    if (typeid(os) == typeid(ofstream)) {
        os << seller_history.size() << endl; // add if size_of_feedback == 0
        for (auto s : seller_history) {
            os << s << endl;
        }
    } else {
        os << "Cart total: " << total_price << endl;
    }
}
bool Buyer::operator>(const Buyer& other) const {
    return this->getTotalPriceOfCart() > other.getTotalPriceOfCart();
}
ifstream& operator>>(ifstream& in, Buyer& b) {
    if (typeid(in) == typeid(ifstream)) {
        //in >> (Account&)b;
        char trash;
        int size;
        in >> size;
        in.getline(&trash,1);
        b.seller_history.reserve(size);
        for (int i = 0; i < size; i++) {
            string curr;
            getline(in, curr);
            b.seller_history.push_back(curr);
        }
        return in;
    }
}

/*ostream& operator<<(ostream& out, Buyer& b) {
    if (typeid(out) == typeid(ofstream)) {
        out << (Account&)b;
        out << b.seller_history.size() << endl; // add if size_of_feedback == 0
        for (auto s : b.seller_history) {
            out << s << endl;
        }
    } else {
        out << (Account&)b;
    }
    return out;
}*/

/*const Buyer& Buyer::operator=(const Buyer& other) {
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
}*/

///Getters and Setters------------------------------------------------------
list<Item*> Buyer::getCart() const {
    return cart;
}

vector<string> Buyer::getSellerHistory() const {
    return seller_history;
}



Item* Buyer::getCartHead() {
    return *cart.begin();
}

int Buyer::getTotalPriceOfCart() const  {
    return total_price;
}

///Cart Functions----------------------------------------------------------
void Buyer::addToCart(Item* new_item) {
    cart.push_back(new_item);                                               //Adding the new item to the end of the list
    this->total_price += new_item->GetPrice() * new_item->GetQuantity();    //Updating the buyer's price.
}

bool Buyer::isEmptyCart() {
    return cart.empty();
}

list<Item*>::iterator Buyer::findItem(const string& item_name) {
    auto item_itr = cart.begin();
    for (; item_itr != cart.end(); ++item_itr) {
        if((*item_itr)->GetName() == item_name) {
            return item_itr;
        }
    }
    return item_itr;
}

///Seller History Functions-------------------------------------------------
//A function which adds an array of strings to the history of the buyer.
//Used for the feedback
//TODO: CHECK THIS FUNCTION!!! or at least change it - we can use <algorithms>
void Buyer::addToSellerHistory(const vector<string>& seller_names) {
    bool to_add = true;
    vector<string> after_erase_dup;
    //string *after_erase_dup = new string[size_of_seller_names];
    //char** AfterEaraseDup = new char* [size_of_seller_names];    //freeing memory in makeNewSellerHistory func
    for (auto& new_history : seller_names) {                           //Going through the array of strings
        for (auto& old_history : seller_history) {                   //Checking the seller already exists in the history
            to_add = (new_history != old_history);
        }
        if (to_add) {                                           //If the seller does not exist in the history
            after_erase_dup.push_back(new_history);
        }
    }
    makeNewSellerHistory(after_erase_dup);
    after_erase_dup.clear();
}

//A function which creates a new seller history array.
void Buyer::makeNewSellerHistory(vector<string>& after_erase_dup) {

    vector<string> new_seller_history = seller_history;
    for (auto& i : after_erase_dup) {
        new_seller_history.push_back(i);
    }
    this->seller_history.clear();
    this->seller_history = new_seller_history;
}

/*void Buyer::emptySellerHistory() {
    for(int i = 0; i < seller_history_size; ++i) {
        delete seller_history[i];
    }
}*/

/*void Buyer::copySellerHistory(const Buyer& other) {
    for (auto& seller_name : other.seller_history) {
        seller_history.push_back(seller_name);
    }
}*/

void Buyer::deleteItemFromCart(const string& item_name) {
    auto item_itr = findItem(item_name);
    if (item_itr != cart.end()) {
        total_price = total_price - ((*item_itr)->GetPrice() * (*item_itr)->GetQuantity());
        delete *item_itr;
        cart.erase(item_itr);
    }
/*    Item* item_to_delete;
    item_to_delete = cart.findItem(item_name);              //Finding the item to delete.
    total_price = total_price - (item_to_delete->GetPrice() * item_to_delete->GetQuantity());  //Decreasing the total price.
    cart.deleteItem(item_name);*/
}


///Printing Functions--------------------------------------------------------
void Buyer::printSellerHistory() const {
    cout << "Buyer : "<< endl << this->username<< endl << "Seller's History:" << endl;
    for (auto& s : seller_history) {
        cout << s << endl;
    }

}

void Buyer::printCart() const {
    cout << username << "'s Cart:\n";
    for (auto item : cart) {
        cout << *item << endl;
    }
}

const string Buyer::getType() const {
    return "Buyer";
}

Account* Buyer::clone() const {
    return new Buyer(*this);
}
