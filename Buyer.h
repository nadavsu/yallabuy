//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_BUYER_H
#define ECOMMERCE_BUYER_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include "Address.h"
#include "ItemList.h"
#include "Account.h"
#include "CUI.h"

class Buyer : virtual public Account {
protected:
    ItemList        cart;         //A linked list of Items, cart points to head of list.
    vector<string>  seller_history;
    int             total_price;
public:
    Buyer(const string& username, const string& password, const string& fname, const string& lname, Address& address);
    //Buyer(const Buyer& other);
    //Buyer(Buyer&& other);
    //virtual ~Buyer();

    //const Buyer& operator=(const Buyer& other);
    bool operator>(const Buyer& other) const;
    friend ostream& operator<<(ostream& out ,Buyer& b);
    void toOs(ostream& os)             const override;

public:
    Item*           getCartHead();
    ItemList        getCart()              const;
    vector<string>  getSellerHistory()     const;
    int             getTotalPriceOfCart()  const;

    void printSellerHistory()              const;

    bool isEmptyCart();
    void addToCart(Item* new_item);
    void deleteItemFromCart(const string& item_name);

    void makeNewSellerHistory(vector<string>& after_erase_dup);
    //void copySellerHistory(const Buyer& other);
    void addToSellerHistory(const vector<string>& seller_names);
    virtual const char* getType() const;
    virtual Account* clone() const override;
    void saveBuyerToFile(ofstream& OutFile);

    friend class Manager;
};


#endif //ECOMMERCE_BUYER_H
