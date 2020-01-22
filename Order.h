//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_ORDER_H
#define ECOMMERCE_ORDER_H
#define _CRT_SECURE_NO_WARNINGS
#include "ItemList.h"
#include <string.h>
#include <vector>
#include <list>
#include <algorithm>

class Order{
public:
    Order() = default;
    explicit Order(const string& name_of_buyer);
    Order(const Order& other);
    //Order(Order&& other);
    ~Order();
    //const Order& operator=(const Order& other);

	void SetNameOfBuyer(const string& name_of_buyer);
    //void setItem(Item* item);
    void setItemList(const list<Item*>& list);

    void updatePrice();
    void updateSellerHistory();

    void printCart();

    const vector<string>& getNameOfSellers() const;
    const list<Item*>& getOrderedItems();
    int getNumOfSellers();
    Item* getOrderedItemsHead(); // check if to move to private

private:
    void addToNameOfSellers(const string& seller_name);
    //void makeNewNameOfSellers(const string& seller_name);
    //void copyNameOfSellers(const Order& other);

private:
    string          name_of_buyer;
    vector<string>  name_of_sellers;
    list<Item*>     ordered_items; // head of linked list
    int             total_price;
    int             num_of_sellers;

};



#endif //ECOMMERCE_ORDER_H
