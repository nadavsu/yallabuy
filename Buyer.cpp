//
// Created by Nadav Suliman on 24/11/19.
//

#include "Buyer.h"
using namespace std;

//Constructor
Buyer::Buyer(char *username, char *password, char *fname, char *lname, Address address) : address(address) {
    setUsername(username);
    setPassword(password);
    setFName(fname);
    setLName(lname);
    seller_history = nullptr;
    seller_history_size = 0;

}

//Copy ctor
Buyer::Buyer(const Buyer& other) : address(other.address), cart(other.cart) {
    setUsername(other.username);
    setPassword(other.password);
    setFName(other.fname);
    setLName(other.lname);
    copySellerHistory(other);
}

//Move ctor
Buyer::Buyer(Buyer&& other) : address(std::move(other.address)), cart(std::move(other.cart)) {
    username = other.username;
    password = other.password;
    fname = other.fname;
    lname = other.lname;
    seller_history = other.seller_history;
    seller_history_size = other.seller_history_size;

    other.username = nullptr;
    other.password = nullptr;
    other.fname = nullptr;
    other.lname = nullptr;
    other.seller_history = nullptr;
}

//dtor
Buyer::~Buyer() {
    delete[] username;
    delete[] password;
    delete[] fname;
    delete[] lname;
    emptySellerHistory();           //emptying the seller history.
    delete[] seller_history;        //deleting it.
}

const Buyer& Buyer::operator=(const Buyer& other) {
    if (this != &other) {
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
    }
    else {
        return *this;
    }
}


///The following are setters and getters.
bool Buyer::setFName(const char *new_fname) {
    if(strlen(new_fname) <= FNAME_MAX_LEN) {
        if(!fname) {
            delete[] fname;
        }
        fname = new char[strlen(new_fname) + 1];
        strcpy(fname, new_fname);
        return true;
    }
    return false;
}

bool Buyer::setLName(const char *new_lname) {
    if(strlen(new_lname) <= LNAME_MAX_LEN) {
        if(!lname) {
            delete[] lname;
        }
        lname = new char[strlen(new_lname) + 1];
        strcpy(lname, new_lname);
        return true;
    }
    return false;
}

bool Buyer::setUsername(const char *new_username) {
    if(strlen(new_username) <= USERNAME_MAX_LEN && strlen(new_username) >= USERNAME_MIN_LEN) {
        if(!username) {
            delete[] username;
        }
        username = new char[strlen(new_username) + 1];
        strcpy(username, new_username);
        return true;
    }
    return false;
}


bool Buyer::setPassword(const char *new_password) {
    if(strlen(new_password) <= PASSWORD_MAX_LEN && strlen(new_password) >= PASSWORD_MIN_LEN) {
        if(!password) {
            delete[] password;
        }
        password = new char[strlen(new_password) + 1];
        strcpy(password, new_password);
        return true;
    }
    return false;
}

void Buyer::setAddress(const Address& new_address) {
    address.setHomeNumber(new_address.getHomeNumber());
    address.setStreet(new_address.getStreet());
    address.setCity(new_address.getCity());
}


void Buyer::addToCart(const Item new_item) {
    cart.addToTail(new_item);
}

bool Buyer::removeFromCart(const char *name) {
    return cart.deleteItem(name);
}

bool Buyer::isEmptyCart() {
    return cart.isEmpty();
}


//A function used to add an array of strings to the history of the buyer.
//Used for the feedback
void Buyer::addToSellerHistory(char** seller_name,int size_of_seller_name) {
    int index = 0;
    bool To_add = true;
    bool found = false;
    char** AfterEaraseDup = new char* [size_of_seller_name]; // delete in makeNewSellerHistory func
    for (int i = 0; i < size_of_seller_name;i++) {
        for (int j = 0; j < seller_history_size || found == true;j++) {
            if (strcmp(seller_history[j], seller_name[i]) == 0) {
                found = true;
                To_add = false;
            }
            else {
                To_add = true;
            }
        }
        if (To_add == true) { // did the last compare
            AfterEaraseDup[index] = new char[strlen(seller_name[i]) + 1];
            strcpy(AfterEaraseDup[index] ,seller_name[i]);
            index++;
            To_add = false;
        }
        found = false;
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

}


const char *Buyer::getFName() const {
    return fname;
}

const char *Buyer::getLName() const {
    return lname;
}

const char *Buyer::getPassword() const {
    return password;
}

char **Buyer::getSellerHistory() const {
    return seller_history;
}

int Buyer::getNumOfSellers() const {
    return seller_history_size;
}

ItemList Buyer::getCart() const {
    return cart;
}

Address Buyer::getAddress() const {
    return address;
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


void Buyer::printBuyer() const {
    cout << "----------------------------------\n";
    cout << "Username: " << username << endl;
    cout << "Name: " << fname << " " << lname << endl;
    this->address.printAddress();
    cout << "----------------------------------\n";

}

void Buyer::printCart() const {
    if(cart.isEmpty()) {
        cout << "Your cart is empty!";
    } else {
        cart.printList();
    }
}
