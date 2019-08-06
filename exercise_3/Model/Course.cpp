//
// Created by denys on 10.07.19.
//

#include <iostream>
#include <sstream>
#include <vector>
#include "Course.hpp"

const std::string Course::ID = "ID";
const std::string Course::NAME = "Name";
const std::string Course::TEACHER_ID = "TeacherID";

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

std::vector<Parameter> Course::_get_print_parameters() const {
    return {
        {ID, std::to_string(_id)},
        {NAME, _name},
        {TEACHER_ID, std::to_string(_teacher_id)}
    };
}

bool Course::match(const std::vector<Condition> &conditions) const {
    return match_parameters(conditions, {{ID, _id,}, {TEACHER_ID, _teacher_id}}) &&
    match_parameters(conditions, {{NAME, _name}});
}

void Course::update(const std::string &key, const std::string &value) {
    if (key == NAME)
        _name = value;
    if (key == TEACHER_ID)
        _teacher_id = str_to_int(value);
}
