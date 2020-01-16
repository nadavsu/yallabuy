#ifndef ECOMMERCE_DATE_H
#define ECOMMERCE_DATE_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

static constexpr int CURRENT_YEAR = 2020;
static constexpr int MINIMUM_YEAR = 1900;

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date();                                     //This constructor creates a date with today's date.
	Date(int day, int month, int year);         //This constructor creates a user inputted date.
	Date(const Date& other);
	Date(const Date&& other);
	const Date& operator=(const Date& other);
	~Date() = default;

	int getYear()   const;
	int getMonth()  const;
	int getDay()    const;
private:                                        //Date does not need to be changed.
	bool setYear(int year);
	bool setMonth(int month);
	bool setDay(int day);
};

#endif //ECOMMERCE_DATE_H