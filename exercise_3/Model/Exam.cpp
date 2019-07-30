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

std::vector<Parameter> Exam::_get_print_parameters() const {
    return {
        {"ID", std::to_string(_id)},
        {"CourseID", std::to_string(_course_id)},
        {"StudentID", std::to_string(_student_id)},
        {"Result", std::to_string(_result)}
    };
}
