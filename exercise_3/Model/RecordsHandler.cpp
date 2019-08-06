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
    auto str_toupper = [] (std::string string) {
        std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c){ return std::toupper(c); });
        return string;
    };
}

RecordsHandler::RecordsHandler(const std::string &file_name) {
    read_records(file_name);

}

void RecordsHandler::read_records(const std::string &file_name) {
    std::ifstream   file(file_name);
    std::string     buffer;

    _init_tables();
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

void RecordsHandler::_init_tables() {
    std::vector<std::pair<std::string, create_record_function_t>> tables = {
        {"Teacher", [](std::istringstream &istringstream_record){return std::make_shared<Teacher>(istringstream_record);}},
        {"Student", [](std::istringstream &istringstream_record){return std::make_shared<Student>(istringstream_record);}},
        {"Course", [](std::istringstream &istringstream_record){return std::make_shared<Course>(istringstream_record);}},
        {"Exam", [](std::istringstream &istringstream_record){return std::make_shared<Exam>(istringstream_record);}},
    };
    for (auto [table_name, record_create_function] : tables) {
        auto table = Table(table_name, record_create_function);
        _tables.insert({table.get_marker(), table});
    }
}

void RecordsHandler::_add_record(const std::string &record) {
    std::istringstream  istringstream_record(record);
    std::string         record_type_marker;

    if (!std::getline(istringstream_record, record_type_marker, ','))
        throw std::invalid_argument("Invalid file");
    auto table_iterator = _tables.find(record_type_marker);
    if (table_iterator != _tables.end())
        table_iterator->second.add_record(istringstream_record);
}

std::vector<std::string> RecordsHandler::get_tables() const {
    std::vector<std::string> result;

    result.reserve(_tables.size());
    for (const auto &table : _tables)
        result.push_back(table.second.get_name());
    return result;
}

const Table &RecordsHandler::get_table_by_marker(const std::string &table_marker) const {
    auto table = _tables.find(table_marker);
    if (table != _tables.end())
        return table->second;
    throw std::invalid_argument("Table with table marker '" + table_marker + "' doesn't exist.");
}

const Table &RecordsHandler::get_table(const std::string &table_name) const {
    auto table_name_uppercase = str_toupper(table_name);

    for (const auto &table_iterator : _tables)
        if (table_name_uppercase == table_iterator.second.get_uppercase_name())
            return table_iterator.second;
    throw std::invalid_argument("Table with table name '" + table_name + "' doesn't exist.");
}

const std::map<int, std::shared_ptr<IRecord>> &RecordsHandler::get_records(const std::string &table_name) const {
    return get_table(table_name).get_all_records();
}

void RecordsHandler::dump_records(std::ostream &ostream, const std::string &table_name) {
    auto table = get_table(table_name);
    for (const auto &record : table.get_all_records())
        ostream << table.get_marker() << "," << record.second->getFormatted() << std::endl;
}

void RecordsHandler::dump_records(std::ostream &ostream) {
    for (const auto &table_iterator : _tables) {
        dump_records(ostream, table_iterator.second.get_uppercase_name());
    }
}

void RecordsHandler::cleare_records(const std::string &table_name, const std::vector<int> &ids) {
    auto table_name_uppercase = str_toupper(table_name);

    for (auto &table_iterator : _tables)
        if (table_name_uppercase == table_iterator.second.get_uppercase_name()) {
            table_iterator.second.clear_records(ids);
            return;
        }
    throw std::invalid_argument("Table with table name '" + table_name + "' doesn't exist.");
}
