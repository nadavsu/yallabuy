//
// Created by Nadav Suliman on 24/11/19.
//

#ifndef ECOMMERCE_FEEDBACK_H
#define ECOMMERCE_FEEDBACK_H

#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <fstream>
#include <string>

static constexpr int COMMENT_MAX_LEN = 200;

class Feedback {
public:
    bool setComment(const string& new_comment);

    const string& getUsername()   const;
    const string& getComment()    const;
    Date getDate()                const;

private:
    void setUsername(const string& new_username);

private:
    string username;
	Date  date;
	string comment;

public:
    Feedback(ifstream& os);
    Feedback(const string& feedbacker_username, const string& comment, const Date& date);
	Feedback(const string& feedbacker_username, const string& comment);
	//Feedback(const Feedback& other);
    //Feedback(Feedback&& other);
    //~Feedback();
    const Feedback& operator=(const Feedback& other);
    friend ifstream& operator>>(ifstream& in, Feedback& f);
    friend ostream& operator<<(ostream& os, Feedback& f);
};


#endif //ECOMMERCE_FEEDBACK_H
