//
// Created by Nadav Suliman on 10/1/20.
//

#include "Account.h"
Account::Account(const char* username, const char* password, const char* fname, const char* lname,const Address& address) : address(address) {
    setUsername(username);
    setPassword(password);
    setFName(fname);
    setLName(lname);
}

Account::Account(const Account& other) : address(other.address) {
    setUsername(other.username);
    setPassword(other.password);
    setFName(other.fname);
    setLName(other.lname);
}

Account::Account(Account&& other) : address(std::move(other.address)) {
    username = other.username;
    password = other.password;
    fname = other.fname;
    lname = other.lname;

    other.username  = nullptr;
    other.password  = nullptr;
    other.fname     = nullptr;
    other.lname     = nullptr;
}

Account::~Account() {
    delete[] username;
    delete[] password;
    delete[] fname;
    delete[] lname;
}

const Account& Account::operator=(const Account& other) {
    if (this != &other) {
        delete[] username;
        delete[] password;
        delete[] fname;
        delete[] lname;
        this->address = other.address;
        setFName(other.fname);
        setLName(other.lname);
        setUsername(other.username);
        setPassword(other.password);
    }
    else {
        return *this;
    }
}

ostream& operator<<(ostream& os, Account& base) {
    os << "Username: " << base.username << endl;
    os << "Name: " << base.fname << " " << base.lname << endl;
    os << "Address: " << base.address << endl;
    base.toOs(os);
    return os;
}

void Account::toOs(ostream &os) const {

}

char *Account::getUsername() const {
    return username;
}

char *Account::getPassword() const {
    return password;
}

char *Account::getLName() const {
    return lname;
}

char *Account::getFName() const {
    return fname;
}

const Address &Account::getAddress() const {
    return address;
}

bool Account::setFName(const char *new_fname) {
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

bool Account::setLName(const char *new_lname) {
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


bool Account::setUsername(const char *new_username) {
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

bool Account::setPassword(const char *new_password) {
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

void Account::setAddress(const Address& new_address) {
    address.setHomeNumber(new_address.getHomeNumber());
    address.setStreet(new_address.getStreet());
    address.setCity(new_address.getCity());
}
