//
// Created by Nadav Suliman on 24/11/19.
//

#include "Seller.h"

///Constructors and Destructors------------------------------------------
Seller::Seller(ifstream& os):Account(os) {
	os >> *this;
}
Seller::Seller(const string& username,const string& password, const string& fname, const string& lname, Address& address) : Account(username, password, fname, lname, address),feedbacks(10,'/n'){

}

Seller::Seller(const Seller& other) : Account(other), stock_list(other.stock_list) , feedbacks(other.feedbacks){
   // this->feedbacks = new Feedback*[other.num_of_feedbacks];
    //copyFeedback(other);
    for (auto item : other.stock_list) {
        stock_list.push_back(new Item(*item));
    }
}

Seller::Seller(Seller&& other) : Account(std::move(other)), stock_list(std::move(other.stock_list))/*, feedbacks(other.feedbacks)*/{
    this->feedbacks         = other.feedbacks;
 //   this->num_of_feedbacks  = other.num_of_feedbacks;
 //   other.feedbacks         = nullptr;
}

Seller::~Seller() {
    auto item_itr = stock_list.begin();
    while (item_itr != stock_list.end()) {
        auto temp = item_itr;
        ++temp;
        delete *item_itr;
        item_itr = temp;
    }
}

const Seller& Seller::operator=(const Seller& other) {
    if (this != &other) {
        //delete[] feedbacks;
        //copyFeedback(other);
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
		//in >> (Account&)s;
		int size_of_feedbacks;
		in >> size_of_feedbacks; // add if size_of_feedback == 0
		//s.feedbacks = new Feedback*[s.num_of_feedbacks];
		for (int i = 0; i < size_of_feedbacks; i++) {
			s.feedbacks += new Feedback(in);// check this
		}
		return in;
	}
}
ostream& operator<<(ostream& out,Seller& s) {
	if (typeid(out) == typeid(ofstream)) {
		out << (Account&)s;
		out << s.feedbacks.givelogsize() << endl; // add if size_of_feedback == 0
		for (int i = 0; i < s.feedbacks.givelogsize(); i++) {
			out << s.feedbacks[i];
		}
	}
	return out;
}
///Getters and Setters------------------------------------------------------
Array<Feedback*> Seller::getFeedback() const {
    return feedbacks;
}

list<Item*> Seller::getStock() const {
    return stock_list;
}

list<Item*>::iterator Seller::getItem(const string& item_name) {
    auto item_itr = stock_list.begin();
    for (; item_itr != stock_list.end(); ++item_itr) {
        if((*item_itr)->GetName() == item_name) {
            return item_itr;
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
	/*
    Feedback** new_feedback = new Feedback*[(num_of_feedbacks)+1];
    for (int i = 0; i < num_of_feedbacks; i++) {
        new_feedback[i] = this->feedbacks[i];
    }
    new_feedback[num_of_feedbacks++] = new_feed;
    delete[] this->feedbacks;
    this->feedbacks = new_feedback;
	*/
}

///Feedback Functions-------------------------------------------------------
/*void Seller::copyFeedback(Seller& other) {
    for(int i = 0; i < other.num_of_feedbacks; ++i) {
		Feedback* new_feed = new Feedback(*other.feedbacks[i]);
		feedbacks += new_feed;
    }
}
*/

///Printing Functions-------------------------------------------------------
void Seller::printStock() const {
    for (auto item : stock_list) {
        cout << *item;
    }
}

///Stock and Item Functions-------------------------------------------------
Item* Seller::getItemToBuyer(const string&  item_name,int quantity) { // check exist for sure
    auto item_to_buy = getItem(item_name);
    if(item_to_buy != stock_list.end()) {
        Item *to_buyer;
        to_buyer = new Item(*(*item_to_buy));              ///todo: check this
        to_buyer->SetQuantity(quantity);
        (*item_to_buy)->reduceQuantity(quantity);
        if ((*item_to_buy)->GetQuantity() == 0) {
            delete *item_to_buy;
            this->stock_list.erase(item_to_buy);
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
    auto item = getItem(item_name);
    if (item != stock_list.end()) {
        return (quantity > 0 && quantity <= (*item)->GetQuantity());
    } else {
        cout << "Item not found!";
        return false;
    }
}

bool Seller::isEmptyStock() const {
    return stock_list.empty();
}

/*
Seller::ePasswordStrength Seller::strengthChecker(const string&  Password) const {
	int a, len, hasUpper, hasLower, hasSymb, hasSpecial, hasNum, i, flag;
	unsigned char x;
	len = strlen(Password);
	if (len < 6) {
		return too_short;
		//printf("password length too short , password should be of minimum of 6 characters ");
	}
	else if (len > 12) {
		return too_long;
			//printf("password length too long, password should be of maximum of 12 characters");
	}
	else {
		a = strcmp(this->username, Password);
		if (a == 0) {
			return match_username;
			//printf(" weak password, matches with username");
		}
		else {
			hasUpper = hasLower = hasSymb = hasSpecial = hasNum = 0;
			flag = 0;
			while (Password[i] != '\0') {
				x = Password[i];
				if (x >= 'a' && x <= 'z') {
					hasLower = 1;
				}
				else if (x >= 'A' && x <= 'Z') {
					hasUpper = 1;
				}
				else if ((x >= 33 && x <= 47) || (x >= 58 && x <= 64) || (x >= 91 && x <= 96)) {// symbols ascii range
					hasSymb = 1;
				}
				else if (x >= 123 && x <= 126) {//special symbols ascii range
					hasSpecial = 1;
				}
				else if (x >= 48 && x <= 57) {//numbers range
					hasNum = 1;
				}
				i++;
			}//while
			if (hasUpper) flag += 10;
			if (hasLower) flag += 10;
			if (hasNum) flag += 10;
			if (hasSymb) flag += 10;
			if (hasSpecial) flag += 10;
			//printf("flag= %d \n", flag);
			if (flag == 50) {
				return Five_out_of_Five;
				//printf("Five out of Five Star Strength!\n");
			}
			else if (flag == 40) {
				return Four_out_of_Five;
				//printf("Four our of Five Star Strength");
			}
			else if (flag == 30) {
				return Three_out_of_Five;
				//printf("Three out of Five Star Strength");
			}
			else if (flag == 20) {
				return Two_out_of_Five;
				//printf("Two out of Five Star Strength");
			}
			else {
				return One_out_of_Five;
				//printf("One out of Five Star Strength");
			}
		}//else
	}//else
}*/

Account* Seller::clone() const {
	return new Seller(*this);
}

const char *Seller::getType() const {
	return "Seller";
}