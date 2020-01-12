#ifndef ECOMMERCE_ACCOUNT_H
#define ECOMMERCE_ACCOUNT_H


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
    char*       username;
    char*       password;
    char*       lname;
    char*       fname;
    Address     address;

public:
    Account(const char *username,const char *password,const char *fname,const char *lname,const Address& address);
    virtual ~Account();
    Account(const Account& other);
    Account(Account&& other);
    const Account& operator=(const Account& other);
    friend ostream& operator<<(ostream& os, Account& base);

public: //Setters & Getters
    char *getUsername()         const;
    char *getPassword()         const;
    char *getLName()            const;
    char *getFName()            const;
    const Address& getAddress() const;

    bool setUsername(const char *username);
    bool setPassword(const char *password);
    bool setLName(const char *lname);
    bool setFName(const char *fname);
    void setAddress(const Address &address);

    virtual Account* clone() const = 0;

    friend class Manager;
};


#endif //ECOMMERCE_ACCOUNT_H
