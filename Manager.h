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

class Manager {
private:
	Seller** arr_seller;
	Buyer** arr_buyer;
	int curr_buyer;
	int max_buyer;
	int curr_seller;
	int max_seller;

public:
	Manager();
	Manager(Manager& other) = delete;
	~Manager();

	bool loginBuyer(const char* username, const char* password) const;
	bool loginSeller(const char* username, const char* password) const;
	Buyer* getBuyer(const char* username); //return through copy const without any inside info like password
	Seller* getSeller(const char* username);
	void AddBuyer(Buyer& new_buyer);
	void AddSeller(Seller& new_seller);
    void addFeedback(const Feedback& feedback, const char *seller_username);
    void AddItem(const char* seller_username,const Item& new_item);
    void addItemToCart(const char *buyer_username, const Item& item);
	void printBuyerCart(const char *buyer_username);
    void payOrder(const char* buyer_username, Order& order);

    bool sellerExistInBuyerSeller(const char *buyer_username, const char *seller_username);
    bool isCartEmpty(const char *buyer_username);
    void copyCartToOrder(Order& order, const char *buyer_username);
    bool printItemsNamed(const char *item_name);
    void printBuyers()  const;
    void printSellers() const;
    void printBuyerSellerHistory(const char *buyer_username);

private:
    void my_realloc(void *arr, int max_size, int curr_size);
};


#endif //ECOMMERCE_MANAGER_H
