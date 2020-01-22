//
// Created by Nadav Suliman on 24/11/19.
//

#include "Order.h"

Order::Order(const string& name_of_buyer) : name_of_buyer(name_of_buyer) {
	total_price = 0;
}

Order::Order(const Order& other) : name_of_buyer(other.name_of_buyer), name_of_sellers(other.name_of_sellers) {
	this->total_price = other.total_price;
	this->num_of_sellers = other.num_of_sellers;
	this->ordered_items = other.ordered_items;
	for (auto item : other.ordered_items) {
	    ordered_items.push_back(new Item(*item));
	}
}

/*void Order::copyNameOfSellers(const Order& other) {
	name_of_sellers = new string[other.num_of_sellers];
	for (int i = 0; i < other.num_of_sellers; i++) {
		name_of_sellers[i] = other.name_of_sellers[i];
	}
}*/

/*Order::Order(Order&& other) : ordered_items(other.ordered_items), name_of_buyer(move(other.name_of_buyer)) {
	name_of_sellers = other.name_of_sellers;
	this->num_of_sellers = other.num_of_sellers;
	this->total_price = other.total_price;
	name_of_sellers = nullptr;
}*/

Order::~Order() {
    auto item_itr = ordered_items.begin();
    while (item_itr != ordered_items.end()) {
        auto temp = item_itr;
        ++temp;
        delete *item_itr;
        item_itr = temp;
    }
}

/*
const Order& Order::operator=(const Order& other) {
	if (this != &other) {
		delete name_of_sellers;
		name_of_buyer = other.name_of_buyer;
		copyNameOfSellers(other);
		total_price = other.total_price;
		num_of_sellers = other.num_of_sellers;
		ordered_items = other.ordered_items;
	}
	else {
		return *this;
	}
}*/

void Order::SetNameOfBuyer(const string& name_of_buyer) {
	this->name_of_buyer = name_of_buyer;
}

void Order::updatePrice() {
    for (auto item : ordered_items) {
        total_price += item->GetPrice() * item->GetQuantity();
    }
}

void Order::updateSellerHistory() {
    for (auto item : ordered_items) {
        if(item->GetQuantity() > 0) {
            addToNameOfSellers(item->getSellerName());
        }
    }
}

void Order::setItemList(const list<Item*>& list) {
	for (auto item : list) {
        ordered_items.push_back(new Item (*item));
	}
}

void Order::printCart() {
	for (auto item : ordered_items) {
	    cout << *item;
	}
}

const vector<string>& Order::getNameOfSellers() const {
	return name_of_sellers;
}

const list<Item*>& Order::getOrderedItems() {
	return ordered_items;
}
int Order::getNumOfSellers() {
	return num_of_sellers;
}

Item* Order::getOrderedItemsHead() {
	return *ordered_items.begin();
}

void Order::addToNameOfSellers(const string& seller_name) {
    auto found = find(name_of_sellers.begin(), name_of_sellers.end(), seller_name);
    if (found == name_of_sellers.end()) {
        return;
    }
    name_of_sellers.push_back(seller_name);
    num_of_sellers++;
}

/*
void Order::makeNewNameOfSellers(const string& seller_name) {
	num_of_sellers++;
	string* new_name_of_sellers = new string[num_of_sellers];
	for (int i = 0; i < num_of_sellers - 1; i++) {
		new_name_of_sellers[i] = name_of_sellers[i];
	}
	new_name_of_sellers[num_of_sellers - 1] = seller_name;
	delete[]name_of_sellers;
	name_of_sellers = new_name_of_sellers;
}*/
