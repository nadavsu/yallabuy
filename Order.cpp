//
// Created by Nadav Suliman on 24/11/19.
//

#include "Order.h"

Order::Order(const string& name_of_buyer) : name_of_buyer(name_of_buyer) {
	total_price = 0;
}

Order::Order(const Order& other) : name_of_buyer(other.name_of_buyer){
	copyNameOfSellers(other);
	this->total_price = other.total_price;
	this->num_of_sellers = other.num_of_sellers;
	this->ordered_items = other.ordered_items;
}

void Order::copyNameOfSellers(const Order& other) {
	name_of_sellers = new string[other.num_of_sellers];
	for (int i = 0; i < other.num_of_sellers; i++) {
		name_of_sellers[i] = other.name_of_sellers[i];
	}
}

Order::Order(Order&& other) : ordered_items(other.ordered_items), name_of_buyer(move(other.name_of_buyer)) {
	name_of_sellers = other.name_of_sellers;
	this->num_of_sellers = other.num_of_sellers;
	this->total_price = other.total_price;
	name_of_sellers = nullptr;
}

Order::~Order() {
	delete name_of_sellers;
}

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
}

void Order::SetNameOfBuyer(const string& name_of_buyer) {
	this->name_of_buyer = name_of_buyer;
}

void Order::updatePrice() {
	Item *temp = ordered_items.getHead();

	while (temp) {
		total_price += temp->GetQuantity() * temp->GetPrice();
		temp = temp->getNext();
	}
}

void Order::updateSellerHistory() {
	Item *temp = ordered_items.getHead();

	while (temp) {
		if(temp->GetQuantity()!= 0) {
			addToNameOfSellers(temp->getSellerName());
		}
		temp = temp->getNext();
	}
}

void Order::setItemList(ItemList list) {
	ordered_items = list;
}

void Order::printCart() {
	ordered_items.printList();
}

string* Order::getNameOfSellers() {
	return name_of_sellers;
}
ItemList Order::getOrderedItems() {
	return ordered_items;
}
int Order::getNumOfSellers() {
	return num_of_sellers;
}

Item* Order::getOrderedItemsHead() {
	return this->ordered_items.getHead();
}

void Order::addToNameOfSellers(const string& seller_name) {
	for (int i = 0; i < this->num_of_sellers; i++) {
		if (seller_name == name_of_sellers[i]) {
			return;
		}
	}
	makeNewNameOfSellers(seller_name);
}
void Order::makeNewNameOfSellers(const string& seller_name) {
	num_of_sellers++;
	string* new_name_of_sellers = new string[num_of_sellers];
	for (int i = 0; i < num_of_sellers - 1; i++) {
		new_name_of_sellers[i] = name_of_sellers[i];
	}
	new_name_of_sellers[num_of_sellers - 1] = seller_name;
	delete[]name_of_sellers;
	name_of_sellers = new_name_of_sellers;
}