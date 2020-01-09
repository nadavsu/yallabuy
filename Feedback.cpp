//
// Created by Nadav Suliman on 24/11/19.
//

#include "Feedback.h"

Feedback::Feedback(char *feedbacker_username, char *comment) {  //Constructor for feedback with today's date.
    setUsername(feedbacker_username);
    setComment(comment);
}

Feedback::Feedback(char *feedbacker_username, char *comment, Date& date) : date(date) { //Constructor with a specific date
    setUsername(feedbacker_username);
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

void Feedback::setUsername(const char* new_username) {
    if (!this->username) {
        delete[] username;
    }
    username = new char[strlen(new_username) + 1];
    strcpy(username, new_username);
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



