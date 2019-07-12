//
// Created by denys on 10.07.19.
//

#include <iostream>
#include <sstream>
#include "Exam.hpp"

Exam::Exam(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_id = std::stoi(buf);
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_course_id = std::stoi(buf);
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_student_id = std::stoi(buf);
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    this->_result = std::stoi(buf);
}

int Exam::getId() const {
    return this->_id;
}

std::string Exam::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream
    << this->_id << ','
    << this->_course_id<< ','
    << this->_student_id << ','
    << this->_result;
    return ostringstream.str();
}
