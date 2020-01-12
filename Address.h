//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_ADDRESS_H
#define ECOMMERCE_ADDRESS_H

#include <iostream>
using namespace std;

static constexpr int CITY_MAX_LEN = 25;
static constexpr int STREET_MAX_LEN = 25;

class Address {
public:
    //friend class Account;

    static constexpr int CITY_NAME_LEN =    20;
    static constexpr int STREET_NAME_LEN =  25;

    bool setCity(const char *city);
    bool setStreet(const char *street);
    bool setHomeNumber(int home_number);

    const char *getCity()       const;
    const char *getStreet()     const;
    int         getHomeNumber() const;

private:
    char*   m_city;
    char*   m_street;
    int     m_home_number;

public:
    Address(const char *city,const char *street, int home_number);
    Address(const Address& other);
    Address(Address&& other);
    ~Address();
    const Address& operator=(const Address& other);
    friend ostream& operator<<(ostream& os, const Address& address);

};


#endif //ECOMMERCE_ADDRESS_H
