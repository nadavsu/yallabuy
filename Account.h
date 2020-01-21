#ifndef ECOMMERCE_ACCOUNT_H
#define ECOMMERCE_ACCOUNT_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "Address.h"
#include "ItemList.h"
using namespace std;

static constexpr int PASSWORD_MAX_LEN = 20;
static constexpr int PASSWORD_MIN_LEN = 6;
static constexpr int USERNAME_MAX_LEN = 20;
static constexpr int USERNAME_MIN_LEN = 1;
static constexpr int FNAME_MAX_LEN = 20;
static constexpr int FNAME_MIN_LEN = 2;
static constexpr int LNAME_MAX_LEN = 25;
static constexpr int LNAME_MIN_LEN = 2;

class Account {
protected:
    string      username;
    string      password;
    string      lname;
    string      fname;
    Address     address;

public:
    Account(const string& username, const string& password, const string& fname, const string& lname ,const Address& address);
    virtual ~Account();
    //Account(const Account& other);
    //Account(Account&& other);
    //const Account& operator=(const Account& other);
    friend ostream& operator<<(ostream& os, Account& base);
    virtual void toOs(ostream& os) const;

public: //Setters & Getters
    const string& getUsername()         const;
    const string& getPassword()         const;
    const string& getLName()            const;
    const string& getFName()            const;
    const Address& getAddress() const;

    bool setUsername(const string& username);
    bool setPassword(const string& password);
    bool setLName(const string& lname);
    bool setFName(const string& fname);
    void setAddress(const Address &address);

    virtual Account* clone() const = 0;

    friend class Manager;
};


#endif //ECOMMERCE_ACCOUNT_H
