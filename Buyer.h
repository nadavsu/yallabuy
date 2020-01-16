//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_BUYER_H
#define ECOMMERCE_BUYER_H
#define _CRT_SECURE_NO_WARNINGS
#include "Address.h"
#include "ItemList.h"
#include "Account.h"
#include "CUI.h"

class Buyer : virtual public Account {
protected:
    ItemList    cart;         //A linked list of Items, cart points to head of list.
    char        **seller_history;
    int         seller_history_size;
    int         total_price;
public:
    Buyer(const char* username, const char* password, const char* fname, const char* lname, Address& address);
    Buyer(const Buyer& other);
    Buyer(Buyer&& other);
    virtual ~Buyer();

    const Buyer& operator=(const Buyer& other);
    bool operator>(const Buyer& other) const;
    void toOs(ostream& os)             const;

public:
    Item*       getCartHead();
    ItemList    getCart()              const;
    char**      getSellerHistory()     const;
    int         getNumOfSellers()      const;
    int         getTotalPriceOfCart()  const;

    void printCart()                   const;
    void printSellerHistory()          const;

    bool isEmptyCart();
    void addToCart(Item* new_item);
    void deleteItemFromCart(const char* item_name);

    void makeNewSellerHistory(char** AfterEaraseDup, int size_of_AfterEaraseDup);
    void emptySellerHistory();
    void copySellerHistory(const Buyer& other);
    void addToSellerHistory(char** seller_name, int size_of_seller_name);
    virtual const char* getType() const;
    virtual Account* clone() const override;

    friend class Manager;
};


#endif //ECOMMERCE_BUYER_H
