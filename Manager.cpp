//
// Created by Nadav Suliman on 19/12/19.
//

#include "Manager.h"

Manager::Manager() {
    this->max_buyer = 1;
    this->max_seller = 1;
    this->curr_buyer = 0;
    this->curr_seller = 0;
    this->arr_seller = new Seller *[max_seller];
    this->arr_buyer = new Buyer *[max_buyer];

}

Manager::~Manager() {
    int mutual_size;
    int i = 0;
    if (this->curr_buyer < this->curr_seller) {
        mutual_size = this->curr_buyer;
    } else {
        mutual_size = this->curr_seller;
    }
    for (i = 0; i < mutual_size; i++) {
        delete this->arr_buyer[i];
        delete this->arr_seller[i];
    }
    while (i < curr_buyer) {
        delete this->arr_buyer[i];
        i++;
    }
    while (i < curr_seller) {
        delete this->arr_seller[i];
        i++;
    }
    delete[] arr_seller;
    delete [] arr_buyer;
}

bool Manager::loginBuyer(const char *username, const char *password) const {
    for (int i = 0; i < curr_buyer; i++) {
        if (strcmp(username, arr_buyer[i]->username) == 0) {
            return strcmp(password, arr_buyer[i]->password) == 0;
        }
    }
    return false;
}

bool Manager::loginSeller(const char *username, const char *password) const {
    for (int i = 0; i < curr_seller; i++) {
        if (strcmp(username, arr_seller[i]->username) == 0) {
            return strcmp(password, arr_seller[i]->password) == 0;
        }
    }
    return false;
}

Buyer *Manager::getBuyer(const char *username) {
    for (int i = 0; i < curr_buyer; i++) {
        if (strcmp(arr_buyer[i]->username, username) == 0) {
            return arr_buyer[i]; //return through copy const without any inside info like password
        }
    }
    return nullptr;             ///Added return if buyer not found.
}

Seller *Manager::GetSeller(const char *username) {
    for (int i = 0; i < curr_seller; i++) {
        if (strcmp(arr_seller[i]->username, username) == 0) {
            return arr_seller[i]; //return through copy const without any inside info like password
        }
    }
    return nullptr;             ///Added return if seller not found.
}

/*void Manager::AddBuyer(Buyer new_buyer) {
    Buyer* buyer_ptr = new Buyer(std::move(new_buyer)); // copy the buyer from the main to take over control
    // check if kill at main
    if (curr_buyer == max_buyer) {
        Buyer** new_arr_buyer = new Buyer*[curr_buyer + 1];
        for(int i = 0; i < curr_buyer; ++i) {
            new_arr_buyer[i] = arr_buyer[i];
        }
        ///my_realloc();
        delete[] arr_buyer;
        arr_buyer = new_arr_buyer;
    }
    arr_buyer[curr_buyer++] = buyer_ptr;
}*/


void Manager::AddBuyer(Buyer &new_buyer) {
    if (this->curr_buyer == this->max_buyer) {
        my_realloc(arr_buyer, max_buyer, curr_buyer);
    }
    *this->arr_buyer[curr_buyer++] = new_buyer;
}

void Manager::my_realloc(void *arr, int max_size, int curr_size) { // make generic func
    this->max_buyer = (this->max_buyer) * 2;
    Buyer **new_arr_buyer = new Buyer *[this->max_buyer];
    for (int i = 0; i < this->curr_buyer; i++) {
        new_arr_buyer[i] = this->arr_buyer[i];
    }
    delete[] arr_buyer;
    arr_buyer = new_arr_buyer;
}


//TODO: Maybe change all the adding functions below to return bool. if seller is not found then error occurs.

void Manager::AddSeller(Seller &new_seller) {
    if (curr_seller == max_seller) {
        my_realloc(arr_seller, max_seller, curr_seller); // make Generic
    }
    *this->arr_seller[curr_seller++] = new_seller;
}


void Manager::AddFeedback(const char *seller_to_feed, const Feedback &new_feedback) {
    Seller *seller = GetSeller(seller_to_feed);
    seller->setFeedback(new_feedback);
}


void Manager::AddItem(const char *seller_username,const Item& new_item) {
    Item* item; // responsible for pointer because add to list
    item = new Item(new_item);
    Seller *seller = GetSeller(seller_username);
    seller->setItem(item);
}


//TODO: Make this function return bool and get the console messages out of here.

void Manager::addItemToCart(const char *buyer_username, Item item) {
    Buyer *buyer = getBuyer(buyer_username);
    buyer->addToCart(item);
}

bool Manager::MakeOrder(const char* buyer_username) {
    Buyer* buyer = getBuyer(buyer_username);
    if (buyer->isEmptyCart()) {
        return false;
    }
        printBuyerCart(buyer);
        return true;
}

//TODO: This function should get const char *username, and get the buyer from here.
void Manager::printBuyerCart(const char *buyer_username) {
    Buyer *buyer = getBuyer(buyer_username);
    buyer->printCart();
}

void Manager::payOrder(const char* buyer_username, Order& to_order) {
    Buyer* buyer = getBuyer(buyer_username);
    Item *curr_cart_item;
    Item* curr_order_item = to_order.getOrderedItems().getHead();

    buyer->addToSellerHistory(to_order.getNameOfSellers(), to_order.getNumOfSellers());
    while (curr_order_item != nullptr) {
        curr_cart_item = buyer->getCart().getHead();
        while (curr_cart_item != nullptr) {
            if (strcmp(curr_order_item->GetName(), curr_cart_item->GetName()) == 0 ) {
                curr_cart_item->reduceQuantity(curr_order_item->GetQuantity());
                curr_cart_item = nullptr;
                if (curr_cart_item->GetQuantity() == 0) {
                    buyer->getCart().deleteItem(curr_cart_item->GetName());
                }
            } else {
                curr_cart_item = curr_cart_item->getNext();
            }
        }
        curr_order_item = curr_order_item->getNext();
    }
}

void Manager::printBuyers() const {
    for (int i = 0; i < curr_buyer; i++) {
        arr_buyer[i]->printBuyer();
    }
}

void Manager::printSellers() const {
    for (int i = 0; i < curr_seller; i++) {
        arr_seller[i]->printSeller();
    }
}

bool Manager::printItemsNamed(const char *item_name) {
    bool res = false;
    for(int i = 0; i < curr_seller; i++) {
        Item *curr_item = arr_seller[i]->stock_list.getHead();
        while(curr_item) {
            if(strcmp(item_name, curr_item->GetName()) == 0) {
                curr_item->printItem();
                res = true;
            }
            curr_item = curr_item->getNext();
        }
    }
    return res;
}

void Manager::printBuyerSellerHistory(const char *buyer_username) {
    Buyer *buyer = getBuyer(buyer_username);
    buyer->printSellerHistory();
    printLine();
}