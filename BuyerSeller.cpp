#include"BuyerSeller.h"


///Constructors & Destructors----------------------------------------------------------------------------------------
//File constructor
BuyerSeller::BuyerSeller(ifstream& os):Account(os),Seller(os),Buyer(os) {

}

//Constructor
BuyerSeller::BuyerSeller(const string&  username, const string&  password, const string&  fname, const string&  lname, Address& address): Account(username, password, fname, lname, address),
Buyer(username, password, fname, lname, address), Seller(username, password, fname, lname, address) {

}

//Copy constructor 1
BuyerSeller::BuyerSeller(const Buyer& otherbuyer, const Seller& otherseller) :
	Account(otherbuyer.getUsername(), otherbuyer.getPassword(),otherbuyer.getFName(), otherbuyer.getLName(), otherbuyer.getAddress()),
	Seller(otherseller),Buyer(otherbuyer){

}

//Copy constructor 2
BuyerSeller::BuyerSeller(const BuyerSeller& other) : Account(other), Buyer(other), Seller(other) {

}

//Move constructor.
BuyerSeller::BuyerSeller(BuyerSeller&& other):Account(other),Seller(other),Buyer(other) {
	
}
/*
ostream& operator<<(ostream& out, BuyerSeller& bs) {
	if (typeid(out) == typeid(ofstream)) {
		out << (Seller&)bs << (Buyer&)bs;
	}
	return out;
}
*/
const BuyerSeller& BuyerSeller::operator=(const BuyerSeller& other) {
	if (this != &other) {
		Account::operator=(other);
		Seller::operator=(other);
	}
	else {
		return *this;
	}
}

//Used for printing to file or to console.
void BuyerSeller::toOs(ostream& out) const {
	Seller::toOs(out);
    Buyer::toOs(out);
}

Account* BuyerSeller::clone() const {
    return new BuyerSeller(*this);
}

const string BuyerSeller::getType() const {
	return "BuyerSeller";
}