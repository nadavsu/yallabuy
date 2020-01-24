//
// Created by Nadav Suliman on 24/11/19.
//

#include "Seller.h"

///Constructors and Destructors-----------------------------------------------------------------------------------------
//File constructor
Seller::Seller(ifstream& os):Account(os) {
	os >> *this;
}

//Constructor
Seller::Seller(const string& username,const string& password, const string& fname, const string& lname, Address& address) : Account(username, password, fname, lname, address),feedbacks(10,'/n'){

}

//Copy constructor
Seller::Seller(const Seller& other) : Account(other), stock_list(other.stock_list) , feedbacks(other.feedbacks){
    for (auto item : other.stock_list) {
        stock_list.push_back(new Item(*item));
    }
}

//Move constructor
Seller::Seller(Seller&& other) : Account(std::move(other)), stock_list(std::move(other.stock_list)), feedbacks(other.feedbacks){
}

//Destructor
Seller::~Seller() {
    auto item_itr = stock_list.begin();
    while (item_itr != stock_list.end()) {      //Deleting the items in stock_list one by one.
        auto temp = item_itr;
        ++temp;
        delete *item_itr;
        item_itr = temp;
    }
}

///Operators------------------------------------------------------------------------------------------------------------
const Seller& Seller::operator=(const Seller& other) {
    if (this != &other) {
		feedbacks        = other.feedbacks;
        address          = other.address;
        stock_list       = other.stock_list;
    }
    else {
        return *this;
    }
}

ifstream& operator>>(ifstream& in, Seller& s) {
	if (typeid(in) == typeid(ifstream)) {
		int size_of_feedbacks;
		in >> size_of_feedbacks; // add if size_of_feedback == 0
		for (int i = 0; i < size_of_feedbacks; i++) {
			s.feedbacks += new Feedback(in);// check this
		}
		return in;
	}
}


//toOs for continuing the printing from the base class Account.
void Seller::toOs(ostream& out) const {
    if (typeid(out) == typeid(ofstream)) {
        out << feedbacks.givelogsize() << endl; // add if size_of_feedback == 0
        for (int i = 0; i < feedbacks.givelogsize(); i++) {
            out << *feedbacks[i];
        }
    }
}
///Getters and Setters--------------------------------------------------------------------------------------------------
Array<Feedback*> Seller::getFeedback() const {
    return feedbacks;
}

list<Item*> Seller::getStock() const {
    return stock_list;
}

list<Item*>::iterator Seller::getItem(const string& item_name) {
    auto item_itr = stock_list.begin();                             //searching for the item
    for (; item_itr != stock_list.end(); ++item_itr) {
        if((*item_itr)->GetName() == item_name) {
            return item_itr;                                        //Returning if the name is the same as item_name.
        }
    }
    return item_itr;
}
void Seller::setItem(Item* seller_item) {
    stock_list.push_back(seller_item);
}

void Seller::setFeedback(const Feedback& buyers_feedback){ // accept item that feedback should have
    Feedback* new_feed = new Feedback(buyers_feedback);
	this->feedbacks += new_feed;
}

///Printing Functions-------------------------------------------------------
void Seller::printStock() const {
    for (auto item : stock_list) {
        cout << *item;
    }
}

///Stock and Item Functions-------------------------------------------------
Item* Seller::getItemToBuyer(const string&  item_name,int quantity) {
    auto item_to_buy = getItem(item_name);                              //getting the item by the name
    if(item_to_buy != stock_list.end()) {                               //checking if it's found
        Item *to_buyer;
        to_buyer = new Item(*(*item_to_buy));                           //creating a copy of the current iterator.
        to_buyer->SetQuantity(quantity);                                //Setting the quantity for the buyer cart
        (*item_to_buy)->reduceQuantity(quantity);                       //reducing the quantity in the seller stock
        if ((*item_to_buy)->GetQuantity() == 0) {                       //Checking if the seller's item has ran out after purchasing
            delete *item_to_buy;
            this->stock_list.erase(item_to_buy);                            //if so we delete.
        }
        return to_buyer;
    } else {
        cout << "Item not found!";
        return nullptr;
    }
}

bool Seller::itemExist(const string&  item_name){
    return (getItem(item_name) != stock_list.end());
}

bool Seller::quantityIsFine(const string& item_name, int quantity) {
    auto item = getItem(item_name);                                     //Searching for the quantity.
    if (item != stock_list.end()) {
        return (quantity > 0 && quantity <= (*item)->GetQuantity());    //checking if it's fine.
    } else {
        cout << "Item not found!";
        return false;
    }
}

bool Seller::isEmptyStock() const {
    return stock_list.empty();
}

Account* Seller::clone() const {
	return new Seller(*this);
}

const string Seller::getType() const {
	return "Seller";
}