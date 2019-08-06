//
// Created by denys on 10.07.19.
//

#include <iostream>
#include <sstream>
#include "Exam.hpp"

const std::string Exam::ID = "ID";
const std::string Exam::COURSE_ID = "CourseID";
const std::string Exam::STUDENT_ID = "StudentID";
const std::string Exam::RESULT = "Result";

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
        {ID, std::to_string(_id)},
        {COURSE_ID, std::to_string(_course_id)},
        {STUDENT_ID, std::to_string(_student_id)},
        {RESULT, std::to_string(_result)}
    };
}

bool Exam::match(const std::vector<Condition> &conditions) const {
    return match_parameters(conditions,
            {{ID, _id}, {COURSE_ID, _course_id}, {STUDENT_ID, _student_id}, {RESULT, _result}});
}

void Exam::update(const std::string &key, const std::string &value) {
    if (COURSE_ID == key)
        _course_id = str_to_int(value);
    if (STUDENT_ID == key)
        _student_id = str_to_int(value);
    if (RESULT == key)
        _result = str_to_int(value);
}
