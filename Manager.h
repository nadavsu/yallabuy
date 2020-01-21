//
// Created by Nadav Suliman on 19/12/19.
//

#ifndef ECOMMERCE_MANAGER_H
#define ECOMMERCE_MANAGER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Buyer.h"
#include "Seller.h"
#include "Order.h"
#include "Date.h"
#include "Feedback.h"
#include "CUI.h"
#include "BuyerSeller.h"

class Manager {
private:
	vector<Account*> account_arr;
	//int curr_account;           //TODO: change this to num_of_accounts?
	int num_of_buyers;
	int num_of_sellers;
	int num_of_buyersellers;
	//int max_account;

public:
	Manager();
	Manager(Manager& other) = delete;
	~Manager();
	const Manager& operator+=(Account* other);
	friend ostream& operator<<(ostream& os, Manager& base);

public:
	int getNumOfAccounts()      const;
    int getNumOfSellers()       const;
    int getNumOfBuyers()        const;
    int getNumOfBuyerSellers()  const;
    Account* getAccount(const string& username);

    bool login(const string& username, const string& password);
	void addAccount(Account* temp);
    void addFeedback(const Feedback& feedback, const string& seller_username);
	void AddItem(const string&  seller_username, const Item& new_item);
	void printBuyerCart(const string& buyer_username);
    void payOrder(const string& buyer_username, Order& order);

    bool buyerIsCartEmpty(const string& buyer_username);
    bool sellerExistInBuyerSeller(const string& buyer_username, const string& seller_username);
    bool sellerIsStockEmpty(const string& seller_username);
    bool sellerIsQuantityFine(const string& seller_username,const string& item_name_to_buy,int quantity);
    bool isSellerExist(string& seller_username);
    bool isItemExistInSeller(const string& seller_username,const string& item_name_to_buy);
    void addItemToCart(const string& buyer_username, const string& seller_username, const string& item_name_to_buy, int quantity);
    void copyCartToOrder(Order& order, const string& buyer_username);

    void printSellerShop(const string& seller_username);
	bool printItemsNamed(const string& item_name);
	void printBuyerSellerHistory(const string& buyer_username);
	void printBuyers()          const;
	void printSellers()         const;
	void printBuyerSellers()    const;
	void printAccount()         const;

	bool testCompareOperator(const string& username_1, const string& username_2);
	bool testPrintCart(const string& buyer_username);
	bool testPrintAccount(const string& username);
    void _debugfill();
private:
	Item* getItemFromSellerToBuyer(const string& seller_username, const string& item_name_to_buy, int quantity);
    void my_realloc();
};


#endif //ECOMMERCE_MANAGER_H
