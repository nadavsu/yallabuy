//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_ADDRESS_H
#define ECOMMERCE_ADDRESS_H

#include <iostream>
#include <fstream>
#include<string>
using namespace std;

static constexpr int CITY_MAX_LEN = 25;
static constexpr int STREET_MAX_LEN = 25;

class Address {
public:
    static constexpr int CITY_NAME_LEN =    20;
    static constexpr int STREET_NAME_LEN =  25;

    bool setCity(const string& city);
    bool setStreet(const string& street);
    bool setHomeNumber(int home_number);

    const string& getCity()       const;
    const string& getStreet()     const;
    int           getHomeNumber() const;

private:
    string   city;
    string   street;
    int      home_number;

public:
    Address(ifstream& in);
    Address(const string& city, const string& street, int home_number);
    friend ostream& operator<<(ostream& os, const Address& address);
    friend ifstream& operator>>(ifstream& in, Address& address);
};


#endif //ECOMMERCE_ADDRESS_H
