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

using namespace std;
static constexpr int sFEEDBACK_MAX = 30;
static constexpr int sPASSWORD_MAX_LEN = 20;
static constexpr int sPASSWORD_MIN_LEN = 6;
static constexpr int sUSERNAME_MAX_LEN = 20;
static constexpr int sUSERNAME_MIN_LEN = 1;
static constexpr int sFNAME_MAX_LEN = 20;
static constexpr int sFNAME_MIN_LEN = 2;
static constexpr int sLNAME_MAX_LEN = 25;
static constexpr int sLNAME_MIN_LEN = 2;


class Seller {
    friend class Manager;
public:
    enum ePasswordStrength {
        match_username, too_short, too_long, One_out_of_Five, Two_out_of_Five,
        Three_out_of_Five, Four_out_of_Five, Five_out_of_Five
    };

    bool setFName(const char* new_fname);
    bool setLName(const char* new_lname);
    bool setUsername(const char* new_username);
    bool setAddress(const Address& new_address);
    bool setPassword(const char* new_password);
    void setFeedback(const Feedback& buyers_feedback);
    void setItem(Item* seller_item);


    const char* getFName()           const;
    const char* getLName()           const;
    const char* getUsername()        const;
    Address getAddress()             const;
    Feedback** getFeedback()         const;
    ItemList getStock()              const;
    void printStock()                const;
    void printSeller()               const;

    Item* getItemToBuyer(const char* item_name, int quantity);
    bool itemExist(const char* item_name)  ;
    bool quantityIsFine(const char* item_name, int quantity);
    bool isEmptyCart();

private:
    Item* getItem(const char* item_name);
    const char* getPassword()     const;
    void copyFeedback(const Seller& other);
    //ePasswordStrength strengthChecker(const char* Password)    const;
private:

    char*        username;
    char*        password;
    char*        fname;
    char*        lname;
    Address      address;
    Feedback**   feedbacks;
    ItemList     stock_list;        //Linked list of ordered_items.
    int          num_of_feedbacks;

public:
    Seller(char *username, char *password, char *fname, char *lname, Address address);
    Seller(const Seller& other); // dont want anyone to copy check what to do
    Seller(Seller&& other);
    ~Seller();

    const Seller& operator=(const Seller& other);
};


#endif //ECOMMERCE_SELLER_H
