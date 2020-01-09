//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_FEEDBACK_H
#define ECOMMERCE_FEEDBACK_H

#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <string.h>

static constexpr int USERNAME_MAX_LEN = 20;
static constexpr int USERNAME_MIN_LEN = 1;
static constexpr int COMMENT_MAX_LEN = 200;

class Feedback {
public:
    bool setDate(const Date& new_date);
    bool setComment(const char* new_comment);

    const char* getUsername()   const;
    const char* getComment()    const;
    Date getDate()              const;

private:
    bool setUsername(const char* new_username);

private:
    char* username;
	Date  date;
	char* comment;

public:
	Feedback(char* feedbacker_username, Date& date, char* comment);
	Feedback(const Feedback& other);
    Feedback(Feedback&& other);
    ~Feedback();
    const Feedback& operator=(const Feedback& other);

};


#endif //ECOMMERCE_FEEDBACK_H
