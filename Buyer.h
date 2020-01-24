//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_BUYER_H
#define ECOMMERCE_BUYER_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include<string>
#include "Address.h"
#include "Account.h"
#include "CUI.h"
#include "Item.h"

class Buyer : virtual public Account {
protected:
    list<Item*>      cart;
    vector<string>  seller_history;
    int             total_price;
public:
    Buyer(ifstream& os);
    Buyer(const string& username, const string& password, const string& fname, const string& lname, Address& address);
    Buyer(const Buyer& other);
    Buyer(Buyer&& other);
    virtual ~Buyer();

    bool operator>(const Buyer& other) const;
    friend ifstream& operator>>(ifstream& in, Buyer& b);
    virtual void toOs(ostream& os)             const override;

public:
    Item*           getCartHead();
    list<Item*>     getCart()              const;
    vector<string>  getSellerHistory()     const;
    int             getTotalPriceOfCart()  const;

    void printSellerHistory()              const;
    void printCart()                       const;

    bool isEmptyCart();
    void addToCart(Item* new_item);
    void deleteItemFromCart(const string& item_name);
    list<Item*>::iterator findItem(const string& item_name);

    void makeNewSellerHistory(vector<string>& after_erase_dup);
    void addToSellerHistory(const vector<string>& seller_names);
    virtual const string getType() const;
    virtual Account* clone() const override;

    friend class Manager;
};


#endif //ECOMMERCE_BUYER_H
