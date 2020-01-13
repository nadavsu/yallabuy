
//
// Created by Nadav Suliman on 24/11/19.
//

#include "Item.h"
using namespace std;

Item::Item(const char* name_of_seller,const char* name, Item::eCategory category, int price, int quantity) {
	SetNameOfSeller(name_of_seller);
	SetName(name);
	SetCategory(category);
	SetPrice(price);
	serial_number = num_of_items++;
	//TODO: fix the above giving us a linker error.
	SetQuantity(quantity);
	next = NULL;
}

Item::Item(const Item& other) {
	SetName(other.name);
	SetCategory(other.category);
	SetPrice(other.price);
	SetQuantity(other.quantity);
	SetNameOfSeller(other.name_of_seller);
	this->serial_number = other.serial_number;
	this->next = other.next;
}

Item::Item(Item&& other) {
	name = other.name;
	category = other.category;
	price = other.price;
	quantity = other.quantity;
	next = other.next;
	name_of_seller = other.name_of_seller;
	serial_number = other.serial_number;
	this->name = nullptr;
	this->name_of_seller = nullptr;
}

Item::~Item() {
	delete[] name;
	delete[] name_of_seller;
}

const Item& Item::operator=(const Item& other) {
	if (this != &other){
		delete[]name;
		delete[]name_of_seller;
		this->category = other.category;
		this->price = other.price;
		this->serial_number = other.serial_number;
		this->quantity = other.quantity;
		this->next = other.next;
	}
	else {
		return *this;
	}
}


void Item::SetName(const char* name) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Item::SetNameOfSeller(const char* name_of_seller) {
	this->name_of_seller = new char[strlen(name_of_seller) + 1];
	strcpy(this->name_of_seller, name_of_seller);
}

void Item::SetCategory(Item::eCategory category) {
	this->category = category;
}
void Item::SetPrice(int price) {
	this->price = price;
}

void Item::SetQuantity(int quantity) {
	this->quantity = quantity;
}

void Item::reduceQuantity(int reduction) {
	this->quantity -= reduction;

}

const char* Item::GetName() const {
	return this->name;
}
Item::eCategory Item::GetCategory() const {
	return category;
}
int Item::GetPrice() const {
	return this->price;
}

int Item::GetSerialNumber() const {
	return this->serial_number;
}

int Item::GetQuantity() const {
	return quantity;
}

Item* Item::getNext() const {
	return next;
}

const char* Item::getSellerName() const {
	return name_of_seller;
}

void Item::printItem() const {
	cout << "---------------------------------------------\n";
	cout << "Name of seller: " << name_of_seller << endl;
	cout << "Product name: " << name << endl;
	cout << "Category: " << category << endl;
	cout << "Quantity: " << quantity << endl;
	cout << "Price: " << price << endl;
	cout << "Serial No. " << serial_number << endl;
	cout << "---------------------------------------------\n";
}

int Item::num_of_items = 1000;