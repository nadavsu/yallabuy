//
// Created by Nadav Suliman on 22/12/19.
//

#ifndef ECOMMERCE_ITEMLIST_H
#define ECOMMERCE_ITEMLIST_H

#include "Item.h"

class ItemList {
private:
    Item* head;
    Item* tail;

public:
    void addToTail(const Item* new_item);
    bool deleteItem(const char *item_name);
    bool isEmpty()   const;
    void printList() const;
    Item *getHead();
    Item *findItem(const char *item_name);
public:

    ItemList();
    ~ItemList();
    ItemList(const ItemList& other);
    ItemList(ItemList&& other);
    const ItemList& operator=(const ItemList& other);

private:
    bool itemIsInList(const Item& new_item);

};


#endif //ECOMMERCE_ITEMLIST_H
