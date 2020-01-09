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
	Order order;
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
	Seller* GetSeller(const char* username);
	void AddBuyer(Buyer& new_buyer);
	void AddSeller(Seller& new_seller);
    void AddFeedback(const char* seller_to_feed, const Feedback& new_feedback);
    void AddItem(const char* seller_username,const Item& new_item);
    void addItemToCart(const char* buyer_username, Item item);
    bool MakeOrder(const char* buyer_username);
	void printBuyerCart(Buyer* buyer);
    void payOrder(const char* buyer_username, Order& to_order);

	bool printItemsNamed(const char *item_name);
    void printBuyers()  const;
    void printSellers() const;
    void printBuyerSellerHistory(const char *buyer_username);

private:
    void my_realloc(void *arr, int max_size, int curr_size);
};


#endif //ECOMMERCE_MANAGER_H
