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

Seller *Manager::getSeller(const char *username) {
    for (int i = 0; i < curr_seller; i++) {
        if (strcmp(arr_seller[i]->username, username) == 0) {
            return arr_seller[i]; //return through copy const without any inside info like password
        }
    }
    return nullptr;             ///Added return if seller not found.
}

bool Manager::buyerIsCartEmpty(const char *buyer_username) {
    Buyer *buyer = getBuyer(buyer_username);
    return buyer->isEmptyCart();
}

bool Manager::sellerIsCartEmpty(const char* seller_username) {
    Seller* selller = getSeller(seller_username);
    return selller->isEmptyCart();
}

bool Manager::isItemExistInSeller(const char* seller_username,const char* item_name_to_buy) {
    Seller* seller = getSeller(seller_username);
    return seller->itemExist(item_name_to_buy);
}

bool Manager::sellerIsQuantityFine(const char* seller_username,const char* item_name_to_buy,int quantity) {
    Seller* seller = getSeller(seller_username);
    return seller->quantityIsFine(item_name_to_buy, quantity);
}

void Manager::printSellerShop(const char* seller_username) {
    Seller* seller = getSeller(seller_username);
    seller->printStock();
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
    this->arr_buyer[curr_buyer++] = new Buyer(new_buyer);
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
    this->arr_seller[curr_seller++] = new Seller(new_seller);
}


void Manager::addFeedback(const Feedback& feedback, const char *seller_username) {
    Seller *seller = getSeller(seller_username);
    seller->setFeedback(feedback);
}


void Manager::AddItem(const char *seller_username,const Item& new_item) {
    Item* item; // responsible for pointer because add to list
    item = new Item(new_item);
    Seller *seller = getSeller(seller_username);
    seller->setItem(item);
}


//TODO: Make this function return bool and get the console messages out of here.

void Manager::addItemToCart(const char *buyer_username, const char* seller_username, const char* item_name_to_buy, int quantity) {
    Item* seller_item = getItemFromSellerToBuyer(seller_username, item_name_to_buy, quantity);
    Item* new_item;
    new_item = new Item(*seller_item);
    new_item->next = nullptr;
    Buyer *buyer = getBuyer(buyer_username);
    buyer->addToCart(new_item);
    delete seller_item;
}

Item* Manager::getItemFromSellerToBuyer(const char* seller_username, const char* item_name_to_buy, int quantity) {
    Seller* seller = getSeller(seller_username);
    Item* seller_item = seller->getItemToBuyer(item_name_to_buy, quantity);
    return seller_item;
}

void Manager::printBuyerCart(const char *buyer_username) {
    Buyer *buyer = getBuyer(buyer_username);
    buyer->printCart();
}

void Manager::payOrder(const char* buyer_username, Order& order) {
    Buyer* buyer = getBuyer(buyer_username);
    Item *curr_cart_item;
    Item* curr_order_item = order.getOrderedItemsHead();

    buyer->addToSellerHistory(order.getNameOfSellers(), order.getNumOfSellers());
    while (curr_order_item != nullptr) {
        curr_cart_item = buyer->getCartHead();
        while (curr_cart_item != nullptr) {
            if (curr_order_item->GetQuantity() && strcmp(curr_order_item->GetName(), curr_cart_item->GetName()) == 0) {
                curr_cart_item->reduceQuantity(curr_order_item->GetQuantity());
                if (curr_cart_item->GetQuantity() == 0) {
                    buyer->deleteItemFromCart(curr_cart_item->GetName());
                }
                curr_cart_item = nullptr;
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

bool Manager::isSellerExist(char* seller_name) {
    Seller* seller = getSeller(seller_name);
    if (seller != nullptr) {
        return true;
    }
    else {
        return false;
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

bool Manager::sellerExistInBuyerSeller(const char *buyer_username, const char *seller_username) {
    Buyer *buyer = getBuyer(buyer_username);

    for (int i = 0; i < buyer->seller_history_size; ++i) {                    //Looking in the buyer history.
        if (strcmp(buyer->seller_history[i], seller_username) == 0) {
            return true;
        }
    }
    return false;
}

void Manager::copyCartToOrder(Order& order, const char *buyer_username) {
    Buyer *buyer = getBuyer(buyer_username);
    order.setItemList(buyer->getCart());//make copy twice!!!!
}

void Manager::_debugfill() {
    Buyer buyer1("dorlasri", "123456", "Dor", "Lasri", Address("Nahariya", "Bialik", 2));
    Buyer buyer2("arnaudmaarek", "ilovefrance", "Arnaud", "Maarek", Address("Tel Aviv", "Bograshov", 9));
    AddBuyer(buyer1);
    AddBuyer(buyer2);

    Seller seller1("nadavsuliman", "fuckyou", "Nadav", "Suliman", Address("Raanana", "Aharonson", 12));
    AddSeller(seller1);
    Item item1s1("nadavsuliman", "PS5", (Item::eCategory) 3, 4000, 20);
    Item item2s1("nadavsuliman", "Wii", (Item::eCategory) 3, 980, 5);
    Item item3s1("nadavsuliman", "Pizza", (Item::eCategory) 0, 60, 90);
    AddItem(seller1.getUsername(), item1s1);
    AddItem(seller1.getUsername(), item2s1);
    AddItem(seller1.getUsername(), item3s1);

    Seller seller2("shaitek5", "maccabizona", "Shai", "Rubinstein", Address("Jerusalem", "Yitzhak Sade", 4));
    AddSeller(seller2);
    Item item1s2("shaitek5", "ASUS PC", (Item::eCategory) 0, 3000, 50);
    Item item2s2("shaitek5", "Macbook Pro", (Item::eCategory) 0, 10000, 5);
    Item item3s2("shaitek5", "Sambusak", (Item::eCategory) 0, 10, 20);
    AddItem(seller2.getUsername(), item1s2);
    AddItem(seller2.getUsername(), item2s2);
    AddItem(seller2.getUsername(), item3s2);
}