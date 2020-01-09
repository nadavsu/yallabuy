//
// Created by Nadav Suliman on 24/11/19.
//

#include "Seller.h"

Seller::Seller(char *username, char *password, char *fname, char *lname, Address address) : address(std::move(address)) {
    this->feedbacks = nullptr;
    this->num_of_feedbacks = 0;

    setUsername(username);
    setPassword(password);
    setFName(fname);
    setLName(lname);

    /*    this->username = new char[strlen(username) + 1];
    this->password = new char[strlen(password) + 1];
    this->fname =    new char[strlen(fname) + 1];
    this->lname =    new char[strlen(lname) + 1];

    strcpy(this->username, username);
    strcpy(this->password, password);
    strcpy(this->fname, fname);
    strcpy(this->lname, lname);*/
}

Seller::Seller(const Seller& other) : address(other.address), stock_list(other.stock_list) {
    this->feedbacks = new Feedback*[other.num_of_feedbacks];
    num_of_feedbacks = other.num_of_feedbacks;

    setUsername(other.username);
    setPassword(other.password);
    setFName(other.fname);
    setLName(other.lname);

    copyFeedback(other);
}

Seller::Seller(Seller&& other) : address(std::move(other.address)), stock_list(std::move(other.stock_list)) {
    this->username          = other.username;
    this->password          = other.password;
    this->fname             = other.fname;
    this->lname             = other.lname;
    this->feedbacks          = other.feedbacks;
    this->num_of_feedbacks  = other.num_of_feedbacks;

    other.username      = nullptr;
    other.password      = nullptr;
    other.fname         = nullptr;
    other.lname         = nullptr;
    other.feedbacks     = nullptr;
}

Seller::~Seller() {
    delete[] username;
    delete[] password;
    delete[] fname;
    delete[] lname;
    for (int i = 0; i < num_of_feedbacks; i++) {
        delete feedbacks[i];
    }
    delete[] feedbacks;
}

const Seller& Seller::operator=(const Seller& other) {
    if (this != &other) {
        delete[] username;
        delete[] password;
        delete[] fname;
        delete[] lname;
        delete[] feedbacks;
        copyFeedback(other);
        address          = other.address;
        stock_list       = other.stock_list;
        num_of_feedbacks = other.num_of_feedbacks;
    }
    else {
        return *this;
    }
}

bool Seller::setFName(const char* new_fname) {
	if(strlen(new_fname) <= sFNAME_MAX_LEN && strlen(new_fname) >= sFNAME_MIN_LEN) {
        if (!this->fname) {
            delete[] this->fname;
        }
        this->fname = new char[strlen(new_fname) + 1];
        strcpy(this->fname, new_fname);

        return true;
    }
	return false;
}
bool Seller::setLName(const char* new_lname) {
    if(strlen(new_lname) <= sLNAME_MAX_LEN && strlen(new_lname) >= sLNAME_MIN_LEN) {
        if (!this->lname) {
            delete[] this->lname;
        }
        this->lname = new char[strlen(new_lname) + 1];
        strcpy(this->lname, new_lname);

        return true;
    }
    return false;
}

bool Seller::setUsername(const char* new_username) { // check if already exist.
    if(strlen(new_username) <= sUSERNAME_MAX_LEN && strlen(new_username) >= sUSERNAME_MIN_LEN) {
        if (!this->username) {
            delete[] this->username;
        }
        this->username = new char[strlen(new_username) + 1];
        strcpy(this->username, new_username);

        return true;
    }
    return false;
}

bool Seller::setAddress(const Address& new_address) {
	bool val1 = this->address.setCity(new_address.getCity());
	bool val2 = this->address.setHomeNumber(new_address.getHomeNumber());
	bool val3 = this->address.setStreet(new_address.getStreet());

	return(val1 && val2 && val3);
}

bool Seller::setPassword(const char* new_password) {
    if(strlen(new_password) <= sPASSWORD_MAX_LEN && strlen(new_password) >= sPASSWORD_MIN_LEN) {
        if(!password) {
            delete[] password;
        }
        password = new char[strlen(new_password) + 1];
        strcpy(password, new_password);
        return true;
    }
    return false;
}

///For next exercise
/*
Seller::ePasswordStrength Seller::strengthChecker(const char* Password) const {
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


void Seller::setFeedback(const Feedback& buyers_feedback){ // accept item that feedback should have
	Feedback* new_feed = new Feedback(buyers_feedback);
	Feedback** new_feedback = new Feedback*[(num_of_feedbacks)+1];
	for (int i = 0; i < num_of_feedbacks; i++) {
		new_feedback[i] = this->feedbacks[i];
	}
	new_feedback[num_of_feedbacks++] = new_feed;
	delete[] this->feedbacks;
	this->feedbacks = new_feedback;
}



void Seller::setItem(Item* seller_item) {
    stock_list.addToTail(seller_item);
}

const char* Seller::getFName() const {
	return fname;
}

const char* Seller::getLName() const {
	return lname;
}

const char* Seller::getUsername() const {
	return username;
}

const char* Seller::getPassword() const {
    return password;
}

Address Seller::getAddress() const {
	return address;
}
Feedback **Seller::getFeedback() const {
    return feedbacks;
}
ItemList Seller::getStock() const {// same as feedback
    return stock_list;
}

void Seller::copyFeedback(const Seller& other) {
    ///Source to problems maybe.
    for(int i = 0; i < other.num_of_feedbacks; ++i) {
        feedbacks[i] = new Feedback(other.feedbacks[i][0]);
    }
}


void Seller::printStock() const {
    stock_list.printList();
}

void Seller::printSeller() const {
    //TODO: if you have a CUI class then use printLine();
    cout << "----------------------------------\n";
    cout << "Username: " << username << endl;
    cout << "Name: " << fname << " " << lname << endl;
    this->address.printAddress();
    cout << "----------------------------------\n";

}

Item *Seller::getItem(const char *item_name) {
    return stock_list.findItem(item_name);
}

Item* Seller::getItemToBuyer(const char* item_name,int quantity) { // check exist for sure
    Item* item_to_buy = getItem(item_name);
    Item* to_buyer;
    to_buyer = new Item(*item_to_buy);
    to_buyer->SetQuantity(quantity);
    item_to_buy->reduceQuantity(quantity);
    if (item_to_buy->GetQuantity() == 0 ) {
        this->stock_list.deleteItem(item_name);
    }
    return to_buyer;
}
bool Seller::itemExist(char* item_name){
    Item* item;
    item = getItem(item_name);
    if (item != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool Seller::quantityIsFine(char* item_name,int quantity) {
    Item* item;
    item = getItem(item_name);
    return (quantity > 0 && quantity <= item->GetQuantity());
}