//
// Created by Nadav Suliman on 24/11/19.
//
#ifndef ECOMMERCE_SELLER_H
#define ECOMMERCE_SELLER_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "Address.h"
#include "Feedback.h"
#include "ItemList.h"
#include "Account.h"
#include "CUI.h"
using namespace std;

class Seller : virtual public Account {
protected:
    Feedback**   feedbacks;
    ItemList     stock_list;        //Linked list of ordered_items.
    int          num_of_feedbacks;

public:
    enum ePasswordStrength {
        match_username, too_short, too_long, One_out_of_Five, Two_out_of_Five,
        Three_out_of_Five, Four_out_of_Five, Five_out_of_Five
    };

public:
    Seller(const string& username, const string& password, const string& fname, const string& lname, Address& address);
    Seller(const Seller& other); // dont want anyone to copy check what to do
    Seller(Seller&& other);
    virtual ~Seller();

    const Seller& operator=(const Seller& other);
    friend ostream& operator<<(ostream& out, Seller& s);
    void setFeedback(const Feedback& buyers_feedback);
    void setItem(Item* seller_item);

public:
    Feedback** getFeedback()         const;
    ItemList getStock()              const;
    void printStock()                const;

    Item* getItemToBuyer(const string& item_name, int quantity);
    bool itemExist(const string& item_name)  ;
    bool quantityIsFine(const string& item_name, int quantity);
    bool isEmptyStock();
    virtual Account* clone() const override;
    virtual const char *getType() const;
private:
    Item* getItem(const string& item_name);
    void copyFeedback(const Seller& other);
    //ePasswordStrength strengthChecker(const char* Password)    const;

    friend class Manager;
};


#endif //ECOMMERCE_SELLER_H
