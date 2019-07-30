//
// Created by denys on 24.07.19.
//

#pragma once

#include <string>
#include <memory>
#include <map>
#include <functional>
#include "IRecord.hpp"

using create_record_function_t = std::function<std::shared_ptr<IRecord>(std::istringstream&)>;

class Table {
public:
//    Table() = default;
    Table(const std::string &table_name, const create_record_function_t &create_record_function);
    Table(const std::string &table_name, const std::string &table_marker,
            const create_record_function_t &create_record_function);

    const std::string &get_name() const;
    const std::string &get_uppercase_name() const;
    const std::string &get_marker() const;
    const std::map<int, std::shared_ptr<IRecord>> &get_all_records() const;
    std::size_t size() const;

    int add_record(int record_id, std::shared_ptr<IRecord> record);
    int add_record(std::istringstream &istringstream);

private:
    const std::string _table_name;
    const std::string _table_marker;
    const std::string _table_name_uppercase;
    const create_record_function_t _create_record_function;

    std::map<int, std::shared_ptr<IRecord>> _records;
};



