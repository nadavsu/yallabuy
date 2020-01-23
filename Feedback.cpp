//
// Created by Nadav Suliman on 24/11/19.
//

#include "Feedback.h"

// constructor for loading system from file 
Feedback::Feedback(ifstream& os):date(os) {
    os >> *this;
}
// constructor that gets feedback and comment
Feedback::Feedback(const string& feedbacker_username, const string& comment) {  //Constructor for feedback with today's date.
    this->username = feedbacker_username;
    this->comment = comment;
}
//Constructor with a specific date
Feedback::Feedback(const string& feedbacker_username, const string& comment, const Date& date) : date(date) {
    this->username = feedbacker_username;
    this->comment = comment;
}
// operator=
const Feedback& Feedback::operator=(const Feedback& other) {
    if (this != &other) {
        this->date      = other.date;
        this->username  = other.username;
        this->comment   = other.comment;
    }
    else {
        return *this;
    }
}
//operator>>
ifstream& operator>>(ifstream& in, Feedback& f) {
    if (typeid(in) == typeid(ifstream)) {
        getline(in,f.username);
        getline(in,f.comment);
    }
    return in;
}
//operator<<
ostream& operator<<(ostream& out, Feedback& f) {
    if (typeid(out) == typeid(ofstream)) {
        out << f.date << f.username << endl<< f.comment<< endl;
    }
    else {
        out << "Username: " << f.username << endl;
        out << "Date: " << f.date << endl;
        out << "Comment: " << f.comment << endl;
    }
    return out;
}

void Feedback::setUsername(const string& new_username) {
    username = new_username;
}

bool Feedback::setComment(const string& new_comment) {
    if(new_comment.length() <= COMMENT_MAX_LEN) {
        comment = new_comment;
        return true;
    }
    return false;
}

Date Feedback::getDate() const {
    return date;
}

const string& Feedback::getComment() const {
    return comment;
}

const string& Feedback::getUsername() const {
    return username;
}



