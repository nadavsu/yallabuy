//
// Created by Nadav Suliman on 24/11/19.
//

#include "Order.h"

Order::Order(char* name_of_buyer) {
	SetNameOfBuyer(name_of_buyer);
	total_price = 0;
}

Order::Order(const Order& other) {
	SetNameOfBuyer(other.name_of_buyer);
	copyNameOfSellers(other);
	this->total_price = other.total_price;
	this->num_of_sellers = other.num_of_sellers;
	this->ordered_items = other.ordered_items;
}

void Order::copyNameOfSellers(const Order& other) {
	name_of_sellers = new char* [other.num_of_sellers];
	for (int i = 0; i < other.num_of_sellers; i++) {
		name_of_sellers[i] = other.name_of_sellers[i];
		name_of_sellers[i] = new char[strlen(other.name_of_sellers[i])+1];
		strcpy(name_of_sellers[i], other.name_of_sellers[i]);
	}
}

Order::Order(const Order&& other) : ordered_items(other.ordered_items) {
	name_of_buyer = other.name_of_buyer;
	name_of_sellers = other.name_of_sellers;
	this->num_of_sellers = other.num_of_sellers;
	this->total_price = other.total_price;
	name_of_sellers = nullptr;
	name_of_buyer = nullptr;
}

Order::~Order() {
	for (int i = 0; i < num_of_sellers; i++) {
		delete name_of_sellers[i];
	}
	delete name_of_sellers;
	delete name_of_buyer;
}

const Order& Order::operator=(const Order& other) {
	if (this != &other) {
		for (int i = 0; i < num_of_sellers; i++) {
			delete name_of_sellers[i];
		}
		delete name_of_sellers;
		delete[]name_of_buyer;
		SetNameOfBuyer(other.name_of_buyer);
		copyNameOfSellers(other);
		total_price = other.total_price;
		num_of_sellers = other.num_of_sellers;
		ordered_items = other.ordered_items;
	}
	else {
		return *this;
	}
}

void Order::SetNameOfBuyer(const char* name_of_buyer) {
	this->name_of_buyer = new char[strlen(name_of_buyer) + 1];
	strcpy(this->name_of_buyer, name_of_buyer);
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

char** Order::getNameOfSellers() {
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

void Order::addToNameOfSellers(const char* seller_name) {
	for (int i = 0; i < this->num_of_sellers;i++) {
		if (strcmp(seller_name,name_of_sellers[i]) == 0) {
			return;
		}
	}
	makeNewNameOfSellers(seller_name);
}
void Order::makeNewNameOfSellers(const char* seller_name) {
	num_of_sellers++;
	char** new_name_of_sellers = new char*[num_of_sellers];
	for (int i = 0; i < num_of_sellers-1; i++) {
		new_name_of_sellers[i] = name_of_sellers[i];
	}
	new_name_of_sellers[num_of_sellers - 1] = new char[strlen(seller_name)+1];
	strcpy(new_name_of_sellers[num_of_sellers - 1],seller_name);
	delete[]name_of_sellers;
	name_of_sellers = new_name_of_sellers;
}