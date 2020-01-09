//
// Created by Nadav Suliman on 9/1/20.
//

#include <iostream>
using namespace std;
#include "CUI.h"


void printSubTitle(const char *title) {
    for (int i = 0; i < (PAGE_WIDTH - strlen(title)) / 2; ++i) {
        cout << "-";
    }
    cout << title;
    for (int i = 0; i < (PAGE_WIDTH - strlen(title)) / 2; ++i) {
        cout << "-";
    }
    cout << '\n';
}

void printTitle(const char *title) {

    cout << "+";
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
    cout << "|";
    for (int i = 0; i < (PAGE_WIDTH - 2 - strlen(title)) / 2; ++i) {
        cout << " ";
    }
    cout << title;
    for (int i = 0; i < (PAGE_WIDTH - 1 - strlen(title)) / 2; ++i) {
        cout << " ";
    }
    cout << "|\n";
    cout << "+";
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
}

void printLine() {
    cout << "+";
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
}

int printMenu() {
    int ans;
    cout << "To register as a new buyer, press 1.\n";
    cout << "To register as a new seller, press 2.\n";
    cout << "To add feedback on a seller, press 3.\n";
    cout << "To add a new item to your shop, press 4.\n";
    cout << "To add a new item to your cart, press 5.\n";
    cout << "To make a new order, press 6.\n";
    cout << "To show all the buyers, press 7.\n";
    cout << "To show all the seller, press 8.\n";
    cout << "To get information about a specific item, press 9.\n";
    cout << "To exit, press 0\n";
    printLine();
    cin >> ans;
    printLine();
    return ans;
}

void printBuyerLogin(const Manager &manager, char *username, char *password) {
    bool logged = true;
    emptyBuffer();
    printSubTitle("Buyer Login");
    do{
        if(!logged) {
            cout << "Wrong username or password!\n";
        }
        cout << "Username: ";
        cin.getline(username, USERNAME_MAX_LEN);
        cout << "Password: ";
        cin.getline(password, PASSWORD_MAX_LEN);
        logged = manager.loginBuyer(username, password);
    } while (!logged);
}

void printSellerLogin(const Manager &manager, char *username, char *password) {
    bool logged = true;
    emptyBuffer();
    printSubTitle("Seller Login");
    do{
        if(!logged) {
            cout << "Wrong username or password!\n";
        }
        cout << "Username: ";
        cin.getline(username, USERNAME_MAX_LEN);
        cout << "Password: ";
        cin.getline(password, PASSWORD_MAX_LEN);
        logged = manager.loginSeller(username, password);
    } while (!logged);
}

void emptyBuffer() {
    int c;
    do{
        c = getchar();
    } while(c != '\n' && c != '\0');
}