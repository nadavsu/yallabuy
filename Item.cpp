
//
// Created by Nadav Suliman on 24/11/19.
//

#include "Item.h"
using namespace std;

///Constructors & Destructors-------------------------------------------------------
Item::Item(const string& name_of_seller ,const string& name, Item::eCategory category, int price, int quantity) {
	this->name_of_seller = name_of_seller;
	this->name = name;
	this->category = category;
	this->price = price;
    this->quantity = quantity;
    serial_number = num_of_items++;
	next = nullptr;
}

/*Item::Item(const Item& other) {
    name = other.name;
    name_of_seller = other.name_of_seller;
	this->category = other.category;
	this->price = other.price;
	this->quantity = other.quantity;
	this->serial_number = other.serial_number;
	this->next = other.next;
}*/
/*
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
}*/

/*Item::~Item() {
	delete[] name;
	delete[] name_of_seller;
}*/

///Operators--------------------------------------------------------------------------
/*const Item& Item::operator=(const Item& other) {
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
}*/

ostream& operator<<(ostream& os, const Item& item) {
    os << "---------------------------------------------\n";
    os << "Name of seller: " << item.name_of_seller << endl;
    os << "Product name: " << item.name << endl;
    os << "Category: " << (Item::eCategory)item.category << endl;
    os << "Quantity: " << item.quantity << endl;
    os << "Price: " << item.price << endl;
    os << "Serial No. " << item.serial_number << endl;
    os << "---------------------------------------------\n";
    return os;
}

///Setters and getters-----------------------------------------------------------------
void Item::SetName(const string& name) {
	this->name = name;
}

void Item::SetNameOfSeller(const string& name_of_seller) {
	this->name_of_seller = name_of_seller;
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

const string& Item::GetName() const {
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

const string& Item::getSellerName() const {
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