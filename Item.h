//
// Created by Nadav Suliman on 24/11/19.
//
#define _CRT_SECURE_NO_WARNINGS
#ifndef ECOMMERCE_ITEM_H
#define ECOMMERCE_ITEM_H

#include <iostream>
using namespace std;
static constexpr int ITEM_MAX_NAME_LEN = 30;
static constexpr int MAX_ITEM_NAME = 20;
static constexpr int MAX_CATEGORY_NAME = 15;
static constexpr int ITEM_MAX = 50;


class Item {
friend class Seller;
friend class Buyer;
friend class Manager;
public:
	enum eCategory{Electronics = 0, Home, Garden, Games};

	void SetName(const string& name);
	void SetNameOfSeller(const string& name_of_seller);
	void SetCategory(eCategory category);
	void SetPrice(int price);
	void SetQuantity(int quantity);

	const string& GetName()         const;
    const string& getSellerName()   const;
    int GetPrice()                  const;
    int GetSerialNumber()           const;
    int GetQuantity()               const;
    Item* getNext()                 const;
    eCategory GetCategory()         const;
    void printItem()                const;
    void reduceQuantity(int reduction);


private:
    static int num_of_items;            //For the serial number.
    string name;
    string name_of_seller;
    eCategory category;
    int price;
    int serial_number;
    int quantity;
    Item* next;

public:
    Item(const string& name_of_seller, const string& name, eCategory category, int price, int quantity);
    //Item(const Item& other);
    //Item(Item&& other);
    //~Item();

    //const Item& operator=(const Item& other);
    friend ostream& operator<<(ostream& os, const Item& item);
};

#endif //ECOMMERCE_ITEM_H
