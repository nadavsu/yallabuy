//
// Created by Nadav Suliman on 24/11/19.
//

#include "Feedback.h"

Feedback::Feedback(char *feedbacker_username, Date& date, char *comment) : date(date) {
    setUsername(username);
    setComment(comment);
}

Feedback::Feedback(const Feedback& other) : date(other.date){
    setUsername(other.username);
    setComment(other.comment);
}

Feedback::Feedback(Feedback&& other) : date(other.date) {
    comment = other.comment;
    username = other.username;

    other.comment = nullptr;
    other.username = nullptr;
}

const Feedback& Feedback::operator=(const Feedback& other) {
    if (this != &other) {
        delete[]username;
        delete[]comment;
        this->date = other.date;
        setUsername(other.username);
        setComment(other.comment);
    }
    else {
        return *this;
    }
}

Feedback::~Feedback() {
    delete[] username;
    delete[] comment;
}

bool Feedback::setUsername(const char* new_username) {
    if (strlen(new_username) <= USERNAME_MAX_LEN && strlen(new_username) >= USERNAME_MIN_LEN) {
        if (!this->username) {
            delete[] username;
        }
        username = new char[strlen(new_username) + 1];
        strcpy(username, new_username);

        return true;
    }
    return false;
}

bool Feedback::setDate(const Date& new_date) {
    bool test1 = date.SetDay(new_date.GetDay());
    bool test2 = date.SetMonth(new_date.GetMonth());
    bool test3 = date.SetYear(new_date.GetYear());

    return (test1 && test2 && test3);
}

bool Feedback::setComment(const char* new_comment) {
    if(strlen(new_comment) <= COMMENT_MAX_LEN){
        if(!this->comment) {
            delete[] comment;
        }
        comment = new char[strlen(new_comment) + 1];
        strcpy(comment, new_comment);

        return true;
    }
    return false;
}

Date Feedback::getDate() const {
    return date;
}

const char *Feedback::getComment() const {
    return comment;
}

const char *Feedback::getUsername() const {
    return username;
}



