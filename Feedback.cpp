//
// Created by Nadav Suliman on 24/11/19.
//

#include "Feedback.h"
Feedback::Feedback(ifstream& os):date(os) {
    os >> *this;
}
Feedback::Feedback(const string& feedbacker_username, const string& comment) {  //Constructor for feedback with today's date.
    this->username = feedbacker_username;
    this->comment = comment;
}

Feedback::Feedback(const string& feedbacker_username, const string& comment, const Date& date) : date(date) { //Constructor with a specific date
    this->username = feedbacker_username;
    this->comment = comment;
}
/*Feedback::Feedback(const Feedback& other) : date(other.date){

}*/

/*
Feedback::Feedback(Feedback&& other) : date(other.date) {
    comment = other.comment;
    username = other.username;

    other.comment = nullptr;
    other.username = nullptr;
}
*/

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

ifstream& operator>>(ifstream& in, Feedback& f) {
    if (typeid(in) == typeid(ifstream)) {
        in >> f.username;
        in.seekg(1, ios::cur); // skip space
        in >> f.comment;
    }
    return in;
}
ostream& operator<<(ostream& out, Feedback& f) {
    if (typeid(out) == typeid(ofstream)) {
        out << f.date << f.username << " " << f.comment<< endl;
    }
    else {
        out << "Username: " << f.username << endl;
        out << "Date: " << f.date << endl;
        out << "Comment: " << f.comment << endl;
        f.toOs(out);
    }
    return out;
}
void Feedback::toOs(ostream& os) const {

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



