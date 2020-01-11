//
// Created by Nadav Suliman on 24/11/19.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Address.h"
using namespace std;
//
//Constructor
Address::Address(char *city, char *street, int home_number) {
    m_city = new char[strlen(city) + 1];
    m_street = new char[strlen(street) + 1];

    strcpy(m_city, city);
    strcpy(m_street, street);
    m_home_number = home_number;
}

//Copy constructor
Address::Address(const Address& other){
    m_city = new char[strlen(other.m_city) + 1];
    m_street = new char[strlen(other.m_street) + 1];

    strcpy(m_city, other.m_city);
    strcpy(m_street, other.m_street);
    m_home_number = other.m_home_number;
}

//Move constructor
Address::Address(Address&& other){
    m_city = other.m_city;
    m_street = other.m_street;
    m_home_number = other.m_home_number;
    other.m_street = nullptr;
    other.m_city = nullptr;
}

//Destructor
Address::~Address(){
    delete[] m_city;
    delete[] m_street;
}

const Address& Address::operator=(const Address& other) {
    if (this != &other) {
        this->m_home_number = other.m_home_number;
        delete[]m_city;
        delete[]m_street;
        this->m_city = other.m_city;
        this->m_street = other.m_street;
    }
    else {
        return *this;
    }
}

ostream& operator<<(ostream& os, const Address& address) {
    os << address.m_street << " " << address.m_home_number << ", " << address.m_city;
    return os;
}

bool Address::setCity(const char *city) {
    if(strlen(city) <= CITY_NAME_LEN) {
        delete[] m_city;
        m_city = new char[strlen(city) + 1];
        strcpy(m_city, city);
        return true;
    }
        return false;
}

bool Address::setStreet(const char *street) {
    if(strlen(street) <= STREET_NAME_LEN){
        delete[] m_street;
        m_street = new char[strlen(street) + 1];
        strcpy(m_street, street);
        return true;
    }
    return false;
}

bool Address::setHomeNumber(int home_number) {
    if(home_number > 0) {
        m_home_number = home_number;
        return true;
    }
    return false;
}

const char *Address::getCity() const{
    return m_city;
}

const char *Address::getStreet() const{
    return m_street;
}

int Address::getHomeNumber() const{
    return m_home_number;
}