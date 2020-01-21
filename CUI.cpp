//
// Created by Nadav Suliman on 9/1/20.
//

#include <iostream>
using namespace std;
#include "CUI.h"
#include "Manager.h"

/*
 * This file includes console user interface functions.
 */


void printSubTitle(const string& title) {
    for (int i = 0; i < (PAGE_WIDTH - title.length()) / 2; ++i) {
        cout << "-";
    }
    cout << title;
    for (int i = 0; i < (PAGE_WIDTH - title.length()) / 2; ++i) {
        cout << "-";
    }
    cout << '\n';
}

void printTitle(const string& title) {

    cout << "+";
    for (int i = 0; i < PAGE_WIDTH - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
    cout << "|";
    for (int i = 0; i < (PAGE_WIDTH - 2 - title.length()) / 2; ++i) {
        cout << " ";
    }
    cout << title;
    for (int i = 0; i < (PAGE_WIDTH - 1 - title.length()) / 2; ++i) {
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

int printMainMenu() {
    int ans;
    cout << "To register as a new account, press 1.\n";
    cout << "To add feedback on a seller, press 2.\n";
    cout << "To add a new item to your shop, press 3.\n";
    cout << "To add a new item to your cart, press 4.\n";
    cout << "To make a new order, press 5.\n";
    cout << "To show all the buyers, press 6.\n";
    cout << "To show all the seller, press 7.\n";
    cout << "To get information about a specific item, press 8.\n";
    cout << "To show all the Buyersellers, press 9.\n";
    cout << "To show all the accounts, press 10.\n";
    cout << "To test the operators overloading, press 11.\n";
    cout << "To Save system, press 12.\n";
    cout << "To exit, press 0\n";
    printLine();
    cin >> ans;
    printLine();
    return ans;
}

int printOperatorsMenu() {
    int ans;
    printSubTitle("Operators Menu");
    cout << "To test the > operator, press 1.\n";
    cout << "To test the << operator on a cart and items, press 2.\n";
    cout << "To test the << operator on an account, press 3.\n";
    cout << "To test the += operator, press 4.\n";
    cout << "To quit this menu, press 0.\n";
    printLine();
    cin >> ans;
    printLine();
    return ans;
}

void printLogin(Manager &manager, string& username, string& password) {
    bool logged = true;
    emptyBuffer();
    printSubTitle("Login:");
    do{
        if(!logged) {
            cout << "Wrong username or password!\n";
        }
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);
        logged = manager.login(username, password);
    } while (!logged);
}

void emptyBuffer() {
    int c;
    do{
        c = getchar();
    } while(c != '\n' && c != '\0');
}