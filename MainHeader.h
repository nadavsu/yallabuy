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

static constexpr int PASSWORD_MAX_LEN = 20;
static constexpr int PASSWORD_MIN_LEN = 6;

static constexpr int FNAME_MAX_LEN = 20;
static constexpr int FNAME_MIN_LEN = 2;
static constexpr int LNAME_MAX_LEN = 25;
static constexpr int LNAME_MIN_LEN = 2;

static constexpr int PAGE_WIDTH = 50;



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