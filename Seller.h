//
// Created by Nadav Suliman on 24/11/19.
//
#ifndef ECOMMERCE_SELLER_H
#define ECOMMERCE_SELLER_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <list>
#include "Address.h"
#include "Item.h"
#include "Feedback.h"
#include "Account.h"
#include "CUI.h"
#include "Array.h"

using namespace std;

class Seller : virtual public Account {
protected:
    Array<Feedback*>   feedbacks;
    list<Item*>        stock_list;

public:
    Seller(ifstream& os);
    Seller(const string& username, const string& password, const string& fname, const string& lname, Address& address);
    Seller(const Seller& other);
    Seller(Seller&& other);
    virtual ~Seller();

    const Seller& operator=(const Seller& other);
    friend ifstream& operator>>(ifstream& in, Seller& s);
    virtual void toOs(ostream& out) const override;
    void setFeedback(const Feedback& buyers_feedback);
    void setItem(Item* seller_item);

public:
    Array<Feedback*> getFeedback()         const;
    list<Item*> getStock()                 const;
    void printStock()                      const;

    bool isEmptyStock()              const;
    Item* getItemToBuyer(const string& item_name, int quantity);
    bool itemExist(const string& item_name)  ;
    bool quantityIsFine(const string& item_name, int quantity);

    virtual const string getType()    const;
    virtual Account* clone()         const override;
private:
    list<Item*>::iterator getItem(const string& item_name);

    friend class Manager;
};


#endif //ECOMMERCE_SELLER_H
