//
// Created by denys on 10.07.19.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "RecordsHandler.hpp"
#include "Course.hpp"
#include "Exam.hpp"
#include "Student.hpp"
#include "Teacher.hpp"


void RecordsHandler::read_records(const std::string &file_name) {
    std::ifstream   file(file_name);
    std::string     buffer;

    if (!file) {
        perror("Can't open file");
        throw std::invalid_argument("Bad file_name.");
    }
    for (int i = 1; file; ++i) {
        std::getline(file, buffer);
        try {
            if (!buffer.empty())
                _add_record(buffer);
        } catch (std::exception &e) {
            throw std::invalid_argument("Invalid file, line: " + std::to_string(i) + ". '" + buffer + "' " + e.what());
        }
    }
}

void RecordsHandler::_add_record(const std::string &record) {
    std::istringstream  istringstream_record(record);
    std::string         record_type_marker;

    if (!std::getline(istringstream_record, record_type_marker, ','))
        throw std::invalid_argument("Invalid file");
    if (auto object = _create(record_type_marker, istringstream_record)) {
        _store_in_record_container(record_type_marker, object);
    }
}

std::map<int, std::shared_ptr<IRecord>> &RecordsHandler::_get_records(const std::string &records_marker) {
    auto container_iterator = CONTAINERS.find(records_marker);
    if (container_iterator == CONTAINERS.end())
        throw std::invalid_argument("CONTAINERS map don't have " + records_marker + " key.");
    return container_iterator->second;
}

void RecordsHandler::_store_in_record_container(const std::string &record_marker, const std::shared_ptr<IRecord>& record) {
    CONTAINERS[record_marker][record->getId()] = record;
}

void RecordsHandler::print_records(const std::string &records_marker) {
    std::cout << "Print records" << std::endl;
    std::cout <<  _get_records(records_marker).size() << std::endl;

    for (auto [id, record] : _get_records(records_marker)) {
        auto a = record->getFormatted();
        std::cout << id << " " << record->getFormatted() << std::endl;
    }
}

void RecordsHandler::print_records(const std::string &records_marker, std::ofstream &ofstream) {
    std::cout << "Printing to file:";
    std::cout <<  _get_records(records_marker).size() << records_marker << std::endl;

    for (const auto &record_iterator : _get_records(records_marker))
        ofstream << records_marker << ',' << record_iterator.second->getFormatted() << std::endl;
}

void RecordsHandler::write_records(const std::string &file_name, const std::string &records_marker) {
    std::ofstream   file(file_name);
    std::string     buffer;

    if (!file) {
        perror("Can't write to file");
        throw std::invalid_argument("Bad file_name.");
    }
    try {
        print_records(records_marker, file);
    } catch (std::exception &e) {
        throw std::invalid_argument("No records with marker: " + records_marker);
    }
}

std::shared_ptr<IRecord>
RecordsHandler::_create(const std::string &type_marker, std::istringstream &istringstream_record)
{
    if (Teacher::MARKER == type_marker)
        return std::make_shared<Teacher>(istringstream_record);
    else if (Student::MARKER == type_marker)
        return std::make_shared<Student>(istringstream_record);
    else if (Course::MARKER == type_marker)
        return std::make_shared<Course>(istringstream_record);
    else if (Exam::MARKER == type_marker)
        return std::make_shared<Exam>(istringstream_record);
    else
        throw std::invalid_argument("Invalid type marker: " + type_marker);
}
