#include"BuyerSeller.h"

BuyerSeller::BuyerSeller(char* username, char* password, char* fname, char* lname, Address& address):Account(username, password, fname, lname, address)
,Buyer(username, password, fname, lname, address) ,Seller(username, password, fname, lname, address) {

}

BuyerSeller::BuyerSeller(const Buyer& otherbuyer, const Seller& otherseller) : 
	Account(otherbuyer.getUsername(), otherbuyer.getPassword(),otherbuyer.getFName(), otherbuyer.getLName(), otherbuyer.getAddress()),
	Seller(otherseller),Buyer(otherbuyer){

}

BuyerSeller::BuyerSeller(const Account& other) :Account(other), Buyer(other), Seller(other) {

}

BuyerSeller::BuyerSeller(const BuyerSeller& other):Account(other),Buyer(other),Seller(other) {

}

BuyerSeller::BuyerSeller(const BuyerSeller&& other):Account(other),Seller(other),Buyer(other) {
	
}

const BuyerSeller& BuyerSeller::operator=(const BuyerSeller& other) {
	Account::operator=(other);
	Buyer::operator=(other);
	Seller::operator=(other);
}

Account* BuyerSeller::clone() const {
	return new BuyerSeller(*this);
}

const char* BuyerSeller::getType() const {
	return "BuyerSeller";
}