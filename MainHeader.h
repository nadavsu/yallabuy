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
void makeFeedback(Manager& admin);
void makeItem(Manager& admin);
void makeFeedback(Manager& admin);
void addToCart(Manager& admin);
void MakeOrderFromCart(Manager& admin);
void getItemInfo(Manager& manager);
void emptyBuffer();
void testOperators(Manager& admin);
void saveSystem(Manager& manager);

#endif //MAINHEADER_H