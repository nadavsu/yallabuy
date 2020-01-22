//
// Created by Nadav Suliman on 9/1/20.
//

#include <iostream>
#include <string>
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
    printSubTitle("Select your option");
    cout << "1. Register as a new account\n";
    cout << "2. Add feedback on a seller\n";
    cout << "3. Add a new item to your shop\n";
    cout << "4. Add a new item to your cart\n";
    cout << "5. Make a new order\n";
    cout << "6. Show all the buyers\n";
    cout << "7. Show all the seller\n";
    cout << "8. Show all the Buyersellers\n";
    cout << "9. Get information about a specific item\n";
    cout << "10. Show all the accounts\n";
    cout << "11. Test the operators overloading\n";
    cout << "12. Save system, press 12\n";
    cout << "0. Exit\n";
    printLine();
    cin >> ans;
    printLine();
    return ans;
}

int printOperatorsMenu() {
    int ans;
    printSubTitle("Operators Menu");
    cout << "1. Test the > operator\n";
    cout << "2. Test the << operator on a cart and items\n";
    cout << "3. Test the << operator on an account\n";
    cout << "4. Test the += operator\n";
    cout << "0. Quit this menu\n";
    printLine();
    cin >> ans;
    printLine();
    return ans;
}

void printLogin(Manager &manager, string& username, string& password, const string& type) {
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
        logged = manager.login(username, password, type);
    } while (!logged);
}

void emptyBuffer() {
    int c;
    do{
        c = getchar();
    } while(c != '\n' && c != '\0');
}