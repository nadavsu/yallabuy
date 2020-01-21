#include"BuyerSeller.h"

BuyerSeller::BuyerSeller(const string&  username, const string&  password, const string&  fname, const string&  lname, Address& address): Account(username, password, fname, lname, address),
Buyer(username, password, fname, lname, address), Seller(username, password, fname, lname, address) {

}

BuyerSeller::BuyerSeller(const Buyer& otherbuyer, const Seller& otherseller) : 
	Account(otherbuyer.getUsername(), otherbuyer.getPassword(),otherbuyer.getFName(), otherbuyer.getLName(), otherbuyer.getAddress()),
	Seller(otherseller),Buyer(otherbuyer){

}

BuyerSeller::BuyerSeller(const BuyerSeller& other) : Account(other), Buyer(other), Seller(other) {

}

BuyerSeller::BuyerSeller(const BuyerSeller&& other):Account(other),Seller(other),Buyer(other) {
	
}

ostream& operator<<(ostream& out, BuyerSeller& bs) {
	if (typeid(out) == typeid(ofstream)) {
		out << (Seller&)bs << (Buyer&)bs;
	}
	return out;
}

const BuyerSeller& BuyerSeller::operator=(const BuyerSeller& other) {
	if (this != &other) {
		Account::operator=(other);
		Buyer::operator=(other);
		Seller::operator=(other);
	}
	else {
		return *this;
	}
}

Account* BuyerSeller::clone() const {
	return new BuyerSeller(*this);
}

const char *BuyerSeller::getType() const {
	return "BuyerSeller";
}