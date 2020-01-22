#include "Date.h"


//Default constructor creates today's date.
Date::Date(ifstream& os) {
    os >> *this;
}
Date::Date() {
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);
    setYear(TM.tm_year);
    setMonth(TM.tm_mon + 1);
    setDay(TM.tm_mday);
}

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {

}

Date::Date(const Date& other) {
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
}

const Date& Date::operator=(const Date& other) {
    if (this != &other) {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
    }
    else {
        return *this;
    }
}
ifstream& operator>>(ifstream& in, Date& d) {
    if (typeid(in) == typeid(ifstream)) {
        in >> d.year;
        in.seekg(1, ios::cur); // skip space
        in >> d.month;
        in.seekg(1, ios::cur); // skip space
        in >> d.day;
        in.seekg(1, ios::cur); // skip space
        return in;
    }
}
Date::Date(const Date&& other) {
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
}

bool Date::setYear(int year) {
    if(year <= CURRENT_YEAR && year >= MINIMUM_YEAR) {
        this->year = year;
        return true;
    }
    return false;
}
bool Date::setMonth(int month) {
    if(month <= 12 && month >= 1) {
        this->month = month;
        return true;
    }
    return false;
}

bool Date::setDay(int day) {
    if(day <= 31 && day >= 1) {
        this->day = day;
        return true;
    }
    return false;
}

int Date::getYear() const {
	return year;
}

int Date::getMonth() const {
	return month;
}

int Date::getDay() const {
	return day;
}