//
// Created by denys on 10.07.19.
//

#include <iostream>
#include <sstream>
#include "Exam.hpp"

const std::string Exam::MARKER = "E";

Exam::Exam(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _id = std::stoi(buf);
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _course_id = std::stoi(buf);
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _student_id = std::stoi(buf);
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _result = std::stoi(buf);
}

int Exam::getId() const {
    return _id;
}

std::string Exam::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream
    << _id << ','
    << _course_id<< ','
    << _student_id << ','
    << _result;
    return ostringstream.str();
}
