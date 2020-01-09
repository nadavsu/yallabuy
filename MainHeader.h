#ifndef MAINHEADER_H
#define MAINHEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Buyer.h"
#include "Address.h"
#include"Seller.h"
#include "Manager.h"
#include "Feedback.h"
#include <time.h>
using namespace std;

Buyer newBuyer();
Seller newSeller();
Feedback newFeedback(char* buyer_username);
void makeItem(Manager& admin);
void makeFeedback(Manager& admin);
void addToCart(Manager& manager);
void MakeOrderFromCart(Manager& manager);
void getItemInfo(Manager& manager);
void printBuyerLogin(const Manager& manager, char* username, char* password);
void printSellerLogin(const Manager& manager, char* username, char* password);
void printSubTitle(const char* title);
void printTitle(const char* title);
void printLine();
int printMenu();

void emptyBuffer();
//int Item::num_of_items = 1000;

#endif //MAINHEADER_H