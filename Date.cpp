#include "Date.h"
#include "MainHeader.h"

Date::Date() {
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);
	SetYear(TM.tm_year);
	SetMonth(TM.tm_mon);
	SetDay(TM.tm_mday);
}

Date::Date(const Date& other) {
	SetMonth(other.month);
	SetYear(other.year);
	SetDay(other.day);
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

Date::Date(const Date&& other) {
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
}

bool Date::SetYear(int year) {
    if(year <= CURRENT_YEAR && year >= MINIMUM_YEAR) {
        this->year = year;
        return true;
    }
    return false;
}
bool Date::SetMonth(int month) {
    if(month <= 12 && month >= 1) {
        this->month = month;
        return true;
    }
    return false;
}

bool Date::SetDay(int day) {
    if(day <= 31 && day >= 1) {
        this->day = day;
        return true;
    }
    return false;
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}