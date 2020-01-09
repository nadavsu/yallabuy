//
// Created by Nadav Suliman on 9/1/20.
//

#ifndef ECOMMERCE_CUI_H
#define ECOMMERCE_CUI_H

#include "Manager.h"
#include "Buyer.h"

static constexpr int PAGE_WIDTH = 50;

void printSubTitle(const char *title);
void printTitle(const char *title);
void printLine();
int printMenu();
void printBuyerLogin(const Manager &manager, char *username, char *password);
void printSellerLogin(const Manager &manager, char *username, char *password);
void emptyBuffer();

#endif //ECOMMERCE_CUI_H
