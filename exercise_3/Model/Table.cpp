//
// Created by denys on 24.07.19.
//

#include <algorithm>
#include <functional>
#include "Table.hpp"

namespace {
    auto str_toupper = [] (std::string string) {
        std::transform(string.begin(), string.end(), string.begin(), [](unsigned char c){ return std::toupper(c); });
        return string;
    };
}

Table::Table(const std::string &table_name,
        const create_record_function_t &create_record_function)
    : Table(table_name, std::string(1, table_name[0]), create_record_function) {
}

Table::Table(const std::string &table_name, const std::string &table_marker,
             const create_record_function_t &create_record_function)
    : _table_name(table_name),
      _table_marker(table_marker),
      _table_name_uppercase(str_toupper(table_name)),
      _create_record_function(create_record_function){
}

const std::string &Table::get_name() const {
    return _table_name;
}

const std::string &Table::get_marker() const {
    return _table_marker;
}

int Table::add_record(int record_id, std::shared_ptr<IRecord> record) {
    auto result = _records.insert({record_id, record});
    if (result.second)
        return record_id;
    return -1;
}

const std::string &Table::get_uppercase_name() const {
    return _table_name_uppercase;
}

const std::map<int, std::shared_ptr<IRecord>> &Table::get_all_records() const {
    return _records;
}

int Table::add_record(std::istringstream &istringstream) {
    auto record = _create_record_function(istringstream);
    int id = add_record(record->getId(), record);
    if (record->getId() != id)
        throw std::invalid_argument("Record with id='" + std::to_string(record->getId()) + "' already exist.");
    return id;
}

std::size_t Table::size() const {
    return _records.size();
}

std::vector<int> Table::clear_records(const std::vector<int> &ids) {
    std::vector<int> result;

    result.reserve(ids.size());
    for (auto id : ids) {
        if (!_records.erase(id))
            result.push_back(id);
    }
    result.shrink_to_fit();
    return result;
}
