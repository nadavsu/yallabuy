//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_BUYER_H
#define ECOMMERCE_BUYER_H

#define _CRT_SECURE_NO_WARNINGS
#include "Address.h"
#include "ItemList.h"

static constexpr int PASSWORD_MAX_LEN = 20;
static constexpr int PASSWORD_MIN_LEN = 6;

static constexpr int FNAME_MAX_LEN = 20;
static constexpr int FNAME_MIN_LEN = 2;
static constexpr int LNAME_MAX_LEN = 25;
static constexpr int LNAME_MIN_LEN = 2;


class Buyer {
    friend class Manager;
public:

    bool setFName(const char *fname);
    bool setLName(const char *lname);
    void setAddress(const Address& new_address);
    bool setPassword(const char *password);
    void addToSellerHistory(char** seller_name, int size_of_seller_name);
    void makeNewSellerHistory(char** AfterEaraseDup, int size_of_AfterEaraseDup);

    const char *getFName()          const;
    const char *getLName()          const;
    const char *getPassword()       const;
    Address getAddress()            const;
    char **getSellerHistory()       const;
    int getNumOfSellers()           const;
    ItemList getCart()              const;

    void printSellerHistory()       const;
    void printBuyer()               const;
    void printCart()                const;

    void addToCart(const Item new_item);
    bool isEmptyCart();
    bool removeFromCart(const char *item);
    void emptySellerHistory();
    void copySellerHistory(const Buyer& other);

        private:
    bool setUsername(const char *username);
    Buyer(const Buyer& other);

private:

    char      *username;
    char      *password;
    char      *fname;
    char      *lname;
    Address   address;
    ItemList  cart;         //A linked list of Items, cart points to head of list.
    char      **seller_history;
    int       seller_history_size;

public:

    Buyer(char *username, char *password, char *fname, char *lname, Address  address);
    Buyer(const Buyer& other);
    Buyer(Buyer&& other);
    ~Buyer();
    const Buyer& operator=(const Buyer& other);
};


#endif //ECOMMERCE_BUYER_H
