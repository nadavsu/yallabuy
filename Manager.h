//
// Created by Nadav Suliman on 19/12/19.
//

#ifndef ECOMMERCE_MANAGER_H
#define ECOMMERCE_MANAGER_H

#include "Buyer.h"
#include "Seller.h"
#include "Order.h"
#include "Date.h"
#include "Feedback.h"
#include "CUI.h"
#include "BuyerSeller.h"

class Manager {
private:
	Account** account_arr;
	int curr_account;           //TODO: change this to num_of_accounts?
	int num_of_buyers;
	int num_of_sellers;
	int num_of_buyersellers;
	int max_account;

public:
	Manager();
	Manager(Manager& other) = delete;
	~Manager();
	const Manager& operator+=(Account* other);

	int getNumOfAccounts()      const;
    int getNumOfSellers()       const;
    int getNumOfBuyers()        const;
    int getNumOfBuyerSellers()  const;

	bool login(const char* username, const char* password) const;
	Account* getAccount(const char* username);
	void addAccout(Account* temp);
	//void AddBuyer(Account& new_account);
	//void AddSeller(Account& new_account);
    void addFeedback(const Feedback& feedback, const char *seller_username);
	void AddItem(const char* seller_username, const Item& new_item);
	void printBuyerCart(const char *buyer_username);
    void payOrder(const char* buyer_username, Order& order);

    bool sellerExistInBuyerSeller(const char *buyer_username, const char *seller_username);
    bool buyerIsCartEmpty(const char *buyer_username);
	bool sellerIsStockEmpty(const char* seller_username);
	bool isItemExistInSeller(const char* seller_username,const char* item_name_to_buy);
	bool sellerIsQuantityFine(const char* seller_username,const char* item_name_to_buy,int quantity);
	void addItemToCart(const char* buyer_username, const char* seller_username, const char* item_name_to_buy, int quantity);
	void printSellerShop(const char* seller_username);
    void copyCartToOrder(Order& order, const char *buyer_username);
    bool printItemsNamed(const char *item_name);
	bool isSellerExist(char* seller_username);
    void printBuyerSellerHistory(const char *buyer_username);
	void printBuyers()  const;
	void printSellers() const;
	void printBuyerSellers()const;
	void printAccount()const;

	bool testCompareOperator(const char *username_1, const char *username_2);
	bool testPrintCart(const char *buyer_username);
	bool testPrintAccount(const char *username);
    void _debugfill();
private:
	Item* getItemFromSellerToBuyer(const char* seller_username, const char* item_name_to_buy, int quantity);
    void my_realloc();
};


#endif //ECOMMERCE_MANAGER_H
