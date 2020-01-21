//
// Created by Nadav Suliman on 10/1/20.
//

#include "Account.h"

///Constructors & Destructors--------------------------------------------------------------
Account::Account(const string& username, const string& password, const string& fname, const string& lname,
                 const Address& address) : address(address), username(username), password(password), fname(fname),
                 lname(lname) {
}

Account::~Account() {

}

/*Account::Account(const Account& other) : address(other.address) {
    setUsername(other.username);
    setPassword(other.password);
    setFName(other.fname);
    setLName(other.lname);
}*/

/*Account::Account(const Account& other) : address(other.address) {}              //TODO: Do we need to remove this?

Account::Account(Account&& other) : address(std::move(other.address)) {}*/

///Operators----------------------------------------------------------------------
/*const Account &Account::operator=(const Account &other) {
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
    } else {
        return *this;
    }
}*/

ostream& operator<<(ostream& os, Account& base) {
    if (typeid(os) == typeid(ofstream)) {
        const char* TypeName = typeid(base).name();
        os << TypeName << " " << base.username << " " << base.password << " "
            << base.fname << " " << base.lname << " "
            << base.address.getCity() << " " << base.address.getStreet() << " " << base.address.getHomeNumber() << endl;
    }
    else {
        os << "Username: " << base.username << endl;
        os << "Name: " << base.fname << " " << base.lname << endl;
        os << "Address: " << base.address << endl;
        base.toOs(os);
    }
    return os;
}

void Account::toOs(ostream &os) const {

}

///Getters and setters---------------------------------------------------------------------
const string& Account::getUsername() const {
    return username;
}

const string&Account::getPassword() const {
    return password;
}

const string& Account::getLName() const {
    return lname;
}

const string& Account::getFName() const {
    return fname;
}

const Address &Account::getAddress() const {
    return address;
}

bool Account::setFName(const string& new_fname) {
    if (new_fname.length() <= FNAME_MAX_LEN) {
        this->fname = new_fname;
        return true;
    }
    return false;
}

bool Account::setLName(const string& new_lname) {
    if (new_lname.length() <= LNAME_MAX_LEN) {
        this->lname = new_lname;
        return true;
    }
    return false;
}


bool Account::setUsername(const string& new_username) {
    if (new_username.length() <= USERNAME_MAX_LEN) {
        this->username = new_username;
        return true;
    }
    return false;
}

bool Account::setPassword(const string& new_password) {
    if (new_password.length() <= PASSWORD_MAX_LEN && new_password.length() >=PASSWORD_MIN_LEN) {
        this->password = new_password;
        return true;
    }
    return false;
}

void Account::setAddress(const Address &new_address) {
    address.setHomeNumber(new_address.getHomeNumber());
    address.setStreet(new_address.getStreet());
    address.setCity(new_address.getCity());
}
