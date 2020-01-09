#ifndef ECOMMERCE_DATE_H
#define ECOMMERCE_DATE_H

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
	Date(int year,int month,int day);
	Date(const Date& other);
	Date(const Date&& other);
	const Date& operator=(const Date& other);
	~Date() = default;

	bool SetYear(int year);
	bool SetMonth(int month);
	bool SetDay(int day);

	int GetYear()   const;
	int GetMonth()  const;
	int GetDay()    const;

};

#endif //ECOMMERCE_DATE_H