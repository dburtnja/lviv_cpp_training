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


namespace {
    auto create = [](const std::string &type_marker, std::istringstream &istringstream_record) ->
            std::shared_ptr<IRecord>{
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
    };
    auto str_toupper = [] (std::string string) {
        std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c){ return std::toupper(c); });
        return string;
    };
}

const std::list<std::pair<std::string, std::string>> RecordsHandler::RECORD_MARKERS = {
        {Student::RECORD_NAME, Student::MARKER},
        {Teacher::RECORD_NAME, Teacher::MARKER},
        {Course::RECORD_NAME, Course::MARKER},
        {Exam::RECORD_NAME, Exam::MARKER}
};

RecordsHandler::RecordsHandler(const std::string &file_name) {
    read_records(file_name);
}

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
    if (auto object = create(record_type_marker, istringstream_record)) {
        _store_in_record_container(record_type_marker, object);
    }
}

const std::map<int, std::shared_ptr<IRecord>> &RecordsHandler::_get_records_by_marker(const std::string &records_marker) const {
    auto container_iterator = CONTAINERS.find(records_marker);
    if (container_iterator == CONTAINERS.end())
        throw std::invalid_argument("CONTAINERS map don't have " + records_marker + " key.");
    return container_iterator->second;
}

void RecordsHandler::_store_in_record_container(const std::string &record_marker, const std::shared_ptr<IRecord>& record) {
    auto result = CONTAINERS[record_marker].insert({record->getId(), record});
    if (!result.second)
        throw std::invalid_argument("Record with id='" + std::to_string(record->getId()) + "' already exist.");
}

void RecordsHandler::dump_records(std::ostream &ostream, const std::string &table_name) {
    for (const auto& record : get_records(table_name))
        ostream << record.second->getFormatted() << std::endl;

}

const std::map<int, std::shared_ptr<IRecord>> &RecordsHandler::get_records(const std::string &table_name) const {
    auto marker = std::find_if(RECORD_MARKERS.begin(), RECORD_MARKERS.end(),
            [table_name = str_toupper(table_name)] (const std::pair<std::string, std::string> &record_names) {
                return table_name == str_toupper(record_names.first);
    });
    if (marker == RECORD_MARKERS.end())
        throw std::invalid_argument("No table name '" + table_name + "' found.");
    return _get_records_by_marker(marker->second);
}

std::list<std::string> RecordsHandler::get_tables() const {
    std::list<std::string>  result;

    for (const auto &iterator : RECORD_MARKERS)
        result.push_back(iterator.first);
    return result;
}

