//
// Created by Nadav Suliman on 22/12/19.
//

#ifndef ECOMMERCE_ITEMLIST_H
#define ECOMMERCE_ITEMLIST_H

#include "Item.h"
using namespace std;

class ItemList {
private:
    Item* head;
    Item* tail;

public:
    void addToTail(Item* new_item);
    bool deleteItem(const string& item_name);
    bool isEmpty()   const;
    void printList() const;
    Item *getHead()  const;
    Item *findItem(const string& item_name);
public:

    ItemList();
    ~ItemList();
    ItemList(const ItemList& other);
    ItemList(ItemList&& other);

    const ItemList& operator=(const ItemList& other);
    friend ostream& operator<<(ostream& os, const ItemList& list);

private:
    bool itemIsInList(const Item& new_item);

};


#endif //ECOMMERCE_ITEMLIST_H
