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
#include "Feedback.h"
#include "ItemList.h"
#include "Account.h"
#include "CUI.h"
#include "Array.h"

using namespace std;

class Seller : virtual public Account {
protected:
    Array<Feedback*>   feedbacks;
    list<Item*>        stock_list;        //Linked list of ordered_items.

public:
    enum ePasswordStrength {
        match_username, too_short, too_long, One_out_of_Five, Two_out_of_Five,
        Three_out_of_Five, Four_out_of_Five, Five_out_of_Five
    };

public:
    Seller(ifstream& os);
    Seller(const string& username, const string& password, const string& fname, const string& lname, Address& address);
    Seller(const Seller& other); // dont want anyone to copy check what to do
    Seller(Seller&& other);
    virtual ~Seller();

    const Seller& operator=(const Seller& other);
    friend ifstream& operator>>(ifstream& in, Seller& s);
    //friend ostream& operator<<(ostream& out, Seller& s);
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

    virtual const string& getType()    const;
    virtual Account* clone()         const override;
private:
    list<Item*>::iterator getItem(const string& item_name);
    void copyFeedback(Seller& other);
    //ePasswordStrength strengthChecker(const char* Password)    const;

    friend class Manager;
};


#endif //ECOMMERCE_SELLER_H
