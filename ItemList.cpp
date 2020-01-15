//
// Created by Nadav Suliman on 22/12/19.
//

#include "ItemList.h"
using namespace std;

ItemList::ItemList() {
    head = tail = nullptr;
}

ItemList::ItemList(const ItemList& other) {
    head = tail = nullptr;
    Item* other_item = other.head;
    while(other_item) {
        Item* curr_item = new Item(*other_item);
        curr_item->next = nullptr;
        addToTail(curr_item);
        other_item = other_item->next;
    }
}

ItemList::ItemList(ItemList&& other) {
    head = other.head;
    tail = other.tail;

    other.head = nullptr;
    other.tail = nullptr;
}

ItemList::~ItemList() {
    Item *temp = head;
    Item *next_temp;
    while(temp) {
        next_temp = temp->next;
        delete temp;
        temp = next_temp;
    }
}

const ItemList& ItemList::operator=(const ItemList& other) {
    if (this != &other) {
        if (this->head != nullptr) {
            this->~ItemList();
        }
        Item* curr_other = other.head;
        while (curr_other != nullptr) {
            Item* temp = new Item(*curr_other);         // check goes to copy
            temp->next = nullptr;
            addToTail(temp);
            curr_other = curr_other->next;
        }
    }
    else {
        return *this;
    }
}

ostream& operator<<(ostream& os, const ItemList& list) {
    Item *curr = list.head;
    while(curr) {
        os << *curr << '\n';
        curr = curr->getNext();
    }
    return os;
}

bool ItemList::isEmpty() const {
    return head == nullptr;
}

void ItemList::addToTail(Item* new_item) {
    if(!itemIsInList(*new_item)) { // add quantity to exist item
        if (isEmpty()) {
            head = tail = new_item;
        } else {
            tail->next = new_item;
            tail = new_item;
        }
    }
}

bool ItemList::deleteItem(const char *item_name) {
    Item *prev = nullptr;
    Item *curr = head;

    if(isEmpty()) {
        return false;
    } else {
        while(curr) {
            if(strcmp(item_name, curr->name) == 0) {
                if(!prev) {
                    head = curr->next;
                    delete curr;
                } else if(!curr->next) {
                    prev->next = curr->next;
                    tail = prev;
                    delete curr;
                } else {
                    prev->next = curr->next;
                    delete curr;
                }
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return false;
}

bool ItemList::itemIsInList(const Item& new_item) { // remeber he add to quantity already
    Item* temp = head;
    while (temp) {
        if (strcmp(temp->name, new_item.name) == 0) {
            temp->quantity += new_item.quantity;
            return true;
        }
        temp = temp->getNext();
    }
    return false;
}

Item *ItemList::findItem(const char *item_name) {
    Item *temp = head;
    while (temp) {
        if(strcmp(temp->name, item_name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void ItemList::printList() const {
    Item *curr = head;
    while(curr) {
        curr->printItem();
        curr = curr->next;
    }
}

Item *ItemList::getHead() const {
    return head;
}