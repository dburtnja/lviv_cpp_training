//
// Created by denys on 10.07.19.
//

#include <iostream>
#include <sstream>
#include "Course.hpp"

const std::string Course::MARKER = "C";
const std::string Course::RECORD_NAME = "Course";

int Course::getId() const {
    return _id;
}

std::string Course::getFormatted() const {
    std::ostringstream  ostringstream;

    ostringstream << _id << "," << _name << "," << _teacher_id;
    return ostringstream.str();
}

Course::Course(std::istringstream &istringstream) {
    std::string buf;

    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _id = std::stoi(buf);
    if (!std::getline(istringstream, _name, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    if (!std::getline(istringstream, buf, ','))
        throw std::invalid_argument("Wrong argument: " + istringstream.str());
    _teacher_id = std::stoi(buf);
}

std::list<std::pair<std::string, std::string>> Course::_get_print_parameters() const {
    return {
        {"ID", std::to_string(_id)},
        {"Name", _name},
        {"TeacherID", std::to_string(_teacher_id)}
    };
}
