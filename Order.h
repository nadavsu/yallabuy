//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_ORDER_H
#define ECOMMERCE_ORDER_H
#define _CRT_SECURE_NO_WARNINGS
#include "ItemList.h"
#include <string.h>

class Order{
public:
    Order() = default;
    Order(const string& name_of_buyer);
    Order(const Order& other);
    Order(Order&& other);
    ~Order();
    const Order& operator=(const Order& other);

	void SetNameOfBuyer(const string& name_of_buyer);
    //void setItem(Item* item);
    void setItemList(ItemList list);

    void updatePrice();
    void updateSellerHistory();

    void printCart();

    string* getNameOfSellers();
    ItemList getOrderedItems();
    int getNumOfSellers();
    Item* getOrderedItemsHead(); // check if to move to private

private:
    void addToNameOfSellers(const string& seller_name);
    void makeNewNameOfSellers(const string& seller_name);
    void copyNameOfSellers(const Order& other);

private:
    string      name_of_buyer;
    string*     name_of_sellers;
    int         total_price;
    int         num_of_sellers;
    ItemList    ordered_items; // head of linked list

};



#endif //ECOMMERCE_ORDER_H
