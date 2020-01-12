#ifndef MAINHEADER_H
#define MAINHEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Account.h"
#include "Buyer.h"
#include "Address.h"
#include"Seller.h"
#include "Manager.h"
#include "Feedback.h"
#include "CUI.h"
#include <time.h>
using namespace std;

void newAccount(Manager& manager);
//Seller newSeller();
void makeFeedback(Manager& admin);
void makeItem(Manager& admin);
void makeFeedback(Manager& admin);
void addToCart(Manager& admin);
void MakeOrderFromCart(Manager& admin);
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